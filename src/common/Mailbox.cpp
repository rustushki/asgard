#include "Mailbox.h"
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/signal.hpp>

Mailbox::Mailbox()
{
}
   
Mailbox::~Mailbox()
{
   
}

void Mailbox::connect(const MailboxSignal::slot_type& slot)
{
   // Connect a signal to the boost slot so that when we receive
   this->deliverMessage.connect(slot);
}
   
void Mailbox::addMessage(Message* message)
{
   // Entering a critical section
   boost::mutex::scoped_lock scopedLock(this->queueMutex);
   
   // Create a new entry in the mailbox queue
   MailboxStorage* newEntry = new MailboxStorage();
   
   newEntry->msg = message;
   newEntry->getCount = 0;
   
   this->messageQueue.push_back(newEntry);
   
   this->deliverMessage();
}
   
Message* Mailbox::getMessage()
{
   // Entering a critical section
   boost::mutex::scoped_lock scopedLock(this->queueMutex);
   
   Message *msgToReturn = NULL;
   
   // If the queue is not empty
   if(this->messageQueue.begin() != this->messageQueue.end())
   {
      unsigned int currentGetCount = 0;

      // Grab the front of the queue
      std::list<MailboxStorage*>::iterator frontOfQueue = this->messageQueue.begin();
      
      MailboxStorage* front = static_cast<MailboxStorage*>(*frontOfQueue);
      
      currentGetCount = ++front->getCount;
      
      // Save the message to return
      msgToReturn = front->msg;
      
      // If this message has been received by all slots
      if(currentGetCount >= this->deliverMessage.num_slots())
      {
         delete front;
         
         this->messageQueue.pop_front();
      }
   }

   return msgToReturn;
}

int Mailbox::getNumMessages()
{
   // Entering a critical section
   boost::mutex::scoped_lock scopedLock(this->queueMutex);

   return this->messageQueue.size();
}
