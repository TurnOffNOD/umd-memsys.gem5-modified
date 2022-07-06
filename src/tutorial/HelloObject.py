from m5.params import *
from m5.SimObject import SimObject

class HelloObject(SimObject):
    type = 'HelloObject'
    cxx_header = "tutorial/hello_object.hh"

    time_to_wait = Param.Latency("Time before firing an event.")
    number_of_fires = Param.Int(1, "No. of times to fire
            events before goodbye.")

