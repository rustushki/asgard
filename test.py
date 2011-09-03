# Demo #1
#import asgard
#asgard.LoadBoundingBox(0, 0)
#asgard.LoadDrawable("OsirisCat")

# Demo #2
#import map
#map.SetFocus(100, 300)

# Demo #3
import map
import time

for x in range(1, 2000, 1):
	map.SetFocus(x, 300)
	time.sleep (0.1)

