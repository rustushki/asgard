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
 ******************************************************************************/

#include "DrawableFactory.h"
#include "Drawable.h"
#include "QueryGenerator.h"
#include "DatabaseColumnMap.h"
#include "MessageFactory.h" //TEMP: for displaying drawable

int DrawableFactory::build(sqlite3 *db, std::string dName)
{
   Drawable *d;
   char *query, *sqliteErrorCode;

   // Create Drawable object
   d = new Drawable(dName);

   // Generate query for building Drawable
   query = QueryGenerator::drawable(dName);

   // Use query to process information from database for building Drawable
   if(sqlite3_exec(db, query, processRow, (void*)d, &sqliteErrorCode) != SQLITE_OK)
   {
      // Handle sqliteErrorCode?

      // Free memory held by error message
      sqlite3_free((void*)sqliteErrorCode);

      return -1;
   }

   delete query;

   // Send drawable to Graphics Engine for display
   MessageFactory::makeDisplayDrawable(d, "stageLayer");

   return 0;
}

int DrawableFactory::processRow(void *d, int columnCount, char **columnValue, char **columnName)
{
   Drawable *drawPtr = static_cast<Drawable*>(d);
   Animation *a;
   uint ssCols, ssRows, height, width, stillCount, sps;

   char dName[50];
   char aName[100];
   char ssName[50];

   // Extract data for creating Animation
   strcpy(dName, columnValue[ANIMATION_COLUMN_DRAWABLE_NAME]);
   strcpy(aName, columnValue[ANIMATION_COLUMN_ANIMATION_NAME]);
   strcpy(ssName, columnValue[ANIMATION_COLUMN_SPRITE_SHEET_NAME]);
   ssCols = atoi(columnValue[ANIMATION_COLUMN_SPRITE_SHEET_NUM_COLUMNS]);
   ssRows = atoi(columnValue[ANIMATION_COLUMN_SPRITE_SHEET_NUM_ROWS]);
   height = atoi(columnValue[ANIMATION_COLUMN_HEIGHT]);
   width = atoi(columnValue[ANIMATION_COLUMN_WIDTH]);
   stillCount = atoi(columnValue[ANIMATION_COLUMN_STILL_COUNT]);
   sps = atoi(columnValue[ANIMATION_COLUMN_STILLS_PER_SECOND]);
   
   // Create Animation
   a = new Animation(std::string(ssName), width, height, stillCount, sps, 
         ssRows, ssCols);
   
   // Load Animation into Drawable
   drawPtr->addAnimation(a, std::string(aName));
   
   return 0;
}

