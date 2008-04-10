#ifndef MAILBOX_H
#define MAILBOX_H

#include "Message.h"
#include <list>
#include <boost/thread/mutex.hpp>
#include <boost/signal.hpp>

struct MailboxStorage
{
   Message* msg;
   int getCount;
};
// TODO: PROBLEM!!!  The mail delivery notification will be called from the MessageRouter thread.
//       We do not want classes receiving mail from the mailbox to hijack the MessageRouter thread
//       for Message processing and we do not want getMessage calls to by asynchronious from different
//       threads (as I think I originally designed it) because currently getMessage will just return 
//       the front of the queue.  Mail delivery needs to be moved to a different thread that can be 
//       hijacked for message processing.  Mailbox needs it's own thread!
// NOTE: The above problem only applies to Mailboxes as they are used in System Components if multiple 
//       classes are attached to receive mailbox notifications.  One solution would be to just limit 
//       Mailboxes only to one connection and define that any class using a Mailbox must have it's own
//       thread... or that Mailboxes may only be used by System Components which must have a thread.
//       The MessageRouter also uses a Mailbox - we could also define a mailbox role (router or system
//       component) and have the Mailbox act according (this could also be acheived through subclassing).

class Mailbox
{
   typedef boost::signal<void ()> MailboxSignal;
   
public:
   Mailbox();
   
   virtual ~Mailbox();
   
   // Any class that wants to be informed of new mail
   // will need to register with the mailbox by calling
   // this connect method
   void connect(const MailboxSignal::slot_type& slot);
   
   // This function should only be called by the MessageRouter
   // to deliver a message to the mailbox.  Other users should
   // not use this.
   void addMessage(Message* message);
   
   // If a class has been notified of new mail they must retreive
   // this mail by calling this getMessage() call.  
   Message* getMessage();
   
private:
   std::list<MailboxStorage*> messageQueue;
   boost::mutex queueMutex;
   MailboxSignal deliverMessage;
   
};

#endif /*MAILBOX_H*/
