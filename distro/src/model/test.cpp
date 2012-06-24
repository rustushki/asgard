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

    return 0;
}
