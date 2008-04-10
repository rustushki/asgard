#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include "SystemComponentState.h"

class SystemComponent
{
public:
   SystemComponent();
   
   virtual ~SystemComponent();
   
   // Should be inheriated and implemented by anyone who inherits
   // from this class.
   // This function should initialize all state variables and 
   // get the system component ready for use
   virtual bool open();
   
   // Should be inheriated and implemented by anyone who inherits
   // from this class.
   // This function should close down and cleanup anything setup
   // in the open function and get the component ready for 
   // destruction or re-opening
   virtual bool close();
   
   // Returns if the System Component is in an open state
   virtual bool isOpen();
   
   // Returns if the System Component is in a closed state
   virtual bool isClosed();
   
private:
   SystemComponentState state;
   
   // TODO: All system components need to contain a Mailbox and probably a
   //       thread of their own so they can communicate with the rest of 
   //       the system via the MessageRouter.
   //       Any class that wants to receive updates from this Mailbox
   //       will need to connect to that Mailbox.
   
   
};

#endif /*SYSTEM_COMPONENT_H*/
