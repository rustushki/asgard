#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::instance = NULL;
boost::shared_mutex GraphicsEngine::updateLock;

GraphicsEngine::GraphicsEngine() {
   // Ensure Screen has been initialized.
   Screen* s = Screen::getInstance();
}

GraphicsEngine::~GraphicsEngine() {

}

GraphicsEngine* GraphicsEngine::getInstance() {
   if(instance == NULL) instance = new GraphicsEngine();
   return instance;
}

bool GraphicsEngine::eventHandler(SDL_Event& event) {
   bool run = true;
   if (event.type == SDL_QUIT) {
      // TODO: Need to signal Asgard to exit here.
   }

   return run;
}

void GraphicsEngine::play() {
   int time = 0;
   Screen* s = Screen::getInstance();
   bool run = true;

   while(run)
   {
      SDL_Event event; 
      while(SDL_PollEvent(&event)) {
         run = this->eventHandler(event);
      }

      time = SDL_GetTicks();

      // Wait for write access to layers.  Once obtained, update them.
      GraphicsEngine::obtainLock();
      s->prepare();
      GraphicsEngine::releaseLock();

      s->flip();
      time = SDL_GetTicks() - time;

      // A delay of <= 0 causes this thread to never wake up
      int delay = (1000/Screen::FPS)-time;
      if (delay <= 0) {
         delay = 1;
      }
      boost::this_thread::sleep(boost::posix_time::milliseconds(delay));
   }
}

// Wait for write access to the screen/layers.
void GraphicsEngine::obtainLock() {
   return GraphicsEngine::updateLock.lock_shared();
}

void GraphicsEngine::releaseLock() {
   GraphicsEngine::updateLock.unlock_shared();
}

/*
bool GraphicsEngine::interpretMessage(Message* message) {
   if (message->header.type == MESSAGE_TYPE_DISPLAY_DRAWABLE) {
      this->handleDisplayDrawable(message);
   } else if (message->header.type == MESSAGE_TYPE_TRANSLATE_DRAWABLES_BY_OFFSET) {
      this->handleTranslateDrawablesByOffset(message);
   } else if (message->header.type == MESSAGE_TYPE_UNLOAD_DRAWABLE) {
      this->handleUnloadDrawable(message);
   }

}

void GraphicsEngine::handleDisplayDrawable(Message* message) {
   LOG(INFO) << "Handling DisplayDrawable";

   std::string layerName = message->data.displayDrawable.layName;
   Drawable* drawable = message->data.displayDrawable.drawPtr;
   int x = message->data.displayDrawable.x;
   int y = message->data.displayDrawable.y;

   Screen* s = Screen::getInstance();

   Layer* l = s->getLayer(layerName);

   drawable->move(x, y);

   // TODO: parameterize whether to play or not.
   drawable->play();

   // TODO: parameterize stack location on layer
   // Always on the top?
   if (l != NULL) {
      l->insertDrawableTop(drawable);
   }
}

void GraphicsEngine::handleTranslateDrawablesByOffset(Message* message) {
   LOG(INFO) << "Handling TranslateDrawablesByOffset";

   TranslateDrawablesByOffset data = message->data.translateDrawablesByOffset;

   Screen* s = Screen::getInstance();
   std::vector<std::string>* drawableNames = data.drawableNames;
   int xOffset = data.X;
   int yOffset = data.Y;

   std::vector<std::string>::iterator itr;
   for (itr = drawableNames->begin(); itr != drawableNames->end(); itr++) {
      std::string drawableName = *itr;
      LOG(INFO) << "Can we find " << drawableName << "?";
      Drawable* d = s->getDrawableByName(drawableName);
      if (d != NULL) {
         LOG(INFO) << "Found it.  Moving by offset.";
         d->moveByOffset(xOffset, yOffset);
      }
   }
}

void GraphicsEngine::handleUnloadDrawable(Message* message) {
   LOG(INFO) << "Handling UnloadDrawable";

   UnloadDrawable data = message->data.unloadDrawable;

   Screen* s = Screen::getInstance();

   Drawable* d = s->getDrawableByName(*(data.drawableName));

   if (d != NULL) {
	   LOG(INFO) << "Successfully found drawable to unload.";
      d->unload();
   } else {
	   LOG(INFO) << "Unable to find Drawable for unloading.";
   }
}

*/
