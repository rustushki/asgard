#ifndef THEME_H
#define THEME_H

#include <string>
#include <SDL/SDL.h>

#include "ResourceLoader.h"


/*
 * Basenames for image files which contain theme elements.
 *	Box Corners:        tl tr bl br
 *	Box Edges:          bh bw (i.e. border height and border width)
 *	Box Background:     bg
 *	Menu Cursor:        cursor
 *
 */

class Theme {
	
public:
   Theme(std::string themeName);

   // Build Drawable for associated with the special string provided.
   std::shared_ptr<SDL_Surface> buildElement(std::string elementName);

private:

   // This name is used to construct the path to the theme resource elements.
   std::string name;

};

#endif//THEME_H
