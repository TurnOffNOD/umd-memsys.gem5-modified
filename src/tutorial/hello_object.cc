#include "tutorial/hello_object.hh"

#include <iostream>

HelloObject::HelloObject(HelloObjectParams *params) :
        SimObject(params)
{
        std::cout << "Hello World from SimObject!" << std::endl;
}

HelloObject *HelloObjectParams::create()
{
        return new HelloObject(this);
}

