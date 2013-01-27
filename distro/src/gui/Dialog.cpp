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

int Dialog::getWordNPos(int n, std::string text) {
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

std::string Dialog::getUpToWordN(int n, std::string text) {
   int pos = Dialog::getWordNPos(n-1, text);


   return text.substr(0, pos);
}

std::string Dialog::getAfterWordN(int n, std::string text) {
   int pos = Dialog::getWordNPos(n-1, text);

   return text.substr(pos+1);
}

std::string Dialog::getNextLine(std::string & remainingText, TTF_Font* font, Uint16 maxWidth) {

   // Let n = Count Number of Words in String
   Uint16 n = Dialog::getWordCount(remainingText);
   Uint16 l = 0;
   Uint16 r = n;
   Uint16 m = 0;

   std::string line = "";

   while (l < r) {

      m = (r - l)/2 + l + 1;

      line = Dialog::getUpToWordN(m, remainingText);

      // determine rendered width of m words
      int h = 0;
      int w = 0;
      TTF_SizeText(font, line.c_str(), &w, &h);

      // rendered width > dialog width
      if (w > maxWidth) {
         r = m - 1;
      } else {
         l = m + 1;
      }
   }

   remainingText = Dialog::getAfterWordN(m, remainingText);
   
   return line;
}

void Dialog::drawText() {

   // Black
   SDL_Color color = {0x00, 0x00, 0x00};

   TTF_Font* font = ResourceLoader::GetFont("Vera.ttf", 17);

   Uint16 margin = 10;

   // Determine the maximum number of lines which can be displayed in this
   // Dialog box..
   Uint16 fontHeight = TTF_FontHeight(font);
   Uint16 maxLines = (this->getHeight() - margin)/ fontHeight;

   // Stick a space on the end of the renderable text so that we can easily
   // count the number of words in the string.
   std::string remainingText = this->text + " ";

   // Render Each Line Onto the Dialog Box.
   Uint16 lineNum = 0;
   while (lineNum < maxLines && remainingText != "") {

      // Get the next line of output and chop it off the remaining text.
      Uint16 maxWidth = this->getWidth() - margin;
      std::string line = this->getNextLine(remainingText, font, maxWidth);

      // Build the text surface containing the given string.
      SDL_Surface* text_surface = TTF_RenderText_Solid(
           font
         , line.c_str()
         , color
      );

      // If the surface is not created successfully.
      if (text_surface == NULL) {
         LOG(INFO) << this->text.c_str();
         LOG(ERROR) << "Error creating text: " << TTF_GetError();
         exit(1);

      } else {

         // Create a destination rectangle based on the created text surface and
         // the position parameter.
         SDL_Rect r;
         r.w = text_surface->w;
         r.h = text_surface->h;
         r.x = margin;
         r.y = lineNum * fontHeight + margin;

         // Blit the text to the screen.
         SDL_BlitSurface(text_surface, NULL, this->tempSurf, &r);

      }

      lineNum++;

   }

   // TODO:
   // This method needs to return whatever it decided not to display due to
   // wrapping constraints.
}
