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

AnimationInteraction::AnimationInteraction(int priority, std::string animationName)
{
   this->priority = priority;
   this->animationName = animationName;
}

AnimationInteraction::~AnimationInteraction()
{

}

void Animation::setPriority(int priority)
{
   this->priority = priority;
}

int Animation::getPriority() const
{
   return this->priority;
}

void Animation::setAnimationName(std::string animationName)
{
   this->animationName = animationName;
}

std::string Animation::getAnimationName() const
{
   return this->animationName;
}
