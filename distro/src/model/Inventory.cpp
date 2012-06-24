#include "Inventory.h"

Inventory::Inventory() {

}

Inventory::~Inventory() {

}


/*------------------------------------------------------------------------------
 * addItem - Add an item to this inventory.
 */
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

/*------------------------------------------------------------------------------
 * mergeInventory - Takes all items in the provided inventory and puts them in
 * this inventory.
 */
void Inventory::mergeInventory(Inventory* inventory) {

}

/*------------------------------------------------------------------------------
 * transferItemToInventory - Given an item name, transfer all of that kind of
 * item from the provided inventory to this inventory.
 */
bool Inventory::transferItemToInventory(std::string name, Inventory* inventory) {
    return true;
}

/*------------------------------------------------------------------------------
 * countUniqueItems - Count item types in the inventory.
 */
unsigned int Inventory::countUniqueItems() const {
    return 0;
}

/*------------------------------------------------------------------------------
 * countItems - Count all items in the inventory.
 */
unsigned int Inventory::countItems() const {
    return 0;
}

/*------------------------------------------------------------------------------
 * countItems - Given an item name, count how many of them are in this inventory.
 */
unsigned int Inventory::countItemsByName(std::string name) const {
    return 0;
}
