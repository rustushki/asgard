#ifndef RECT_HARDPOINT_H
#define RECT_HARDPOINT_H

#include "Hardpoint.h"

class RectHardpoint : public Hardpoint
{
   private:
      int height;
      int width;
   public:
      bool conflict(int wc) const;
};

#endif //RECT_HARDPOINT_H
