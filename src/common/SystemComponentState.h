#ifndef SYSTEM_COMPONENT_STATE_H
#define SYSTEM_COMPONENT_STATE_H

enum SystemComponentState
{
   SYSTEM_COMPONENT_STATE_CREATED,  // The System Component has been constructed
   SYSTEM_COMPONENT_STATE_OPEN,     // The System Component has been initialized is ready
   SYSTEM_COMPONENT_STATE_CLOSED,   // The System Component has closed down and is ready to be deleted
   SYSTEM_COMPONENT_STATE_COUNT
};

#endif /*SYSTEM_COMPONENT_STATE_H*/
