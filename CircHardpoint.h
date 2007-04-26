#ifndef CIRC_HARDPOINT_H
#define CIRC_HARDPOINT_H

#include "Hardpoint.h"

class CircHardpoint : public Hardpoint
{
   private:
      int radius;
   public:
      bool conflict(int wc) const;

};

#endif //CIRC_HARDPOINT
