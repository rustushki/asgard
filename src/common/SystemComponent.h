#ifndef SYSTEM_COMPONENT_H
#define SYSTEM_COMPONENT_H

#include "externals.h"
#include "SystemComponentState.h"
#include "AsgardThread.h"
#include "Mailbox.h"
#include "MessageRouter.h"

struct Message;

class SystemComponent
{
public:
   SystemComponent(std::string threadName);
   
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
   virtual bool isOpen() const;
   
   // Returns if the System Component is in a closed state
   virtual bool isClosed() const;

   // Block until messages arrive from the MessageRouter, or for a certain
   // amount of milliseconds.
   void listen();
   void listen(uint waitUntilMS);

   // Signals SystemComponent thread when a new message is detected.
   // Only MessageRouter should use this.
   void notifyMessages();

protected:
   // A thread for the SystemComponent to run in.
   AsgardThread* thread;
   
   // Override to interpet received messages.
   virtual bool interpretMessage(Message* message) = 0;
   
private:
   SystemComponentState state;

   // A mailbox for receiving messages from the MessageRouter.
   Mailbox mailbox;

   // Connect mailbox to the MessageRouter for receiving messages from it.
   void connectMessageRouter();
   
};

#endif /*SYSTEM_COMPONENT_H*/
