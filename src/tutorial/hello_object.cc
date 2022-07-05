#include <iostream>

#include "hello_objedt.hh"

HelloObject::HelloObject(HelloObjectParams *params):
        SimObject(params)
{
        std::out << "Hello World from SimObject!" << std::endl;
}

HelloObject *HelloObjectParams::create()
{
        return new HelloObject(this);
}

