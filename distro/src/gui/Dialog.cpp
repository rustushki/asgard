#include "Dialog.h"

Dialog::Dialog(std::string image, std::string text) {
	// Discard Image for the Momemnt.

	// Set the text member.
	this->text = text;
}

Dialog::~Dialog() {

}

void Dialog::setText(std::string text) {
   this->text = text;
}

std::string Dialog::getText() const {
   return this->text;
}
