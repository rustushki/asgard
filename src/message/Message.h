/*****************************************************************************
 * Copyright (c) 2011 Russ Adams, Sean Eubanks, Asgard Contributors
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

#ifndef MESSAGE_H
#define MESSAGE_H

#include "MessageHeader.h"
#include "DisplayDrawable.h"
#include "LoadBoundingBox.h"
#include "LoadDrawable.h"
#include "PrintString.h"
#include "InstallMapObject.h"
#include "MoveFocusPoint.h"
#include "TranslateDrawablesByOffset.h"

struct Message
{
   MessageHeader header;
   union
   {
      DisplayDrawable displayDrawable;
      LoadBoundingBox box;
      LoadDrawable loadDrawable;
      PrintString printString;
      InstallMapObject installMapObject;
      MoveFocusPoint moveFocusPoint;
      TranslateDrawablesByOffset translateDrawablesByOffset;
   } data;
};

#endif //MESSAGE_H
