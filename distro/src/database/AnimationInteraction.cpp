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

#include "AnimationInteraction.h"

AnimationInteraction::AnimationInteraction(int priority, bool isHandledOnce, std::string animationName)
{
   this->priority = priority;
   this->isHandledOnce = isHandledOnce;
   this->animationName = animationName;
}

AnimationInteraction::~AnimationInteraction()
{

}

void AnimationInteraction::setPriority(int priority)
{
   this->priority = priority;
}

int AnimationInteraction::getPriority() const
{
   return this->priority;
}

void AnimationInteraction::setIsHandledOnce(bool isHandledOnce)
{
   this->isHandledOnce = isHandledOnce;
}

bool AnimationInteraction::getIsHandledOnce() const
{
   return this->isHandledOnce;
}

void AnimationInteraction::setAnimationName(std::string animationName)
{
   this->animationName = animationName;
}

std::string AnimationInteraction::getAnimationName() const
{
   return this->animationName;
}

int AnimationInteraction::getType() const
{
   return INTERACTION_TYPE_ANIMATION;
}
