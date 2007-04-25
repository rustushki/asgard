#ifndef _HARDPOINT_H
#define _HARDPOINT_H
class Hardpoint
{
   protected:
      int coordinate;

   public:
      virtual bool conflict(const int wc) const = 0;
};
#endif
