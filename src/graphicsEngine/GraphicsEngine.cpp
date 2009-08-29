#include <string>
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
}
      
bool GraphicsEngine::interpretMessage(Message* message)
{
   if (message->header.type == MESSAGE_TYPE_DISPLAY_DRAWABLE)
   {
      string layerName = message->data.displayDrawable.layName;
      Drawable* drawable = message->data.displayDrawable.drawPtr;

      Screen* s = Screen::getInstance();

      Layer* l = s->getLayer(layerName);

      // TOOD: parameterize stack location on layer
      // Always on the top?
      if (l != NULL)
         l->insertDrawableTop(drawable);

      // TOOD: parameterize whether to play or not.
      drawable->play();
   }
}
