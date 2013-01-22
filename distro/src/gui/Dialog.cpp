#include "Dialog.h"

Dialog::Dialog(std::string image, std::string text) {
	// Discard Image for the Momemnt.

	// Set the text member.
	this->text = text;
}

Dialog::~Dialog() {

}

void Dialog::buildSurface() {
   Box::buildSurface();
   this->drawText();
}

void Dialog::drawText() {

   // Black
   SDL_Color color = {0x00, 0x00, 0x00};

   // Build the text surface containing the given string.
   SDL_Surface* text_surface = TTF_RenderText_Solid(
        ResourceLoader::GetFont("Vera.ttf", 20)
      , text.c_str()
      , color
   );

   // If the surface is not created successfully.
   if (text_surface == NULL) {
      LOG(INFO) << this->text.c_str();
      LOG(ERROR) << "Error creating text: " << TTF_GetError();
      exit(1);

      // Otherwise,
   } else {

      // TODO: Implement Wrapping ...

      // Create a destination rectangle based on the created text surface and
      // the position parameter.
      SDL_Rect r;
      r.w = text_surface->w;
      r.h = text_surface->h;
      r.x = 0;
      r.y = 0;
      //r.y = ::getHeight() - text_surface->h;

      // Blit the text to the screen.
      SDL_BlitSurface(text_surface, NULL, this->tempSurf, &r);

      // TODO:
      // This method needs to return whatever it decided not to display due to
      // wrapping constraints.
   }

}
