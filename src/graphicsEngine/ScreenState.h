#ifndef SCREENSTATE_H
#define SCREENSTATE_H
enum ScreenState
{
   SCREENSTATE_IDLE,
   SCREENSTATE_INITTING,
   SCREENSTATE_PREPARING,
   SCREENSTATE_FLIPPING,
   SCREENSTATE_DESTROYING,
   SCREENSTATE_COUNT
};
#endif//SCREENSTATE_H