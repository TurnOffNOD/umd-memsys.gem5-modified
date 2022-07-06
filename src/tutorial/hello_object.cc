#include <iostream>

#include "debug/Hello.hh"
#include "tutorial/goodbye_object.hh"
#include "tutorial/hello_object.hh"

//#include "base/misc.hh"

HelloObject::HelloObject(HelloObjectParams *params) :
        SimObject(params),
        event(*this), goodbye(params->goodbye_object),
        myName(params->name),
        latency(params->time_to_wait), timesLeft(params->number_of_fires)
{
//        std::cout << "Hello World from SimObject!" << std::endl;
        DPRINTF(Hello, "Created the new object with the name %s\n", myName);
//	panic_if(!goodbye, "HelloObject must have a non-null GoodbyeObject");
}

void HelloObject::processEvent()
{
        timesLeft--;
        DPRINTF(Hello, "Hello World! Processing the Event!\
                        After this, %d left\n", timesLeft);

        if (timesLeft <=0)
        {
                DPRINTF(Hello, "Done firing!\n");
                goodbye->sayGoodbye(myName);
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
