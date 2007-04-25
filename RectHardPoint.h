#ifndef _RECTHARDPOINT_H
#define _RECTHARDPOINT_H

#include "hardpoint.h"

class RectHardPoint : public Hardpoint
{
   private:
      int height;
      int width;
   public:
      bool conflict(int wc) const;
};

#endif
