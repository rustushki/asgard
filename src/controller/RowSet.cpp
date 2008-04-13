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

#include "RowSet.h"
#include <sqlite3.h>
#include <cstring>

RowSet::RowSet()
{
   table = NULL;
   rowCount = 0;
   colCount = 0;
   errorMsg = "";
}


int RowSet::select(sqlite3 * db, const char* query)
{
   char queryCpy[2048];
   int rc;
   //char* error;

   strcpy(queryCpy,query);

   rc = sqlite3_get_table(
         db, 
         queryCpy, 
         &(this->table), 
         &(this->rowCount), 
         &(this->colCount), 
         0);
         //&error);

   //this->errorMsg = error;

   return rc;
}


const char* RowSet::getColumnValue(int row, int column)
{
   char* columnValue;

   columnValue = table[(row + 1) * colCount + column];

   return columnValue;

}


int RowSet::getRowCount()
{
   return this->rowCount;
}


int RowSet::getColCount()
{
   return this->colCount;

}


std::string RowSet::getError()
{
   std::string * error = new std::string(this->errorMsg);

   return *error;

}


RowSet::~RowSet()
{
   if (table != NULL)
   {
      sqlite3_free(table);
   }
}
