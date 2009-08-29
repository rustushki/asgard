#include "GraphicsEngine.h"

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
{return true;}
