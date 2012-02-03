/*****************************************************************************
 * Copyright (c) 2012 Russ Adams, Sean Eubanks, Asgard Contributors
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
 
#ifndef QUERY_GENERATOR_H
#define QUERY_GENERATOR_H

#include "externals.h"
#include "Map.h"

class QueryGenerator
{
   public:
      static char* mapObject(int boxX, int boxY);
      static char* nonPlayerCharacter(int boxX, int boxY);
      static char* nonPlayerCharacterPath(int mapObjectId);
      static char* container(int boxX, int boxY);
      static char* tile(int boxX, int boxY);
      static char* hardpoint(int mapObjectId);
      static char* drawable(std::string dName);
   private:
      static char* makeCStr(std::string s);
      static std::string intToString(int b);
};

#endif // QUERY_GENERATOR_H
