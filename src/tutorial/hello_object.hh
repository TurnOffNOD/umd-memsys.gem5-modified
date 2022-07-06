#ifndef __TUTORIAL_GEM5_HELLO_OBJECT_HH__
#define __TUTORIAL_GEM5_HELLO_OBJECT_HH__

#include "params/HelloObject.hh"
#include "sim/sim_object.hh"

class HelloObject : public SimObject
{
        private:
                void processEvent();

                EventWrapper<HelloObject, &HelloObject::processEvent> event;

                GoodbyeObject *goodbye;

                std::string myName;
                Tick latency;
                int timesLeft;


        public:
                HelloObject(HelloObjectParams *p);

        void startup();
};

#endif // __LEARNING_GEM5_HELLO_OBJECT_HH__
