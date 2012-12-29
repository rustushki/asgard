/*****************************************************************************
 * Copyright (c) 2006 Russ Adams, Sean Eubanks, Asgard Contributors
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

#ifndef INTERACTION_H
#define INTERACTION_H

class Interaction
{
   public:
      virtual void setPriority(int priority) = 0;
      virtual int getPriority() const = 0;
      virtual void setIsHandledOnce(bool isHandledOnce) = 0;
      virtual bool isHandledOnce() const = 0;
      virtual bool handle() = 0;
   protected:
      int priority;
      bool isHandledOnce;
};

enum INTERACTION_TYPE
{
   INTERACTION_TYPE_ANIMATION,
   INTERACTION_TYPE_ITEM,
   INTERACTION_TYPE_DIALOG,
   INTERACTION_TYPE_COUNT
};

#endif //INTERACTION_H
