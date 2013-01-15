#ifndef THEME_H
#define THEME_H

#include <string>
#include <SDL/SDL.h>


/*
 * Basenames for image files which contain theme elements.
 *	Box Corners:        tl tr bl br
 *	Box Edges:          re le te be
 *	Box Background:     tile
 *	Menu Cursor:        cursor
 *
 */

class Theme {
	
public:
   Theme(std::string themeName);

   // Build Drawable for associated with the special string provided.
   SDL_Surface* buildElement(std::string elementName);

private:

   // This name is used to construct the path to the theme resource elements.
   std::string name;

};

#endif//THEME_H
