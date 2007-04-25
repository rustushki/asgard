#ifndef _CIRCHARDPOINT_H
#define _CIRCHARDPOINT_H

#include "hardpoint.h"

class CircHardPoint : public Hardpoint
{
	private:
		int radius;
	public:
		bool conflict(int wc) const;

};

#endif
