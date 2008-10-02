#include <boost/bind.hpp>
#include <iostream>
#include "MessageRouter.h"
#include "SystemComponent.h"

SystemComponent::SystemComponent()
{
   this->state = SYSTEM_COMPONENT_STATE_CREATED;
   this->connectMessageRouter();
   this->thread = new AsgardThread(&this->mailbox);
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

bool SystemComponent::isOpen()
{
   return (this->state == SYSTEM_COMPONENT_STATE_OPEN);
}

bool SystemComponent::isClosed()
{
   return (this->state == SYSTEM_COMPONENT_STATE_CLOSED);
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

void SystemComponent::listen()
{
   bool messagesHandled = false;
   while (1)
   {
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
         break;

      //std::cout << this->thread->name << " sleeps.." << std::endl;

      // sleep until messages arrive
      this->thread->sleep();

      //std::cout << this->thread->name << " woken!" << std::endl;

   }
}
