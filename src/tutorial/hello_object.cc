#include <iostream>

#include "debug/Hello.hh"
#include "tutorial/hello_object.hh"

HelloObject::HelloObject(HelloObjectParams *params) :
        SimObject(params), event([this]{processEvent();}, name()),
        latency(100), timesLeft(10)
{
//        std::cout << "Hello World from SimObject!" << std::endl;
        DPRINTF(Hello, "Created the new hello object\n");
}

void HelloObject::processEvent()
{
        timesLeft--;
        DPRINTF(Hello, "Hello World! Processing the Event!\
                        After this, %d left\n", timesLeft);

        if (timesLeft <=0)
        {
                DPRINTF(Hello, "Done firing!\n");
        }
        else
        {
                schedule(event, curTick() + latency);
        }
}

HelloObject *HelloObjectParams::create()
{
        return new HelloObject(this);
}

void HelloObject::startup()
{
        schedule(event, latency);
}
