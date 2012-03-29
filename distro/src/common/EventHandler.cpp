#include "EventHandler.h"
#include "AsgardEvent.h"

/* -----------------------------------------------------------------------------
 * fireEvent - Put a user defined event on the SDL Event Queue.  The provided
 * eventCode signifies how the provided eventData should be interpretted by the
 * handler.
 */
void EventHandler::fireEvent(AsgardEvent eventCode, void* eventData) const {
   
   // Ensure that the AsgardEvent code is VALID.
   if (eventCode > ASGARDEVENT_COUNT || eventCode < 0) {
      LOG(FATAL) << "Invalid Event Code." << eventCode;
   }

   // It's OK to not allocate memory here.  SDL_PushEvent makes a copy of the
   // provided event.
   SDL_Event event;

   // This type signifies that the 'user' member of the SDL_Event is relevant.
   event.type = SDL_USEREVENT;

   // Set the EventCode to signify how data1 should be interpretted when
   // handling the event.
   event.user.code = eventCode;

   // Depending on the eventCode, we may end up using data2 in the future.  For
   // the moment, data1 should be sufficient.
   event.user.data1 = eventData;
   event.user.data2 = NULL;

   // Stick the event on the SDL Event Queue.
   SDL_PushEvent(&event);
}
