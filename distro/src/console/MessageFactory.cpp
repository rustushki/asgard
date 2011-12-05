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

#include "MessageFactory.h"

void MessageFactory::makeDisplayDrawable(Drawable *d, std::string layerName, int x, int y)
{
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_DISPLAY_DRAWABLE;
   msg->data.displayDrawable.drawPtr = d;
   strcpy(msg->data.displayDrawable.layName, layerName.c_str());
   msg->data.displayDrawable.x = x;
   msg->data.displayDrawable.y = y;

   // Message should be picked up by Graphics Engine
   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeLoadBoundingBox(int x, int y)
{
   LOG(INFO) << "Making LoadBoundingBox Message: (" << x << ", " << y << ")";
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_LOAD_BOUNDING_BOX;
   msg->data.box.X = x;
   msg->data.box.Y = y;

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeLoadDrawable(char *dName)
{
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_LOAD_DRAWABLE;
   msg->data.loadDrawable.drawableName = dName;

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makePrintString(const char* output)
{
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_PRINT_STRING;
   msg->data.printString.output = new char[strlen(output)+1];
   strcpy(msg->data.printString.output, output);

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeInstallMapObject(MapObject* mo, Drawable* d)
{
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_INSTALL_MAP_OBJECT;
   msg->data.installMapObject.drawPtr = d;
   msg->data.installMapObject.mapObjectPtr = mo;

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeMoveFocusPoint(int x, int y)
{
   LOG(INFO) << "Making MoveFocusPoint Message: (" << x << ", " << y << ")";
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_MOVE_FOCUS_POINT;
   msg->data.box.X = x;
   msg->data.box.Y = y;

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeTranslateDrawablesByOffset(std::vector<std::string>* drawableNames, int x, int y) {
   LOG(INFO) << "Making TranslateDrawablesByOffset Message for Offset = " << x << ", " << y << ")";
   LOG(INFO) << "For these Drawables:";
   
   std::vector<std::string>::iterator dNameIter;
   for (dNameIter = drawableNames->begin(); dNameIter != drawableNames->end(); dNameIter++) {
      LOG(INFO) << (*dNameIter);
   }

   Message *msg = new Message();

   msg->header.type = MESSAGE_TYPE_TRANSLATE_DRAWABLES_BY_OFFSET;
   msg->data.translateDrawablesByOffset.drawableNames = drawableNames;
   msg->data.translateDrawablesByOffset.X = x;
   msg->data.translateDrawablesByOffset.Y = y;

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeUnloadDrawable(std::string drawableName) {
   LOG(INFO) << "Unloading Drawable " << drawableName;
   
   Message *msg = new Message();

   msg->header.type = MESSAGE_TYPE_UNLOAD_DRAWABLE;
   msg->data.unloadDrawable.drawableName = new std::string(drawableName);

   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}