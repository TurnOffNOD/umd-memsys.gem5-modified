#include <iostream>

#include "debug/Hello.hh"
#include "tutorial/hello_object.hh"

HelloObject::HelloObject(HelloObjectParams *params) :
        SimObject(params), event([this]{processEvent();}, name())
{
//        std::cout << "Hello World from SimObject!" << std::endl;
        DPRINTF(Hello, "Created the new hello object\n");
}

void HelloObject::processEvent()
{
        DPRINTF(Hello, "Hello World! Processing the Event!\n");
}

HelloObject *HelloObjectParams::create()
{
        return new HelloObject(this);
}

void HelloObject::startup()
{
        schedule(event, 100);
}
