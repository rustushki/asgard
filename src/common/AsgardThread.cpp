#include "AsgardThread.h"
#include <boost/bind.hpp>

#include <iostream>

AsgardThread::AsgardThread(std::string name, Mailbox* mb)
{
   this->state = ASGARD_THREAD_STATE_CLOSED;
   this->mb = mb;
   this->name = name;
}

AsgardThread::~AsgardThread()
{
   if(!this->isClosed())
      this->close();
}

void AsgardThread::open(ThreadDelegate delegate)
{
   this->state = ASGARD_THREAD_STATE_OPEN;
   boost::function<void()> runThreadPtr = boost::bind(&AsgardThread::runThread, this);
   this->customRunThread = delegate;
   this->thread = new boost::thread(runThreadPtr);
}

void AsgardThread::close()
{
   this->state = ASGARD_THREAD_STATE_CLOSE;
   this->thread->join(); // wait for thread to close
   delete this->thread;
   this->state = ASGARD_THREAD_STATE_CLOSED;
}

bool AsgardThread::wake()
{
   if (this->isSleeping())
   {
      this->state = ASGARD_THREAD_STATE_OPEN;
      this->untilMessagesArrive.notify_all();
      return true;
   }

   return false;
}

bool AsgardThread::isClosing()
{
   return (this->state == ASGARD_THREAD_STATE_CLOSE);
}

bool AsgardThread::isClosed()
{
   return (this->state == ASGARD_THREAD_STATE_CLOSED);
}

bool AsgardThread::isSleeping()
{
   return (this->state == ASGARD_THREAD_STATE_SLEEPING);
}

void AsgardThread::sleep()
{
   boost::unique_lock<boost::mutex> lock(this->mut);
   this->state = ASGARD_THREAD_STATE_SLEEPING;
   if (this->mb->getNumMessages() == 0)
      this->untilMessagesArrive.wait(lock);
}

void AsgardThread::runThread()
{
   while(!this->isClosing())
   {
      if(this->state == ASGARD_THREAD_STATE_OPEN)
         this->state = ASGARD_THREAD_STATE_ACTIVE;
      
      // Call some method to execute custom thread code.
      this->customRunThread();
   }
}

std::string AsgardThread::getName()
{
   return this->name;
}
