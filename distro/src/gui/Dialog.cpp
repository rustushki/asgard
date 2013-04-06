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

/* ------------------------------------------------------------------------------
 * getWordNPos - Find the character position of the first character following
 * word N of the provided string.
 */
int Dialog::getWordNPos(int wordN, std::string text) {
   if (wordN <= 0) {
      return 0;
   }

   size_t pos = text.find(" ", 0);

   while (wordN-- > 0 && pos != string::npos) {
      pos = text.find(" ", pos+1);
   }

   return pos;
}

/* ------------------------------------------------------------------------------
 * getWordCount - Count the words in the provided string.
 */
int Dialog::getWordCount(std::string text) {
   size_t pos = text.find(" ", 0);

   int count = 0;

   while (pos != string::npos) {
      count++;
      pos = text.find(" ", pos+1);
   }

   if (pos == string::npos) {
      count++;
   }

   return count;
}

/* ------------------------------------------------------------------------------
 * getUpToWordN - Get a substring from the beginning of the provided string up
 * to Word N of the string.
 */
std::string Dialog::getUpToWordN(int n, std::string text) {
   int pos = Dialog::getWordNPos(n-1, text);

   return text.substr(0, pos);
}

/* ------------------------------------------------------------------------------
 * getAfterWordN - Return the string following word N in the provided string.
 */
std::string Dialog::getAfterWordN(int n, std::string text) {
   size_t pos = Dialog::getWordNPos(n, text);

   // If there is no more string after word N, return the empty string.
   //
   // GOTCHA:
   // Be careful because string::npos == -1.  If we were to add 1 to
   // string::npos, we would get character 0 of the string.  That would cause
   // this method to effectively return the entire string.
   if (pos == string::npos) {
      return "";

   } else {
      return text.substr(pos+1);
   }
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

   remainingText = Dialog::getAfterWordN(r, remainingText);
   
   return line;
}

void Dialog::drawText() {

   // Black
   SDL_Color color = {0x33, 0x33, 0x33};

   TTF_Font* font = ResourceLoader::GetFont("Vera.ttf", 17);

   Uint16 margin = 10;

   // Determine the maximum number of lines which can be displayed in this
   // Dialog box..
   Uint16 fontHeight = TTF_FontHeight(font);
   Uint16 maxLines = (this->getHeight() - margin)/ fontHeight;

   // Stick a space on the end of the renderable text so that we can easily
   // count the number of words in the string.
   std::string remainingText = this->text;

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
