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

      // Set screen x-coordinate of drawable
      void setX(int x);

      // Set screen y-coordinate of drawable
      void setY(int y);

      // Get screen x-coordinate of drawable
      int getX();

      // Get screen y-coordinate of drawable
      int getY();

      // Get height of current animation.
      uint getHeight() const;

      // Get width of current animation.
      uint getWidth() const;

      // Add a new Animation to the Drawable with an associated name.
      void addAnimation(Animation* animation, std::string name);

      // Remove an animation from the Drawable by provided name.
      bool removeAnimation(std::string name);

      // Checks to see if the Drawable needs to be updated on the Screen.
      bool needsUpdate();

      // Sets the new coordinate of the drawable.  Marks as moved.
      void move(int newX, int newY);

      // Move the Drawable by an Offset.  Marks as moved.
      void moveByOffset(int offX, int offY);

      // Sets the an animation to swap to.  Marks as swapped.
      bool swapAnimation(std::string name);

      // Triggers the current animation to animate.
      void play();

      // Triggers the current animation to stop animating.
      void stop();

      // Triggers the Drawable to no longer display.
      void hide();

      // Triggers the Drawable to display.
      void show();

      // Schedules the Drawable to be removed from the Layer and deleted from
      // memory after first being hidden.
      void unload();

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

      // Is the Drawable visible?
      bool hidden;
      
      // Has the Drawable already been hidden?  If so, no need to updateRect again.
      bool hasBeenHidden;

      // Schedules the drawable to be removed.  Drawable must be hidden before
      // being removed.  Use Drawable::unload()
      bool toBeRemoved;

      // Has the current animation been changed?  Reset in doAnim()
      bool swapped;

      SDL_Rect getRect();

      // Find the intersecting rectangle between the provided rect and the
      // current animation's rect.
      SDL_Rect getIntersectingRect(SDL_Rect r);

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

      // Handles the hiding of a Drawable.
      // When the Drawable::hidden bit is set this method will stop Animation
      // and rects from Layers beneath the drawable are blitted on top of the
      // Drawable.
      void doHide();

      void updateRect(SDL_Rect r);

	  static unsigned int nextUniqueNumber;

	  std::string instanceName;

   friend class Layer;

};
#endif//DRAWABLE_H
