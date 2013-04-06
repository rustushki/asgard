#include "GuiFactory.h"
//#include "Menu.h"
#include "Coordinate.h"
#include "Theme.h"
#include "Box.h"
#include "Dialog.h"

GuiFactory* GuiFactory::instance = NULL;

GuiFactory::GuiFactory() {
   this->theme = NULL;
   this->setThemeName("default");
}

GuiFactory::~GuiFactory() {
}

GuiFactory* GuiFactory::GetInstance() {
   if (GuiFactory::instance == NULL) {
      GuiFactory::instance = new GuiFactory();
   }

   return GuiFactory::instance;
}

Menu* GuiFactory::buildMenu(std::vector<std::string> list) {
/*
   Menu* menu = new Menu(list);
   this->box.push_back((Box*) menu);

   return menu;
*/
   return NULL;
}

Dialog* GuiFactory::buildDialog(std::string imagePath, std::string text) {
   Dialog* dialog = new Dialog(imagePath, text);
   this->box.push_back((Box*) dialog);

   return dialog;
}

void GuiFactory::setThemeName(std::string themeName) {
   if (this->themeName != themeName) {
      this->themeName = themeName;

      if (this->theme != NULL) {
         delete this->theme;
      }

      this->theme = new Theme(themeName);
   }
}

std::string GuiFactory::getThemeName() const {
   return this->themeName;
}

Theme* GuiFactory::getTheme() const {
   return this->theme;
}
