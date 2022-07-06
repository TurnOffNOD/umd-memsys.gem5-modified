import m5
from m5.objects import *

root = Root(full_system = False)

root.hello = HelloObject(number_of_fires = 5);
root.hello.time_to_wait = '2us';

root.hello.goodbye_object = GoodbyeObject(buffer_size = '100B');

m5.instantiate()

print("Beginning Simulation...")
exit_event = m5.simulate()
#print('Exiting @tick {} because {}'
#        .format(m5.curTick(), exit_event.getCause()))
print('Exiting @tick %i because %s' % (m5.curTick(), exit_event.getCause()))
