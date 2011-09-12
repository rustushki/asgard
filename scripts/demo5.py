# Demo #5 - Trigger Unloading of Bounding Box
# Rapidly pan the map to cause a Bounding Box to be unloaded.
import map
import time


for x in range(0, 4000, 20):
	map.SetFocus(x, 0);
	time.sleep(.1)
