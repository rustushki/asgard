#include "MessageRouter.h"
#include <boost/bind.hpp>
#include <iostream>

MessageRouter* MessageRouter::messageRouter = NULL;

MessageRouter* MessageRouter::getInstance()
{
   if(MessageRouter::messageRouter == NULL)
   {
      MessageRouter::messageRouter = new MessageRouter();
   }
   
   return MessageRouter::messageRouter;
}

void MessageRouter::deleteInstance()
{
   delete MessageRouter::messageRouter;
}

void MessageRouter::newMessageReceived()
{
   // Unlock the runRouterThread because new mail is here
   this->routerThread->wake();
}

MessageRouter::MessageRouter()
{
   this->routerThread = new AsgardThread(&this->mailbox);

   // Open the MessageRouter thread
   this->routerThread->open(boost::bind(&MessageRouter::runRouterThread, this));
   
   // Connect to the message router mailbox
   this->mailbox.connect(boost::bind(&MessageRouter::newMessageReceived, this));
}
 
MessageRouter::~MessageRouter()
{
   // If the thread isn't closed we need to close it
   if(!this->routerThread->isClosed())
   {
      this->routerThread->close();
   }

   delete this->routerThread;
}

void MessageRouter::connect(const RouterSignal::slot_type& slot)
{
   // Connect slot (should be a mailbox) to the routeMessage signal
   this->routeMessage.connect(slot);
}

void MessageRouter::sendMessage(Message* message)
{
   // Add to MessageRouter's mailbox
   this->mailbox.addMessage(message);
}

void MessageRouter::runRouterThread()
{
   while(1)
   {
      // Lock until new mail is received
      this->routerThread->sleep();
      // new mail has been received, call get mail
      Message* mail = this->mailbox.getMessage();
      
      // And route to attached mailboxes
      this->routeMessage(mail);
   }
}
