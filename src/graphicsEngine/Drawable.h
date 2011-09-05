#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "externals.h"
#include "DrawableState.h"
#include "Animation.h"

class Drawable
{
   public:
      Drawable(std::string name);
      ~Drawable();

      // Return current animation's name.
      std::string getCurrentAnimation();

      // Return the Drawable's name. (i.e. "tree")
      std::string getName();

      // Return the Drawable's unique instance name. (i.e. "treeb01017f")
      std::string getInstanceName();

      // Return the current status of the Drawable.
      DrawableState getStatus();

      // Add a new Animation to the Drawable with an associated name.
      void addAnimation(Animation* animation, std::string name);

      // Remove an animation from the Drawable by provided name.
      bool removeAnimation(std::string name);

      // Checks to see if the Drawable needs to be updated on the Screen.
      bool needsUpdate();

      // Sets the new coordinate of the drawable.  Marks as moved.
      bool move(int newX, int newY);

      // Move the Drawable by an Offset.  Marks as moved.
      bool moveByOffset(int offX, int offY);

      // Sets the an animation to swap to.  Marks as swapped.
      bool swapAnimation(std::string name);

      // Triggers the current animation to animate.
      void play();

      // Triggers the current animation to stop animating.
      void stop();

      void updateRect(SDL_Rect r);

      // The following do**** ops should be called in the order provided:
      // Handles situations when a Drawable coordinates changed.
      // Specifically, it "erases" where the Drawable was.
      void doMove();

      // Handles situations when a Drawable has a swapped animation.
      // Specifically, it "erases" the frame of the animation displayed before
      // the animation swap.
      void doSwap();

      // Handles the default Animation still update scenario.
      // Updates the current Animation.  Also resets the moved and swapped flags.
      void doAnim();

   private:

      // Reference name of the drawable.
      std::string name;

      // Map of animations for this drawable.
      std::map<std::string, Animation*> animation;

      // Current status of the Drawable for observation.
      DrawableState status;

      // Animation currently being used.
      std::string currentAnimation;

      // Animation to swap to.
      std::string newAnimation;
      
      // Current coordinates.
      int x, y;

      // Coordinates to be updated to.
      int newX, newY;

      // Have the coordinates been updated?  Reset in doAnim()
      bool moved;

      // Has the current animation been changed?  Reset in doAnim()
      bool swapped;

      SDL_Rect getRect();

      // Find the intersecting rectangle between the provided rect and the
      // current animation's rect.
      SDL_Rect getIntersectingRect(SDL_Rect r);

};
#endif//DRAWABLE_H
