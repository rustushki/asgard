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
   // this mail by calling getMessage().  
   Message* getMessage();

   // Return the number of messages in the mailbox.
   int getNumMessages();

private:
   std::list<MailboxStorage*> messageQueue;
   boost::mutex queueMutex;
   MailboxSignal deliverMessage;
};

#endif /*MAILBOX_H*/
