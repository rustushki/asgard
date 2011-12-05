#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::instance = NULL;
boost::shared_mutex GraphicsEngine::updateLock;

GraphicsEngine::GraphicsEngine() : SystemComponent("graphicsEngine") {

   // Initialize SDL
   SDL_Init(SDL_INIT_VIDEO);
   SDL_SetVideoMode(Screen::WIDTH, Screen::HEIGHT, 16, SDL_DOUBLEBUF);

   // Initialize Screen.
   Screen* s = Screen::getInstance();
}

GraphicsEngine::~GraphicsEngine()
{

}

GraphicsEngine* GraphicsEngine::getInstance()
{
   if(instance == NULL) instance = new GraphicsEngine();
   return instance;
}


bool GraphicsEngine::open()
{
   bool status = true;
   
   this->thread->open(boost::bind(&GraphicsEngine::initScreen, this));
   
   status = SystemComponent::open();
   
   return status;
}

bool GraphicsEngine::close()
{
   bool status = true;
   
   if(!this->thread->isClosed())
   {
      this->thread->close();
   }
   
   status = SystemComponent::close();
   
   return status;
}

void GraphicsEngine::initScreen()
{
   // Grab Screen Instance
   Screen* s = Screen::getInstance();

   // Setup Screen Layers
   std::string lsName = "stageLayer";
   s->pushLayer(new Layer(lsName));

   // TODO: Another process should initialize the background layer.
   // Special Background Layer, Drawable and Animation. Needed so that there's
   // something to out-blit transparent pixels with.

   // Create Background
   std::string abName = "backgroundAnimation";
   Animation* ab = new Animation("background.png", 800, 600, 1, 1, 1, 1);
   std::string dbName = "testBackground";
   Drawable* db = new Drawable(dbName);
   db->addAnimation(ab, abName);
   db->play();
   lsName = "background";
   Layer* bgLayer = new Layer(lsName);
   bgLayer->insertDrawableTop(db);
   s->pushLayer(bgLayer);

   // TODO: make this a command so that this thread can terminate.
   LOG(INFO) << "Starting GraphicsEngine.";
   this->play();
}

bool GraphicsEngine::eventHandler(SDL_Event& event) {
   bool run = true;
   if (event.type == SDL_QUIT) {
      // TODO: Need to signal Asgard to exit here.
   }

   return run;
}

void GraphicsEngine::play()
{
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
      this->listen(delay);
   }
}

// Wait for write access to the screen/layers.
void GraphicsEngine::obtainLock()
{
   return GraphicsEngine::updateLock.lock_shared();
}

void GraphicsEngine::releaseLock()
{
   GraphicsEngine::updateLock.unlock_shared();
}

bool GraphicsEngine::interpretMessage(Message* message)
{
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