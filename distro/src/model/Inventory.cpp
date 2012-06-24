#include "Inventory.h"

Inventory::Inventory() {

}

Inventory::~Inventory() {

}


void Inventory::addItem(Item item) {
    this->item.push_back(item);
}

/*------------------------------------------------------------------------------
 * getItemByName - Return an inventory containing the item denoted by the
 * provided name.  Note that we need an Inventory returned because there may be
 * multiple items of the same type.  Use transferItemToInventory to move items
 * between existing inventories.
 */
Inventory Inventory::getItemsByName(std::string name) {

    Inventory inv;

    std::vector<Item>::iterator itemI;

    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    for(itemI = this->item.begin(); itemI < this->item.end(); itemI++) {
        
        std::string cName = (*itemI).getName();
        std::transform(cName.begin(), cName.end(), cName.begin(), ::tolower);

        if (cName.compare(name)) {
            inv.addItem(*itemI);
        }
    }

    return inv;

}

void Inventory::mergeInventory(const Inventory* inventory) {

}

bool Inventory::transferItemToInventory(std::string name, const Inventory* inventory) {
    return true;
}

unsigned int Inventory::countUniqueItems() const {
    return 0;
}

unsigned int Inventory::countItems() const {
    return 0;
}

unsigned int Inventory::getCountOfItemByName(std::string name) const {
    return 0;
}
