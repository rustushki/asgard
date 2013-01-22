#ifndef DIALOG_H
#define DIALOG_H

#include <string>
#include "Box.h"
#include "ResourceLoader.h"
#include "externals.h"

class Dialog : public Box {

   public:
      ~Dialog();

   protected:
      virtual void buildSurface();

   private:
      Dialog(std::string image, std::string text);

      std::string text;

      void drawText();

      friend class GuiFactory;
};

#endif//DIALOG_H
