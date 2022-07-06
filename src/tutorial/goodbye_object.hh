#ifndef __TUTORIAL_GEM5_GOODBYE_OBJECT_HH__
#define __TUTORIAL_GEM5_GOODBYE_OBJECT_HH__

#include <string>

#include "params/GoodbyeObject.hh"
#include "sim/sim_object.hh"

class GoodbyeObject : public SimObject
{
        private:
                void processEvent();

        /**
         *Fills the buffer for one iteration. If the buffer isn't full, this
         *function will enqueue another event to continue filling.
         */
        void fillBuffer();

        EventWrapper<GoodbyeObject, &GoodbyeObject::processEvent> event;

        /// The bytes processed per tick
        float bandwidth;

        /// The size of the buffer we are going to fill
        int bufferSize;

        /// The buffer we are putting our message in
        char *buffer;

        /// The message to put into the buffer.
        std::string message;

        /// The amount of the buffer we've used so far.
        int bufferUsed;


        public:
                GoodbyeObject(GoodbyeObjectParams *p);
                ~GoodbyeObject();

        void sayGoodbye(std::string name);
};

#endif // __TUTORIAL_GEM5_GOODBYE_OBJECT_HH__
