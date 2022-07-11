#include "base/logging.hh"
#include "sim/sim_exit.hh"
#include "tutorial/simple_cache/simple_cache.hh"

SimpleCache::SimpleCache(SimpleCacheParams *params) :
        MemObject(params),
        latency(params->latency),
        blockSize(params->system->cacheLineSize()),
        capacity(params->size / blockSize),
        memPort(params->name + ".mem_side", this),
        blocked(false), outstandingPacket(nullptr), waitingPortId(-1)
{
        for (int i = 0; i < params->port_cpu_side_connection_count; ++i)
        {
                cpuPorts.emplace_back(name() + csprintf(".cpu_side[%d]", i), i, this);
        }
}


BaseSlavePort&
SimpleCache::getSlavePort(const std::string& if_name, PortID idx)
{
        if (if_name == "cpu_side" && idx < cpuPorts.size())
        {
                return cpuPorts[idx];
        }
        else
        {
                return MemObject::getSlavePort(if_name, idx);
        }
}



bool
SimpleCache::handleRequest(PacketPtr pkt, int port_id)
{
        if (blocked)
        {
                return false;
        }
        DPRINTF(SimpleCache, "Got request for addr %#x\n", pkt->getAddr());

        blocked = true;
        waitingPortId = port_id;

        schedule(new AccessEvent(this, pkt), clockEdge(latency));

        return true;
}



void
SimpleCache::accessTiming(PacketPtr pkt)
{
        bool hit = accessFunctional(pkt);
    if (hit)
        {
        pkt->makeResponse();
        sendResponse(pkt);
    }
        else
        {}
}




void SimpleCache::sendResponse(PacketPtr pkt)
{
    int port = waitingPortId;

    blocked = false;
    waitingPortId = -1;

    cpuPorts[port].sendPacket(pkt);
    for (auto& port : cpuPorts)
        {
        port.trySendRetry();
    }
}


void
SimpleCache::accessTiming(PacketPtr pkt)
{
    bool hit = accessFunctional(pkt);
    if (hit)
        {
        pkt->makeResponse();
        sendResponse(pkt);
    }
        else
        {
        Addr addr = pkt->getAddr();
        Addr block_addr = pkt->getBlockAddr(blockSize);
        unsigned size = pkt->getSize();
        if (addr == block_addr && size == blockSize)
                {
            DPRINTF(SimpleCache, "forwarding packet\n");
            memPort.sendPacket(pkt);
        }
                else
                {
            DPRINTF(SimpleCache, "Upgrading packet to block size\n");
            panic_if(addr - block_addr + size > blockSize,
                     "Cannot handle accesses that span multiple cache lines");

            assert(pkt->needsResponse());
            MemCmd cmd;
            if (pkt->isWrite() || pkt->isRead())
                        {
                cmd = MemCmd::ReadReq;
            }
                        else
                        {
                panic("Unknown packet type in upgrade size");
            }

            PacketPtr new_pkt = new Packet(pkt->req, cmd, blockSize);
            new_pkt->allocate();

            outstandingPacket = pkt;

            memPort.sendPacket(new_pkt);
        }
    }
}


bool
SimpleCache::handleResponse(PacketPtr pkt)
{
    assert(blocked);
    DPRINTF(SimpleCache, "Got response for addr %#x\n", pkt->getAddr());
    insert(pkt);

    if (outstandingPacket != nullptr)
        {
        accessFunctional(outstandingPacket);
        outstandingPacket->makeResponse();
        delete pkt;
        pkt = outstandingPacket;
        outstandingPacket = nullptr;
    } // else, pkt contains the data it needs

    sendResponse(pkt);

    return true;
}



bool
SimpleCache::accessFunctional(PacketPtr pkt)
{
    Addr block_addr = pkt->getBlockAddr(blockSize);
    auto it = cacheStore.find(block_addr);
    if (it != cacheStore.end())
        {
        if (pkt->isWrite())
                {
            pkt->writeDataToBlock(it->second, blockSize);
        }
                else if (pkt->isRead())
                {
            pkt->setDataFromBlock(it->second, blockSize);
        }
                else
                {
            panic("Unknown packet type!");
        }
        return true;
    }
    return false;
}



void
SimpleCache::insert(PacketPtr pkt)
{
    if (cacheStore.size() >= capacity)
        {
        int bucket, bucket_size;
        do
                {
            bucket = random_mt.random(0, (int)cacheStore.bucket_count() - 1);
        }
                while ( (bucket_size = cacheStore.bucket_size(bucket)) == 0 );

                auto block = std::next(cacheStore.begin(bucket),
                               random_mt.random(0, bucket_size - 1));

        RequestPtr req = new Request(block->first, blockSize, 0, 0);
        PacketPtr new_pkt = new Packet(req, MemCmd::WritebackDirty, blockSize);
        new_pkt->dataDynamic(block->second); // This will be deleted later

        DPRINTF(SimpleCache, "Writing packet back %s\n", pkt->print());
        memPort.sendTimingReq(new_pkt);

        cacheStore.erase(block->first);
    }
    uint8_t *data = new uint8_t[blockSize];
    cacheStore[pkt->getAddr()] = data;

    pkt->writeDataToBlock(data, blockSize);
}
