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

#include "QueryGenerator.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdio.h>

char* QueryGenerator::staticMapObject(int boundingBoxId)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.Height, ";
   qs += "mo.Width ";
   qs += "from BoundingBox bb ";
   qs += "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   qs += "where mo.BoundingBoxId = " + QueryGenerator::intToString(boundingBoxId) + " ";

   // TODO:
   // This is not ideal.
   // Instantiation of StaticMapObjects will need to be addressed.
   qs += "  and mo.MapObjectId not in ";
   qs += "     (select MapObjectId from Container) ";
   qs += "  and mo.MapObjectId not in ";
   qs += "     (select MapObjectId from NonPlayerCharacter) ";
   qs += "  and mo.MapObjectId not in ";
   qs += "     (select MapObjectId from Tiles);";

   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::nonPlayerCharacter(int boundingBoxId)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.Height, ";
   qs += "mo.Width, ";
   qs += "npc.Speed, ";
   qs += "mo.BoundingBoxId ";
   qs += "from BoundingBox bb ";
   qs += "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   qs += "inner join NonPlayerCharacter npc on npc.MapObjectId = mo.MapObjectId ";
   qs += "where mo.BoundingBoxId = " + QueryGenerator::intToString(boundingBoxId) + ";";
   
   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::nonPlayerCharacterPath(int mapObjectId)
{
   std::string qs;
   qs += "select ";
   qs += "npcp.MapObjectId, ";
   qs += "npcp.WC_X, ";
   qs += "npcp.WC_Y, ";
   qs += "npcp.PathIndex ";
   qs += "from NonPlayerCharacterPath npcp ";
   qs += "where npcp.MapObjectId = " + QueryGenerator::intToString(mapObjectId) + ";";

   return QueryGenerator::makeCStr(qs);
}
      
char* QueryGenerator::container(int boundingBoxId)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.Height, ";
   qs += "mo.Width, ";
   qs += "c.item0, ";
   qs += "c.item1, ";
   qs += "c.item2, ";
   qs += "c.item3, ";
   qs += "c.item4, ";
   qs += "c.item5, ";
   qs += "c.item6, ";
   qs += "c.item7, ";
   qs += "c.item8, ";
   qs += "c.item9, ";
   qs += "c.item10, ";
   qs += "c.item11, ";
   qs += "c.item12, ";
   qs += "c.item13, ";
   qs += "c.item14 ";
   qs += "from BoundingBox bb ";
   qs += "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   qs += "inner join Container c on c.MapObjectId = mo.MapObjectId ";
   qs += "where bb.BoundingBoxId = " + QueryGenerator::intToString(boundingBoxId) + ";";
   
   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::tile(int boundingBoxId)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.Height, ";
   qs += "mo.Width, ";
   qs += "t.tileType ";
   qs += "from BoundingBox bb ";
   qs += "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   qs += "inner join Tiles t on mo.MapObjectId = t.MapObjectId ";
   qs += "where bb.BoundingBoxId = " + QueryGenerator::intToString(boundingBoxId) + ";";
   
   return QueryGenerator::makeCStr(qs);
}
      
char* QueryGenerator::hardpoint(int mapObjectId)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "h.RelativeX, ";
   qs += "h.RelativeY, ";
   qs += "h.HardpointType, ";
   qs += "h.Width, ";
   qs += "h.Height, ";
   qs += "h.Radius ";
   qs += "from MapObject mo ";
   qs += "inner join Hardpoints h on h.MapObjectId = mo.MapObjectId ";
   qs += "where mo.MapObjectId = " + QueryGenerator::intToString(mapObjectId) + ";";
   
   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::drawable(std::string dName)
{
   std::string qs;
   qs += "select ";
   qs += "d.DrawableName, ";
   qs += "d.AnimationName, ";
   qs += "ss.SpriteSheetName, ";
   qs += "ss.NumColumns, ";
   qs += "ss.NumRows, ";
   qs += "a.Height, ";
   qs += "a.Width, ";
   qs += "a.StillCount, ";
   qs += "a.StillsPerSecond ";
   qs += "from Animation a ";
   qs += "inner join SpriteSheet ss on ss.SpriteSheetName = a.SpriteSheetName ";
   qs += "inner join Drawable d on d.AnimationName = a.AnimationName ";
   qs += "where d.DrawableName = '" + dName + "';";

   return QueryGenerator::makeCStr(qs);
}

// Convert an integer into a string.  We used to use std::stringstream for this
// purpose, but then discovered that std::stringstream is not threadsafe when
// compiled with g++.
std::string QueryGenerator::intToString(int bar)
{
   // All `integer` types are 11 characters wide maximally in MySQL.
   char* buf = new char[11];
   sprintf(buf, "%d", bar);
   return std::string(buf);
}

// Convert an std::string into a properly allocated char*
char* QueryGenerator::makeCStr(std::string qs)
{
   char* s = new char[strlen(qs.c_str())+1];
   strcpy(s, qs.c_str());   
   return s;
}
