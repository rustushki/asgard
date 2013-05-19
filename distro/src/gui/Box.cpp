#include "externals.h"
#include "Box.h"
#include "DrawableFactory.h"
#include "GuiFactory.h"
#include "GraphicsEngine.h"
#include "Theme.h"

Box::Box() {
   this->box = NULL;
}

Box::~Box() {

}

/* ------------------------------------------------------------------------------
 * setPosition - Set the top left corner of the box.  The coordinate provided
 * should be a screen coordinate.
 */
void Box::setPosition(Coordinate<ScreenPoint> pos) {
   this->pos = pos;
   this->refresh();
}

/* ------------------------------------------------------------------------------
 * setDimension - Set the width and height of the box.
 */
void Box::setDimension(uint width, uint height) {
   this->width = width;
   this->height = height;
   this->refresh();
}

/* ------------------------------------------------------------------------------
 * getPosition - Return the coordinate of the top left corner of the box.
 * This is a screen coordinate.
 */
Coordinate<ScreenPoint> Box::getPosition() const {
   return this->pos;
}

/* ------------------------------------------------------------------------------
 * getHeight - Get the Height of the Box.
 */
uint Box::getHeight() const {
   return this->height;
}

/* ------------------------------------------------------------------------------
 * getWidth - Get the Width of the Box.
 */
uint Box::getWidth() const {
   return this->width;
}

/* ------------------------------------------------------------------------------
 * show - Display the Box instance on the GUI Layer of the GraphicsEngine.
 */
void Box::show() const {
   this->box->show();
}

/* ------------------------------------------------------------------------------
 * hide - Hide this Box instance and do not show it on the GUI Layer of the
 * GraphicsEngine any longer.
 */
void Box::hide() const {
   this->box->hide();
}

/* ------------------------------------------------------------------------------
 * unload - Hide this Box instance and remove it from memory.
 */
void Box::unload() const {
   this->box->unload();
}

/* ------------------------------------------------------------------------------
 * refresh - Update all graphical elements associated with this Box instance.
 */
void Box::refresh() {

   this->buildSurface();

   // Glue In Four Corners and Four Borders.

   // TODO:
   // Write the text.

   // Build an Single Still Animation based on the constructed SDL_Surface.
   Animation* anim = new Animation(this->tempSurf.get());

   // If the initial Drawable has not yet been built, go ahead and build it.
   bool justCreated = false;
   if (this->box == NULL) {
      this->box = DrawableFactory::build(this->tempSurf.get(), "dialog");
      justCreated = true;

   // Otherwise, go ahead and switch out the animation.
   } else {
      this->box->removeAnimation("default");
      this->box->addAnimation(anim, "default");
   }

   // Ensure that the drawable is animating its animation.
   this->box->play();

   // Only add the drawable to the GraphicsEngine if it's just been created.
   if (justCreated) {
      GraphicsEngine* ge = GraphicsEngine::getInstance();
      ge->displayDrawable(this->box, "gui", 0, 0);
   }
}

/* ------------------------------------------------------------------------------
 * buildSurface - Create the tempSurf (SDL_Surface) by blitting corners, edges
 * and background onto it (effectively an empty box).
 *
 * Override to implement additional behavior.
 */
void Box::buildSurface() {

   // Create an SDL_Surface.
   this->tempSurf = std::shared_ptr<SDL_Surface>(SDL_CreateRGBSurface(
        SDL_HWSURFACE
      , this->width
      , this->height
      , 32
      , 0,0,0,0
   ));

   // Get the Theme object.
   auto theme = GuiFactory::GetInstance()->getTheme();

   // Tile
   SDL_Surface* bg = theme->buildElement("bg");

   // Edges
   SDL_Surface* bh = theme->buildElement("bh");
   SDL_Surface* bw = theme->buildElement("bw");

   // Corners
   SDL_Surface* tl = theme->buildElement("tl");
   SDL_Surface* tr = theme->buildElement("tr");
   SDL_Surface* bl = theme->buildElement("bl");
   SDL_Surface* br = theme->buildElement("br");

   // Tile the Background onto the Surface.
   this->twoDimTile(bg, tl->w/2, tl->h/2, this->tempSurf->w - br->w, this->tempSurf->h - br->h);

   // Tiles the Edges onto the Surface.
   this->horzLinearTile(bw, tl->w, 0, this->tempSurf->w - tl->w);
   this->vertLinearTile(bh, 0, tl->h, this->tempSurf->h - bl->h);
   this->horzLinearTile(bw, br->w, this->getHeight() - br->h, this->tempSurf->w - tl->w);
   this->vertLinearTile(bh, this->getWidth() - tr->w, tl->h, this->tempSurf->h - br->h);

   // Draw the Corners onto the surface.
   this->singBlit(tl, 0, 0);
   this->singBlit(tr, this->getWidth() - tr->w, 0);
   this->singBlit(bl, 0, this->getHeight() - bl->h);
   this->singBlit(br, this->getWidth() - br->w, this->getHeight() - br->h);

}


/* ------------------------------------------------------------------------------
 * singBlit - Blit exactly the provided surface onto the tempSurf at the
 * provided X, Y.
 */
void Box::singBlit(SDL_Surface* surf, Uint16 x, Uint16 y) {

   // Rectangle from the Source Surface.
   SDL_Rect srcRect;
   srcRect.x = 0;
   srcRect.y = 0;
   srcRect.h = surf->h;
   srcRect.w = surf->w;

   // Rectangle to blit to on the Destination Surface.
   SDL_Rect destRect;
   destRect.x = x;
   destRect.y = y;
   destRect.h = surf->h;
   destRect.w = surf->w;

   // Perform Blit.
   SDL_BlitSurface(surf, &srcRect, this->tempSurf.get(), &destRect);
}

/* ------------------------------------------------------------------------------
 * horzLinearTile - Perform a horizontal linear tile starting at the X,Y
 * provided at the height of the provided surface for the count of the passed
 * width of pixels.
 *
 * This is like unrolling some wrapping paper horizontally.
 */
void Box::horzLinearTile(SDL_Surface* surf, Uint16 x, Uint16 y, Uint16 w) {

   // How many horizontal blits are required to cover w pixels?
   Uint16 blitCnt = w / surf->w;

   // Set the Clipping Rect.
   // This ensures that we never blit beyond the edges of this rectable.
   SDL_Rect rect;
   rect.x = x;
   rect.y = y;
   rect.h = surf->h;
   rect.w = w;
   SDL_SetClipRect(this->tempSurf.get(), &rect);

   // Blit the Surface across the horizontal region.
   for (Uint16 cnt = 0; cnt < blitCnt; cnt++) {
      this->singBlit(surf, cnt * surf->w, y);
   }

   // Clear the Clipping Rect.
   SDL_SetClipRect(this->tempSurf.get(), NULL);
}

/* ------------------------------------------------------------------------------
 * vertLinearTile - Perform a vertical linear tile starting at the X,Y provided
 * at the width of the provided surface for the count of the passed height of
 * pixels.
 *
 * This is like unrolling some wrapping paper vertically.
 */
void Box::vertLinearTile(SDL_Surface* surf, Uint16 x, Uint16 y, Uint16 h) {

   // How many vertical blits are required to cover w pixels?
   Uint16 blitCnt = h / surf->h;

   SDL_Rect rect;
   rect.x = x;
   rect.y = y;
   rect.h = h;
   rect.w = surf->w;

   // Set the Clipping Rect.
   // This ensures that we never blit beyond the edges of this rectable.
   SDL_SetClipRect(this->tempSurf.get(), &rect);

   // Blit the Surface across the vertical region.
   for (Uint16 cnt = 0; cnt < blitCnt; cnt++) {
      this->singBlit(surf, x, cnt * surf->h);
   }

   // Clear the Clipping Rect.
   SDL_SetClipRect(this->tempSurf.get(), NULL);
}

/* ------------------------------------------------------------------------------
 * twoDimTile - Tile the provided surface across the tempSurf starting at the
 * provided X,Y as far as the provided height and width.
 *
 * This is like wallpapering a wall.
 */
void Box::twoDimTile(SDL_Surface* surf, Uint16 x, Uint16 y, Uint16 w, Uint16 h) {

   // How many horizontal and vertical blits are required to accomplish the
   // tiling?
   Uint16 hBlitCnt = w / surf->w;
   Uint16 vBlitCnt = h / surf->h;

   // Set the Clipping Rect.
   // This ensures that we never blit beyond the edges of this rectable.
   SDL_Rect rect;
   rect.x = x;
   rect.y = y;
   rect.h = h;
   rect.w = w;
   SDL_SetClipRect(this->tempSurf.get(), &rect);

   for (Uint16 hCnt = 0; hCnt <= hBlitCnt; hCnt++) {
      for (Uint16 vCnt = 0; vCnt <= vBlitCnt; vCnt++) {
         this->singBlit(surf, hCnt * surf->w, vCnt * surf->h);
      }
   }

   // Clear the Clipping Rect.
   SDL_SetClipRect(this->tempSurf.get(), NULL);
}

std::shared_ptr<SDL_Surface> Box::getTempSurf() {
   return tempSurf;
}
