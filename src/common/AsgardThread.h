#ifndef ASGARD_THREAD_H
#define ASGARD_THREAD_H

#include <boost/thread/thread.hpp>
#include <boost/function.hpp>
#include "AsgardThreadState.h"

typedef boost::function<void()> ThreadDelegate;

class AsgardThread
{
public:
	AsgardThread();
	virtual ~AsgardThread();
	
	// Starts thread execution of the passed in delegate method
	void open(ThreadDelegate delegate);
	
	// Tells the thread to close down
	void close();
	
	// Provides status that the thread is in the process of closing
	bool isClosing();
	
	// If thread state is closed the thread should not be executing anymore.
	bool isClosed();

protected:
   // This is the method that executes the thread
   virtual void runThread();

private:
   boost::thread *thread;
   AsgardThreadState state;
   ThreadDelegate customRunThread;
};

#endif /*ASGARD_THREAD_H*/
