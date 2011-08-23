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
#include "QueryGenerator.h"
#include "DatabaseColumnMap.h"
#include "MessageFactory.h" //TEMP: for displaying drawable

Drawable* DrawableFactory::build(sqlite3 *db, std::string dName)
{
   Drawable *d;
   Animation *a;
   char *query;

   // Create Drawable object
   d = new Drawable(dName);

   // Generate query for building Drawable
   query = QueryGenerator::drawable(dName);

   // Prepare SQLite3 statement
   sqlite3_stmt *stmt = 0;
   sqlite3_prepare_v2(db, query, -1, &stmt, 0);

   // Load Drawable object with Animations
   while (sqlite3_step(stmt) == SQLITE_ROW)
   {
      a = new Animation((const char *)sqlite3_column_text(stmt, ANIMATION_COLUMN_SPRITE_SHEET_NAME), sqlite3_column_int(stmt, ANIMATION_COLUMN_WIDTH), sqlite3_column_int(stmt, ANIMATION_COLUMN_HEIGHT), sqlite3_column_int(stmt, ANIMATION_COLUMN_STILL_COUNT), sqlite3_column_int(stmt, ANIMATION_COLUMN_STILLS_PER_SECOND), sqlite3_column_int(stmt, ANIMATION_COLUMN_SPRITE_SHEET_NUM_ROWS), sqlite3_column_int(stmt, ANIMATION_COLUMN_SPRITE_SHEET_NUM_COLUMNS));
      d->addAnimation(a, (const char *)sqlite3_column_text(stmt, ANIMATION_COLUMN_ANIMATION_NAME));
   }

   // Clean up
   sqlite3_finalize(stmt);
   sqlite3_close(db);
   delete [] query;

   return d;
}
