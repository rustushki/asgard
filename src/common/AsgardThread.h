#ifndef ASGARD_THREAD_H
#define ASGARD_THREAD_H

#include "externals.h"
#include "AsgardThreadState.h"
#include "Mailbox.h"

typedef boost::function<void()> ThreadDelegate;

class AsgardThread
{
public:
   AsgardThread(std::string name, Mailbox* mb);
   virtual ~AsgardThread();
   
   // Starts thread execution of the passed in delegate method
   void open(ThreadDelegate delegate);
   
   // Tells the thread to close down
   void close();

   // Interrupts a thread, but only if it's sleeping.  Returns false if thread
   // was not interrupted.
   bool wake();

   // Put the thread to sleep.
   void sleep();

   // Is the thread currently sleeping.
   bool isSleeping() const;

   // Provides status that the thread is in the process of closing
   bool isClosing() const;
   
   // If thread state is closed the thread should not be executing anymore.
   bool isClosed() const;
   
   // Retrieve the thread's name. (for debugging purposes)
   std::string getName() const;

protected:
   // This is the method that executes the thread
   virtual void runThread();

private:

   boost::thread *thread;
   AsgardThreadState state;
   ThreadDelegate customRunThread;

   boost::mutex sleepMutex;
   boost::condition_variable untilMessagesArrive;

   // Pointer to AsgardThread's associated SystemComponent's Mailbox.
   // We need this to do a last minute check that there are no messages before
   // the thread goes to sleep.
   Mailbox* mb;

   // Thread's name
   std::string name;

};

#endif /*ASGARD_THREAD_H*/
