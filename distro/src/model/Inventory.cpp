#include "Inventory.h"

Inventory::Inventory() {

}

Inventory::~Inventory() {

}

/* ------------------------------------------------------------------------------
 * Copy Constructor for Inventory.
 */
Inventory::Inventory(const Inventory& inv) {
   this->item = inv.item;
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

   bool stillFoundItems = true;
   while(stillFoundItems) {
      stillFoundItems = this->transferItemToInventory(name, &inv);
   }

   return inv;
}

/*------------------------------------------------------------------------------
 * transferAll - Takes all items in this inventory and put them in the
 * provided inventory.
 */
void Inventory::transferAll(Inventory* inventory) {
   while (this->countItems() > 0) {
         std::string name = this->item[0].getName();
         this->transferItemToInventory(name, inventory);
   }
}

/*------------------------------------------------------------------------------
 * transferItemToInventory - Given an item name, transfer one of that kind of
 * item from this inventory to the provided inventory.
 */
bool Inventory::transferItemToInventory(std::string name, Inventory* inventory) {
   std::vector<Item>::iterator itemI;

   std::transform(name.begin(), name.end(), name.begin(), ::tolower);

   bool found = false;

   for(itemI = this->item.begin(); itemI < this->item.end(); itemI++) {

      std::string cName = itemI->getName();
      std::transform(cName.begin(), cName.end(), cName.begin(), ::tolower);

      if (cName.compare(name) == 0) {
         Item toBeTransferred = *itemI;
         this->item.erase(itemI);
         inventory->addItem(toBeTransferred);
         found = true;
         break;
      }

   }

   return found;
}

/*------------------------------------------------------------------------------
 * transferItemToInventory - Given an item name, transfer n of that kind of
 * item from this inventory to the provided inventory.
 */
unsigned int Inventory::transferItemToInventory(std::string name, Inventory* inventory, unsigned int count) {
   unsigned int totalFound = 0;

   while (totalFound < count) {

      if (this->transferItemToInventory(name, inventory)) {
         totalFound++;
      } else {
         break;
      }
   }

   return totalFound;
}

/*------------------------------------------------------------------------------
 * countUniqueItems - Count item types in the inventory.
 */
unsigned int Inventory::countUniqueItems() const {

	std::set<std::string> uniqueSet;
    std::vector<Item>::const_iterator itemI;

    for(itemI = this->item.begin(); itemI < this->item.end(); itemI++) {
        
        std::string cName = itemI->getName();
        std::transform(cName.begin(), cName.end(), cName.begin(), ::tolower);

		uniqueSet.insert(cName);
    }

    return uniqueSet.size();
}

/*------------------------------------------------------------------------------
 * countItems - Count all items in the inventory.
 */
unsigned int Inventory::countItems() const {
    return this->item.size();
}

/*------------------------------------------------------------------------------
 * countItems - Given an item name, count how many of them are in this inventory.
 */
unsigned int Inventory::countItemsByName(std::string name) const {
    std::vector<Item>::const_iterator itemI;

    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	unsigned int count = 0;

    for(itemI = this->item.begin(); itemI < this->item.end(); itemI++) {
        
        std::string cName = itemI->getName();
        std::transform(cName.begin(), cName.end(), cName.begin(), ::tolower);

		if (cName.compare(name) == 0) {
			count++;
		}

    }

	return count;

}