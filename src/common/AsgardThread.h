#ifndef ASGARD_THREAD_H
#define ASGARD_THREAD_H

#include <boost/thread/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>
#include "AsgardThreadState.h"
#include "Mailbox.h"

typedef boost::function<void()> ThreadDelegate;

class AsgardThread
{
public:
	AsgardThread(Mailbox* mb);
	virtual ~AsgardThread();
	
	// Starts thread execution of the passed in delegate method
	void open(ThreadDelegate delegate);
	
	// Tells the thread to close down
	void close();

   // Interrupts a thread, but only if it's sleeping.  Returns false if thread
   // was not interrupted.
   bool wake();

   // Is the thread currently sleeping.
   bool isSleeping();

	// Provides status that the thread is in the process of closing
	bool isClosing();
	
	// If thread state is closed the thread should not be executing anymore.
	bool isClosed();
   
   // Sleep for a duration of milliseconds.
   void sleep();

   char* name;

protected:
   // This is the method that executes the thread
   virtual void runThread();

private:

   boost::thread *thread;
   AsgardThreadState state;
   ThreadDelegate customRunThread;

   boost::mutex mut;
   boost::condition_variable untilMessagesArrive;
   Mailbox* mb;
};

#endif /*ASGARD_THREAD_H*/
