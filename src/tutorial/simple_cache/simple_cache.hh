class AccessEvent : public Event
{
        private:
                SimpleCache *cache;
                PacketPtr pkt;

        public:
                AccessEvent(SimpleCache *cache, PacketPtr pkt) :
                        Event(Default_Pri, AutoDelete), cache(cache), pkt(pkt)
                        { }

                void process() override
                {
                        cache->accessTiming(pkt);
                }
};
