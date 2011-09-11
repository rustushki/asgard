#include "externals.h"
#include "Screen.h"
#include "Layer.h"
#include "Drawable.h"
#include "Animation.h"

int main()
{
   google::InitGoogleLogging("asgard");

   Screen* s = Screen::getInstance();

   std::string lsName = "stage";
   Layer* ls = new Layer(lsName);

   std::string lbName = "background";
   Layer* lb = new Layer(lbName);

   std::string d1Name = "testDrawable1";
   Drawable* d1 = new Drawable(d1Name);

   std::string d2Name = "testDrawable2";
   Drawable* d2 = new Drawable(d2Name);
   
   std::string dbName = "testBackground";
   Drawable* db = new Drawable(dbName);

   std::string abName = "backgroundAnimation";
   Animation* ab = new Animation("background.png", 800, 600, 1, 1, 1, 1);

   std::string a1Name = "cecil";
   std::string a2Name = "cecil";
   std::string a3Name = "demo";
   Animation* a1 = new Animation("cecil.png", 34, 24, 8, 1, 1, 8);
   Animation* a2 = new Animation("cecil.png", 34, 24, 8, 1, 1, 8);
   Animation* a3 = new Animation("demo_animation.png", 250, 250, 4, 25, 2, 2);

   d1->addAnimation(a1, a1Name);
   d2->addAnimation(a2, a2Name);
   d2->addAnimation(a3, a3Name);
   db->addAnimation(ab, abName);

   ls->insertDrawableTop(d2);
   ls->insertDrawableTop(d1);
   lb->insertDrawableTop(db);
   s->appendLayer(lb);
   s->appendLayer(ls);

   d1->play();
   d2->play();
   db->play();
   int time = 0;
   int cv = 0;
   int r = 0;
   bool run = true;
   while(run)
   {
      SDL_Event event; 
      while(SDL_PollEvent(&event)) {
         if (event.type == SDL_QUIT) {
            run = false;
         }
      }

      time = SDL_GetTicks();
      s->prepare();
      s->flip();
      time = SDL_GetTicks() - time;
      cv++;

      d1->moveByOffset(1,1);

      if (r == 35) {
         LOG(INFO) << "Showing";
         d1->show();
      } else if (r == 15) {
         LOG(INFO) << "Hiding";
         d1->hide();
      }

      if (r == 25)
      {
         d2->swapAnimation("cecil");
      }
      else if (r == 50)
      {
         d2->swapAnimation("demo");
         r=0;
      }
      r++;

      cv = 0;

      int delay = (1000/Screen::FPS) - time;
      if (delay <= 0) {
         delay = 1;
      }
      SDL_Delay(delay);
   }
   
   delete s;
   return 0;
}
