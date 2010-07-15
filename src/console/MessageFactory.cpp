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

#include <cstring>
#include "MessageFactory.h"
#include "MessageRouter.h"

void MessageFactory::makeDisplayDrawable(Drawable *d, std::string layerName)
{
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_DISPLAY_DRAWABLE;
   msg->data.displayDrawable.drawPtr = d;
   strcpy(msg->data.displayDrawable.layName, layerName.c_str());

   // Message should be picked up by Graphics Engine
   MessageRouter* mr = MessageRouter::getInstance();
   mr->sendMessage(msg);
}

void MessageFactory::makeLoadBoundingBox(int bbId)
{
   Message *msg = new Message();
   msg->header.type = MESSAGE_TYPE_LOAD_BOUNDING_BOX;
   msg->data.box.boundingBoxId = bbId;

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
