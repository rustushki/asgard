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

#include "QueryGenerator.h"

char* QueryGenerator::mapObject(int boxX, int boxY)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mot.DrawableName ";
   qs += "from MapObject mo ";
   qs += "inner join MapObjectType mot on mo.MapObjectTypeId = mot.MapObjectTypeId ";
   qs += "where mo.WC_X  > " + QueryGenerator::intToString(boxX);
   qs += "  and mo.WC_X <= " + QueryGenerator::intToString(boxX + Map::BOUNDING_BOX_SIZE);
   qs += "  and mo.WC_Y  > " + QueryGenerator::intToString(boxY);
   qs += "  and mo.WC_Y <= " + QueryGenerator::intToString(boxY + Map::BOUNDING_BOX_SIZE);

   // TODO:
   // This is not ideal.
   // Instantiation of MapObjects will need to be addressed.
   qs += "  and mo.MapObjectId not in ";
   qs += "     (select MapObjectId from Container) ";
   qs += "  and mo.MapObjectId not in ";
   qs += "     (select MapObjectId from NonPlayerCharacter) ";
   qs += "  and mo.MapObjectId not in ";
   qs += "     (select MapObjectId from Tiles);";

   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::nonPlayerCharacter(int boxX, int boxY)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.DrawableName, ";
   qs += "npc.Speed, ";
   qs += "from MapObject mo ";
   qs += "inner join NonPlayerCharacter npc on npc.MapObjectId = mo.MapObjectId ";
   qs += "where mo.WC_X  > " + QueryGenerator::intToString(boxX);
   qs += "  and mo.WC_X <= " + QueryGenerator::intToString(boxX + Map::BOUNDING_BOX_SIZE);
   qs += "  and mo.WC_Y  > " + QueryGenerator::intToString(boxY);
   qs += "  and mo.WC_Y <= " + QueryGenerator::intToString(boxY + Map::BOUNDING_BOX_SIZE);
   
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
      
char* QueryGenerator::container(int boxX, int boxY)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.DrawableName, ";
   qs += "from MapObject mo ";
   qs += "inner join Container c on c.MapObjectId = mo.MapObjectId ";
   qs += "where mo.WC_X  > " + QueryGenerator::intToString(boxX);
   qs += "  and mo.WC_X <= " + QueryGenerator::intToString(boxX + Map::BOUNDING_BOX_SIZE);
   qs += "  and mo.WC_Y  > " + QueryGenerator::intToString(boxY);
   qs += "  and mo.WC_Y <= " + QueryGenerator::intToString(boxY + Map::BOUNDING_BOX_SIZE);
   
   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::tile(int boxX, int boxY)
{
   std::string qs;
   qs += "select ";
   qs += "mo.MapObjectId, ";
   qs += "mo.WC_X, ";
   qs += "mo.WC_Y, ";
   qs += "mo.DrawableName, ";
   qs += "t.tileType ";
   qs += "from MapObject mo ";
   qs += "inner join Tiles t on mo.MapObjectId = t.MapObjectId ";
   qs += "where mo.WC_X  > " + QueryGenerator::intToString(boxX);
   qs += "  and mo.WC_X <= " + QueryGenerator::intToString(boxX + Map::BOUNDING_BOX_SIZE);
   qs += "  and mo.WC_Y  > " + QueryGenerator::intToString(boxY);
   qs += "  and mo.WC_Y <= " + QueryGenerator::intToString(boxY + Map::BOUNDING_BOX_SIZE);
   
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
   qs += "inner join MapObjectType mot on mo.MapObjectTypeId = mot.MapObjectTypeId ";
   qs += "inner join Hardpoints h on h.MapObjectTypeId = mot.MapObjectTypeId ";
   qs += "where mo.MapObjectId = " + QueryGenerator::intToString(mapObjectId) + ";";
   
   return QueryGenerator::makeCStr(qs);
}

char* QueryGenerator::animationInteraction(int mapObjectId, int interactionType)
{
   std::string qs;
   qs += "select ";
   qs += "i.Priority, ";
   qs += "i.AnimationName ";
   qs += "from Interaction i ";
   qs += "where i.MapObjectId = " + QueryGenerator::intToString(mapObjectId);
   qs += " and i.InteractionType = " + QueryGenerator::intToString(interactionType) + ";";
}

char* QueryGenerator::itemInteraction(int mapObjectId, int interactionType)
{
   std::string qs;
   qs += "select ";
   qs += "i.Priority, ";
   qs += "it.ItemName ";
   qs += "from Interaction i ";
   qs += "inner join Item it on i.ItemId = it.ItemId ";
   qs += "where i.MapObjectId = " + QueryGenerator::intToString(mapObjectId);
   qs += " and i.InteractionType = " + QueryGenerator::intToString(interactionType) + ";";
}

char* QueryGenerator::dialogInteraction(int mapObjectId, int interactionType)
{
   std::string qs;
   qs += "select ";
   qs += "i.Priority, ";
   qs += "d.Quote ";
   qs += "from Interaction i ";
   qs += "inner join Dialog d on i.DialogId = d.DialogId ";
   qs += "where i.MapObjectId = " + QueryGenerator::intToString(mapObjectId);
   qs += " and i.InteractionType = " + QueryGenerator::intToString(interactionType) + ";";
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
   std::string str = std::string(buf);
   delete[] buf;
   return str;
}

// Convert an std::string into a properly allocated char*
char* QueryGenerator::makeCStr(std::string qs)
{
   char* s = new char[strlen(qs.c_str())+1];
   strcpy(s, qs.c_str());   
   return s;
}
