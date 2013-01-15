#include "Theme.h"

Theme::Theme(std::string themeName) {
   this->name = themeName;
}

SDL_Surface* Theme::buildElement(std::string elementName) {
   // Do something with element name.

   // TODO: Real work starts here.
   //

   // TODO: Optimize Theme by storing each theme element in an std::map.  This
   // method then looks up the element in tha map rather than rebuilding a new
   // SDL_Surface.
   //

   // Return SDL_Surface.
   return NULL;
}
