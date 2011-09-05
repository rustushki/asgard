# Demo #4 - Ugly pan off screen.
# Pan the Map so that some map objects immediately go off screen.
import map
import time

y = 0

for x in range(400, 1000, 2):
	map.SetFocus(x, y)
	time.sleep (0.1)
