#include "MessageFactory.h"
#include "../message/Message.h"

void MessageFactory::makeLoadBoundingBox(int bbId)
{
   Message m;
   m.data.box.boundingBoxId= bbId;

   // TODO:
   // Do something with constructed
   // message.
   // ...
}
