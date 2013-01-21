#ifndef DIALOG_H
#define DIALOG_H

#include <string>
#include "Box.h"

class Dialog : public Box {

public:
	~Dialog();

protected:
   virtual void buildSurface();

private:
	Dialog(std::string image, std::string text);

	std::string text;

	friend class GuiFactory;
};

#endif//DIALOG_H
