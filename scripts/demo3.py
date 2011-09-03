# Demo #3 - Ugly Pan
# This is a terrible way to pan.  There should be a built in support for
# Panning.  This is here just for demo purposes.
import map
import time

y = 0

for x in range(0, 1350, 10):
	map.SetFocus(x, y)
	time.sleep (0.1)

for y in range(0, 1350, 10):
	map.SetFocus(x, y)
	time.sleep (0.1)

for x in range(1350, 0, -10):
	map.SetFocus(x, y)
	time.sleep (0.1)

for y in range(1350, 0, -10):
	map.SetFocus(x, y)
	time.sleep (0.1)
