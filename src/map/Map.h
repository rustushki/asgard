#ifndef MAP_H
#define MAP_H

#include "SystemComponent.h"

class Map : public SystemComponent
{
   public:
      ~Map();

      virtual bool open();
      virtual bool close();

      static Map* getInstance();

   private:
      Map();

      void noop();

      static Map* instance;

      virtual bool interpretMessage(Message* message);
};

#endif//MAP_H
