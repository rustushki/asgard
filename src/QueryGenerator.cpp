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

char* QueryGenerator::staticMapObject(int boundingBoxId)
{
   std::stringstream queryStream;
   std::string       query;
   char* cStr = new char[2048];
   
   queryStream << "select ";
   queryStream << "mo.MapObjectId, ";
   queryStream << "mo.WC_X, ";
   queryStream << "mo.WC_Y, ";
   queryStream << "mo.Height, ";
   queryStream << "mo.Width ";
   queryStream << "from BoundingBox bb ";
   queryStream << "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   queryStream << "where mo.BoundingBoxId = " << boundingBoxId << " ";

   // TODO:
   // This is not ideal.
   // Instantiation of StaticMapObjects will need to be addressed.
   queryStream << "  and mo.MapObjectId not in ";
   queryStream << "     (select MapObjectId from Container) ";
   queryStream << "  and mo.MapObjectId not in ";
   queryStream << "     (select MapObjectId from NonPlayerCharacter) ";
   queryStream << "  and mo.MapObjectId not in ";
   queryStream << "     (select MapObjectId from Tiles);";

   
   query = queryStream.str();
   strcpy(cStr,query.c_str());
   return cStr;
}

char* QueryGenerator::nonPlayerCharacter(int boundingBoxId)
{
   std::stringstream queryStream;
   std::string       query;
   char* cStr = new char[2048];
   
   queryStream << "select ";
   queryStream << "mo.MapObjectId, ";
   queryStream << "mo.WC_X, ";
   queryStream << "mo.WC_Y, ";
   queryStream << "mo.Height, ";
   queryStream << "mo.Width, ";
   queryStream << "npc.Speed, ";
   queryStream << "mo.BoundingBoxId ";
   queryStream << "from BoundingBox bb ";
   queryStream << "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   queryStream << "inner join NonPlayerCharacter npc on npc.MapObjectId = mo.MapObjectId ";
   queryStream << "where mo.BoundingBoxId = " << boundingBoxId << ";";
   
   query = queryStream.str();
   
   strcpy(cStr,query.c_str());
   return cStr;
}

char* QueryGenerator::nonPlayerCharacterPath(int mapObjectId)
{
   std::stringstream queryStream;
   std::string       query;
   char* cStr = new char[2048];
   
   queryStream << "select ";
   queryStream << "npcp.MapObjectId, ";
   queryStream << "npcp.WC_X, ";
   queryStream << "npcp.WC_Y, ";
   queryStream << "npcp.PathIndex ";
   queryStream << "from NonPlayerCharacterPath npcp ";
   queryStream << "where npcp.MapObjectId = " << mapObjectId << ";";

   query = queryStream.str();
   
   strcpy(cStr,query.c_str());
   return cStr;
}
      
char* QueryGenerator::container(int boundingBoxId)
{
   std::stringstream queryStream;
   std::string       query;
   char* cStr = new char[2048];
   
   queryStream << "select ";
   queryStream << "mo.MapObjectId, ";
   queryStream << "mo.WC_X, ";
   queryStream << "mo.WC_Y, ";
   queryStream << "mo.Height, ";
   queryStream << "mo.Width, ";
   queryStream << "c.item0, ";
   queryStream << "c.item1, ";
   queryStream << "c.item2, ";
   queryStream << "c.item3, ";
   queryStream << "c.item4, ";
   queryStream << "c.item5, ";
   queryStream << "c.item6, ";
   queryStream << "c.item7, ";
   queryStream << "c.item8, ";
   queryStream << "c.item9, ";
   queryStream << "c.item10, ";
   queryStream << "c.item11, ";
   queryStream << "c.item12, ";
   queryStream << "c.item13, ";
   queryStream << "c.item14 ";
   queryStream << "from BoundingBox bb ";
   queryStream << "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   queryStream << "inner join Container c on c.MapObjectId = mo.MapObjectId ";
   queryStream << "where bb.BoundingBoxId = " << boundingBoxId << ";";
   
   query = queryStream.str();
   
   strcpy(cStr,query.c_str());
   return cStr;
}

char* QueryGenerator::tile(int boundingBoxId)
{
   std::stringstream queryStream;
   std::string       query;
   char* cStr = new char[2048];
   
   queryStream << "select ";
   queryStream << "mo.MapObjectId, ";
   queryStream << "mo.WC_X, ";
   queryStream << "mo.WC_Y, ";
   queryStream << "mo.Height, ";
   queryStream << "mo.Width, ";
   queryStream << "t.tileType ";
   queryStream << "from BoundingBox bb ";
   queryStream << "inner join MapObject mo on mo.BoundingBoxId = bb.BoundingBoxId ";
   queryStream << "inner join Tiles t on mo.MapObjectId = t.MapObjectId ";
   queryStream << "where bb.BoundingBoxId = " << boundingBoxId << ";";
   
   query = queryStream.str();
   
   strcpy(cStr,query.c_str());
   return cStr;
}
      
char* QueryGenerator::hardpoint(int mapObjectId)
{
   std::stringstream queryStream;
   std::string       query;
   char* cStr = new char[2048];
   
   queryStream << "select ";
   queryStream << "mo.MapObjectId, ";
   queryStream << "h.RelativeX, ";
   queryStream << "h.RelativeY, ";
   queryStream << "h.HardpointType, ";
   queryStream << "h.Width, ";
   queryStream << "h.Height, ";
   queryStream << "h.Radius ";
   queryStream << "from MapObject mo ";
   queryStream << "inner join Hardpoints h on h.MapObjectId = mo.MapObjectId ";
   queryStream << "where mo.MapObjectId = " << mapObjectId << ";";
   
   query = queryStream.str();
   
   strcpy(cStr,query.c_str());
   return cStr;
}

