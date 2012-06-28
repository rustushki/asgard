#include "externals.h"
#include "Item.h"
#include "Inventory.h"

int main() {
   Inventory i1;

   Item it1("potion");
   Item it2("master sword");
   Item it3("potion");

   i1.addItem(it1);
   i1.addItem(it2);
   i1.addItem(it3);

   assert(i1.countItems() == 3);
   assert(i1.countUniqueItems() == 2);
   assert(i1.countItemsByName("potion") == 2);
   assert(i1.countItemsByName("MASTer SWoRD") == 1);

   Inventory i2;
   i1.transferItemToInventory("mastER sworD", &i2);
   assert(i1.countItems() == 2);
   assert(i1.countUniqueItems() == 1);

   i1.transferItemToInventory("potion", &i2, 2);
   assert(i1.countItems() == 0);
   assert(i1.countUniqueItems() == 0);

   assert(i2.countItems() == 3);
   assert(i2.countUniqueItems() == 2);
   assert(i2.countItemsByName("potion") == 2);
   assert(i2.countItemsByName("MASTer SWoRD") == 1);

   Inventory i3 = i2.getItemsByName("potion");
   assert(i3.countUniqueItems() == 1);
   assert(i3.countItems() == 2);
   assert(i3.countItemsByName("potion") == 2);

    return 0;
}
