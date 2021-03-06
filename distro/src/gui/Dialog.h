#ifndef DIALOG_H
#define DIALOG_H

#include "externals.h" 
#include "Box.h"

class Dialog : public Box {

   public:
      ~Dialog();

   protected:
      virtual void buildSurface();

   private:
      Dialog(std::string image, std::string text);

      std::string text;

      static std::string getNextLine(std::string& remainingText, TTF_Font* font, Uint16 maxWidth);
      static int getWordNPos(int n, std::string text);
      static int getWordCount(std::string text);
      static std::string getUpToWordN(int n, std::string text);
      static std::string getAfterWordN(int n, std::string text);

      void drawText();

      friend class GuiFactory;

};

#endif//DIALOG_H
