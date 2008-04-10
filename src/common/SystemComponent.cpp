#include "SystemComponent.h"

SystemComponent::SystemComponent()
{
   this->state = SYSTEM_COMPONENT_STATE_CREATED;
}

SystemComponent::~SystemComponent()
{
}

bool SystemComponent::open()
{
   this->state = SYSTEM_COMPONENT_STATE_OPEN;
   
   return true;
}

bool SystemComponent::close()
{
   this->state = SYSTEM_COMPONENT_STATE_CLOSED;
   
   return true;
}

bool SystemComponent::isOpen()
{
   return (this->state == SYSTEM_COMPONENT_STATE_OPEN);
}

bool SystemComponent::isClosed()
{
   return (this->state == SYSTEM_COMPONENT_STATE_CLOSED);
}