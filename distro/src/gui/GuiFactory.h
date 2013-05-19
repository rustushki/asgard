#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include <vector>
#include <string>

#include "Dialog.h"
#include "Box.h"
#include "Theme.h"
class Menu;

class GuiFactory {

private:
   GuiFactory();

   static GuiFactory* instance;

   std::vector< std::shared_ptr<Box> > box;

   std::string themeName;
   std::shared_ptr<Theme> theme;

public:

   static GuiFactory* GetInstance();
   ~GuiFactory();

   std::shared_ptr<Menu> buildMenu(std::vector<std::string> list);
   std::shared_ptr<Dialog> buildDialog(std::string imagePath, std::string text);

   void setThemeName(std::string themeName);
   std::string getThemeName() const;
   std::shared_ptr<Theme> getTheme() const;

   void deleteAll();

};

#endif//GUIFACTORY_H
