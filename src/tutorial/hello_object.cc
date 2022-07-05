#include <iostream>

#include "debug/Hello.hh"
#include "tutorial/hello_object.hh"

HelloObject::HelloObject(HelloObjectParams *params) :
        SimObject(params)
{
//        std::cout << "Hello World from SimObject!" << std::endl;
        DPRINTF(Hello, "Created the hello object\n");
}

HelloObject *HelloObjectParams::create()
{
        return new HelloObject(this);
}

