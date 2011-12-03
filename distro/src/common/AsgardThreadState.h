#ifndef ASGARD_THREAD_STATE_H
#define ASGARD_THREAD_STATE_H

enum AsgardThreadState
{
   ASGARD_THREAD_STATE_OPEN,     // Thread has just been opened, not yet executing
   ASGARD_THREAD_STATE_ACTIVE,   // Thread is open and executing
   ASGARD_THREAD_STATE_CLOSE,    // Thread has been sent the close() command an is cleaning up
   ASGARD_THREAD_STATE_CLOSED,   // Thread has closed and execution has stopped
   ASGARD_THREAD_STATE_SLEEPING, // Thread is sleeping
   ASGARD_THREAD_STATE_COUNT
};

#endif // ASGARD_THREAD_STATE_H
