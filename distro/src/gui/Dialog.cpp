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

int Dialog::getWordNPos(int n) {
   if (n <= 0) {
      return 0;
   }

   int pos = text.find(" ", 0);

   while (n-- > 0 && pos != -1) {
      pos = text.find(" ", pos+1);
   }

   return pos;
}

int Dialog::getWordCount(std::string text) {
   int pos = text.find(" ", 0);

   int count = 0;

   while (pos != -1) {
      count++;
      pos = text.find(" ", pos+1);
   }

   return count;
}

std::string Dialog::chopUpToWordN(int n) {
   int pos = this->getWordNPos(n-1);

   return text.substr(0, pos);
}

void Dialog::drawText() {

   // Black
   SDL_Color color = {0x00, 0x00, 0x00};

   TTF_Font* font = ResourceLoader::GetFont("Vera.ttf", 20);

   //std::string chunk = text.substr(0, m);
   //std::string line = text.substr(l, r);

   // Let n = Count Number of Words in String
   Uint16 n = this->getWordCount(this->text);
   Uint16 l = 0;
   Uint16 r = n;

   std::string chunk = "";

   int tries = 10;
   while (l < r && tries > 0) {


      Uint16 m = (r - l)/2 + l;

      chunk = this->chopUpToWordN(m);

      std::cout << chunk << std::endl;
      std::cout << l << std::endl;
      std::cout << r << std::endl;
      std::cout << m << std::endl;

      // determine rendered width of m words
      int h = 0;
      int w = 0;
      TTF_SizeText(font, chunk.c_str(), &w, &h);

      // rendered width > dialog width
      if (w > this->getWidth()) {
         r = m - 1;
      } else {
         l = m + 1;
      }
      tries--;
   }

   // Build the text surface containing the given string.
   SDL_Surface* text_surface = TTF_RenderText_Solid(
        font
      , chunk.c_str()
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
