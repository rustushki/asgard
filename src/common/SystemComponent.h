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
   
   // Should be inherited and implemented by anyone who inherits from this
   // class.  This function should initialize all state variables and get the
   // system component ready for use. Connect to Mailbox.
   virtual bool open();
   
   // Should be inherited and implemented by anyone who inherits from this
   // class. This function should close down and cleanup anything setup in the
   // open function and get the component ready for destruction or re-opening
   virtual bool close();
   
   // Returns if the System Component is in an open state
   virtual bool isOpen();
   
   // Returns if the System Component is in a closed state
   virtual bool isClosed();

   // Sleep until messages arrive from the MessageRouter.
   void listen();

   // Wakes up the SystemComponent thread when a new message is detected.
   void notifyMessages();

   // A mailbox for receiving messages from the MessageRouter.
   // Should this be public?
   Mailbox mailbox;

protected:
   // A thread for the SystemComponent to run in.
   AsgardThread* thread;
   
   // Override to interpet received messages.
   virtual bool interpretMessage(Message* message) = 0;

private:
   SystemComponentState state;

   // Connect mailbox to the MessageRouter for receiving messages from it.
   void connectMessageRouter();
};

#endif /*SYSTEM_COMPONENT_H*/
