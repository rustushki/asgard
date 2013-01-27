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

      static int getWordNPos(int n, std::string text);
      static int getWordCount(std::string text);
      static std::string getUpToWordN(int n, std::string text);
      static std::string getAfterWordN(int n, std::string text);

      void drawText();

      friend class GuiFactory;
};

#endif//DIALOG_H
