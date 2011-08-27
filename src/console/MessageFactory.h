/*****************************************************************************
 * Copyright (c) 2007 Russ Adams, Sean Eubanks, Asgard Contributors
 * This file is part of Asgard.
 * 
 * Asgard is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asgard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with Asgard; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/
#ifndef MESSAGE_FACTORY_H
#define MESSAGE_FACTORY_H

#include <string>
#include "Message.h"
#include "Drawable.h"
#include "MapObject.h"

class MessageFactory
{
   public:
      static void makeDisplayDrawable(Drawable *d, std::string layerName, int x, int y);
      static void makeLoadBoundingBox(int bbId);
      static void makeLoadDrawable(char *dName);
      static void makePrintString(const char* output);
      static void makeInstallMapObject(MapObject* mo, Drawable* d);
};

#endif // MESSAGE_FACTORY_H
