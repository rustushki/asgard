#include "AsgardThread.h"
#include <boost/bind.hpp>

#include <iostream>

AsgardThread::AsgardThread()
{
   this->state = ASGARD_THREAD_STATE_CLOSED;
}

AsgardThread::~AsgardThread()
{
   if(!this->isClosed())
   {
      this->close();
   }
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
   this->thread->join(); // what for thread to close
   delete this->thread;
   this->state = ASGARD_THREAD_STATE_CLOSED;
}

bool AsgardThread::isClosing()
{
   return (this->state == ASGARD_THREAD_STATE_CLOSE);
}

bool AsgardThread::isClosed()
{
   return (this->state == ASGARD_THREAD_STATE_CLOSED);
}

void AsgardThread::runThread()
{
   while(!this->isClosing())
   {
      if(this->state == ASGARD_THREAD_STATE_OPEN) this->state = ASGARD_THREAD_STATE_ACTIVE;
      
      // Call some method to execute custom thread code.
      this->customRunThread();
   }
}