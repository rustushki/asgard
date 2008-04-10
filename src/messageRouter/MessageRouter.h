#ifndef MESSAGE_ROUTER_H
#define MESSAGE_ROUTER_H

#include <boost/signal.hpp>
#include <boost/signals/trackable.hpp>
#include "AsgardThread.h"
#include "Mailbox.h"
#include "Message.h"

class MessageRouter : public boost::signals::trackable
{
   typedef boost::signal<void (Message*)> RouterSignal;
   
public:
   // Singleton Stuff
   static MessageRouter* getInstance();
   static void deleteInstance();
   
   // Connect to receive broadcasts from the Message Router.
   // Mailboxes should be the only classes to use this
   void connect(const RouterSignal::slot_type& slot);
 
   // Send a message through the Message Router to all
   // attached Mailboxes.  This is how any class in the system
   // should send a message through the system.
   void sendMessage(Message* message);
   
   // This is the slot used by the Mailbox
   // Informs us of a new mail
   void newMessageReceived();
   
   
private:
   MessageRouter();
   ~MessageRouter();

   // The method that runs the message router thread
   void runRouterThread();
   
   // Singleton instance
   static MessageRouter* messageRouter;
   
   RouterSignal routeMessage;
   
   AsgardThread routerThread;
   
   Mailbox mailbox;
};

#endif /*MESSAGE_ROUTER_H*/
