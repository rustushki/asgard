#include <string>
#include <boost/bind.hpp>
#include <iostream>
#include "MessageRouter.h"
#include "SystemComponent.h"

SystemComponent::SystemComponent(std::string threadName)
{
   this->state = SYSTEM_COMPONENT_STATE_CREATED;
   this->connectMessageRouter();
   this->thread = new AsgardThread(threadName, &this->mailbox);
}

SystemComponent::~SystemComponent()
{
   delete this->thread;
}

bool SystemComponent::open()
{
   this->state = SYSTEM_COMPONENT_STATE_OPEN;

   this->mailbox.connect(boost::bind(&SystemComponent::notifyMessages, this));

   return true;
}

bool SystemComponent::close()
{
   this->state = SYSTEM_COMPONENT_STATE_CLOSED;

   return true;
}

bool SystemComponent::isOpen() const
{
   return (this->state == SYSTEM_COMPONENT_STATE_OPEN);
}

bool SystemComponent::isClosed() const
{
   return (this->state == SYSTEM_COMPONENT_STATE_CLOSED);
}

// WARNING:  Be wary of editing this routine as changes may trigger system-wide
// race conditions.
void SystemComponent::listen()
{

   bool messagesHandled = false;

   // If messages have arrived before the listening session begins OR since
   // the thread was woken at end of loop
   int numMessages = this->mailbox.getNumMessages();
   while (numMessages > 0)
   {
      // handle the message appropriately (if this component handles it)
      // false means message was discarded.
      messagesHandled |= this->interpretMessage(this->mailbox.getMessage());

      // re-evaluate each time.. more messages could have been added.
      numMessages = this->mailbox.getNumMessages();
   }
   
   // If messages were handled, this listening session is over.
   if (messagesHandled == true)
      return;
   
   // sleep until messages arrive
   this->thread->sleep();

   // otherwise, run listen again (done automatically)
}

void SystemComponent::notifyMessages()
{
   this->thread->wake();
}

void SystemComponent::connectMessageRouter()
{
   MessageRouter* mr = MessageRouter::getInstance();
   mr->connect(boost::bind(&Mailbox::addMessage,&this->mailbox,_1));
}


