#ifndef ANIMATION_H
#define ANIMATION_H
#include "externals.h"
#include "AnimationState.h"
#include "RectBlitter.h"

class Animation
{
   private:

      // Helper for Constructors.  Initialize Animation members.
      void init(uint width, uint height, uint sps, uint ssRows, uint ssCols);

      // Status of animation for observation.
      AnimationState status;

      // Still Dimensions
      uint height, width;

      // Number of frames since last still update.
      uint frameCounter;

      // Still being displayed currently.
      uint currentStill;

      // Rate at which stills are updated.  Stills per second.
      uint sps;

      // Sprite Sheet.  Hot Pink is transparent.
      std::shared_ptr<SDL_Surface> spriteSheet;

      // Dimensions of spritesheet.
      uint ssCols, ssRows;

   public:
      // Constructor.  Makes sprite sheet by reading a File.
      Animation(std::string filename, uint width, uint height, uint sps, 
		  uint ssRows, uint ssCols);

      // Constructor.  Makes sprite sheet with an SDL_Surface*
      Animation(SDL_Surface* surf, uint width, uint height, uint sps, uint
        ssRows, uint ssCols);

      // Constructor.  Makes sprite sheet and assumes there is only 1 frame.
      Animation(SDL_Surface* surf);

      // Updates the current still.
      void advance();

      // Adds 1 to the frame counter.
      void incFrameCounter();

      // Returns true when the animation is ready to advace.
      bool needsUpdate();

      // Blits this animation to the screen, updating the provided rect on the
      // screen.
      void updateRect(SDL_Rect r, uint offsetX, uint offsetY);

      // Return the total count of stills for the assigned spritesheet.
      uint getStillCount();

      // Accessors.
      uint getWidth();
      uint getHeight();
      uint getSPS();
      AnimationState getStatus();

      // Mutators.
      void setSPS(uint sps);

};
#endif//ANIMATION_H
