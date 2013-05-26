#include "GuiFactory.h"
//#include "Menu.h"
#include "Coordinate.h"
#include "Theme.h"
#include "Box.h"
#include "Dialog.h"

GuiFactory* GuiFactory::instance = NULL;

GuiFactory::GuiFactory() {
   theme = nullptr;
   setThemeName("default");
}

GuiFactory::~GuiFactory() {
   deleteAll();
}

GuiFactory* GuiFactory::GetInstance() {
   if (GuiFactory::instance == NULL) {
      GuiFactory::instance = new GuiFactory();
   }

   return GuiFactory::instance;
}

std::shared_ptr<Menu> GuiFactory::buildMenu(std::vector<std::string> list) {
/*
   std::shared_ptr<Menu> menu(new Menu(list));
   box.push_back(menu);

   return menu;
*/
   return nullptr;
}

std::shared_ptr<Dialog> GuiFactory::buildDialog(std::string imagePath, std::string text) {
   std::shared_ptr<Dialog> dialog(new Dialog(imagePath, text));
   box.push_back(dialog);

   return dialog;
}

void GuiFactory::setThemeName(std::string themeName) {
   if (this->themeName != themeName) {
      themeName = themeName;

      if (theme != nullptr) {
         theme.reset();
      }

      theme = std::shared_ptr<Theme>(new Theme(themeName));
   }
}

std::string GuiFactory::getThemeName() const {
   return themeName;
}

std::shared_ptr<Theme> GuiFactory::getTheme() const {
   return theme;
}

void GuiFactory::deleteAll() {
   // Hide all Boxes
   for (int i=0; i<this->box.size(); i++)
      box[i]->unload(); // also deletes associated Drawable

   // Free Boxes from memory
   this->box.clear();
}
