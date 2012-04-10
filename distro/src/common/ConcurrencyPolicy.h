#ifndef CONCURRENCY_POLICY_H
#define CONCURRENCY_POLICY_H

enum ConcurrencyPolicy {

	// Allow multiple Event Handling Threads to run concurrently.
	  CONCURRENCY_POLICY_CONCURRENT
	
	// Block future Event Handling Threads from starting for a given Event Type
	// if one thread for such an Event Type is already running.  Requests to
	// start new Event Handling Threads will then "queue" up and be started
	// first come first serve.
	, CONCURRENCY_POLICY_BLOCK

	// If an Event is currently being handled in an Event Handling Thread, that
	// event is signal to come to a stopping point so that the new Event may
	// start a new Event Handling Thread (presumably with different
	// parameters).
	, CONCURRENCY_POLICY_OVERRIDE

	// Only one Event Handling Thread may be started for an Event.  All
	// subsequent events are cancelled.
	, CONCURRENCY_POLICY_CANCEL

	// Here to assist in iterating over concurrency policies.
	, CONCURRENCY_POLICY_COUNT
};

#endif//CONCURRENCY_POLICY_H
