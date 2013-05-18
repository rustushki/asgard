#include "Theme.h"

Theme::Theme(std::string themeName) {
   this->name = themeName;
}

SDL_Surface* Theme::buildElement(std::string elementName) {

   std::string path  = "gui/";
               path += this->name + "/";
               path += elementName + ".png";

   // Return SDL_Surface.
   return ResourceLoader::GetInstance()->loadSDLSurface(path);

}
