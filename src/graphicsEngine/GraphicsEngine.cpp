#include <string>
#include "Screen.h"
#include "GraphicsEngine.h"

using std::string;

GraphicsEngine* GraphicsEngine::instance = NULL;

GraphicsEngine::GraphicsEngine() : SystemComponent("graphicsEngine")
{

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
   Screen* s = Screen::getInstance();

   std::string lsName = "stageLayer";
   s->pushLayer(new Layer(lsName));

   // TODO: Another process should initialize the background layer.
   // Special Background Layer, Drawable and Animation. Needed so that there's
   // something to out-blit transparent pixels with.
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

   int time = 0;
   while(1)
   {
      time = SDL_GetTicks();
      s->prepare();
      s->flip();
      time = SDL_GetTicks() - time;
      this->listen((1000/Screen::FPS)-time);
   }
}

bool GraphicsEngine::interpretMessage(Message* message)
{
   if (message->header.type == MESSAGE_TYPE_DISPLAY_DRAWABLE)
   {
      string layerName = message->data.displayDrawable.layName;
      Drawable* drawable = message->data.displayDrawable.drawPtr;

      Screen* s = Screen::getInstance();

      Layer* l = s->getLayer(layerName);

      // TODO: parameterize whether to play or not.
      drawable->play();

      // TOOD: parameterize stack location on layer
      // Always on the top?
      if (l != NULL)
         l->insertDrawableTop(drawable);

   }
}
