#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include "SystemComponentState.h"
#include "AsgardThread.h"
#include "Mailbox.h"

class SystemComponent
{
public:
   SystemComponent();
   
   virtual ~SystemComponent();
   
   // Should be inherited and implemented by anyone who inherits
   // from this class.
   // This function should initialize all state variables and 
   // get the system component ready for use.
   // Connect to Mailbox.
   virtual bool open();
   
   // Should be inherited and implemented by anyone who inherits
   // from this class.
   // This function should close down and cleanup anything setup
   // in the open function and get the component ready for 
   // destruction or re-opening
   virtual bool close();
   
   // Returns if the System Component is in an open state
   virtual bool isOpen();
   
   // Returns if the System Component is in a closed state
   virtual bool isClosed();

   // Should be inherited and implemented by anyone who inherits
   // from this class.
   // This function should retrieve a Message from the mailbox
   // handle it.
   virtual void handleMessage() = 0;
   
protected:
   // A thread for the SystemComponent to run in.
   AsgardThread thread;

   // A mailbox for receiving messages from the MessageRouter.
   Mailbox mailbox;

private:
   SystemComponentState state;
};

#endif /*SYSTEM_COMPONENT_H*/
