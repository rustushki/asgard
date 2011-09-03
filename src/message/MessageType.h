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

#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

enum MessageType
{
   MESSAGE_TYPE_DISPLAY_DRAWABLE,
   MESSAGE_TYPE_LOAD_BOUNDING_BOX,
   MESSAGE_TYPE_LOAD_DRAWABLE,
   MESSAGE_TYPE_PRINT_STRING,
   MESSAGE_TYPE_INSTALL_MAP_OBJECT,
   MESSAGE_TYPE_MOVE_FOCUS_POINT,
   MESSAGE_TYPE_TRANSLATE_DRAWABLES_BY_OFFSET,
   MESSAGE_TYPE_COUNT
};

#endif //MESSAGE_TYPE_H
