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
	~GuiFactory();

	static GuiFactory* instance;

	std::vector<Box*> box;

   std::string themeName;
	Theme* theme;

public:

	static GuiFactory* GetInstance();

	Menu* buildMenu(std::vector<std::string> list);
	Dialog* buildDialog(std::string imagePath, std::string text);

	void setThemeName(std::string themeName);
	std::string getThemeName() const;
	Theme* getTheme() const;

};

#endif//GUIFACTORY_H
