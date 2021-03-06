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

#ifndef ANIMATION_INTERACTION_H
#define ANIMATION_INTERACTION_H

#include "externals.h"
#include "Interaction.h"

class AnimationInteraction : public Interaction
{
   public:
      AnimationInteraction(int priority, bool isHandledOnce, std::string animationName);
      ~AnimationInteraction();
      void setPriority(int priority);
      int getPriority() const;
      void setIsHandledOnce(bool isHandledOnce);
      bool getIsHandledOnce() const;
      void setAnimationName(std::string animationName);
      std::string getAnimationName() const;
      int getType() const;
   private:
      std::string animationName;
};

#endif //ANIMATION_INTERACTION_H
