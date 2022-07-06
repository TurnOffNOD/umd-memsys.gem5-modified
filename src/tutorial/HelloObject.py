from m5.params import *
from m5.SimObject import SimObject

class HelloObject(SimObject):
    type = 'HelloObject'
    cxx_header = "tutorial/hello_object.hh"

    time_to_wait = Param.Latency("Time before firing an event.")
    number_of_fires = Param.Int(1, "No. of times to fire "
            "events before goodbye.")

    goodbye_object = Param.GoodbyeObject("My goodbye object")



class GoodbyeObject(SimObject) :
    type = 'GoodbyeObject'
    cxx_header = "tutorial/goodbye_object.hh"

    buffer_size = Param.MemorySize('1kB',"Size of "
            "buffer to fill with goodbye.")

    write_bandwidth = Param.MemoryBandwidth('100MB/s', "Badnwidth "
            "to fill the buffer")
