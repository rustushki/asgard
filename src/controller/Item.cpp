#include "Item.h"

Item::Item()
{
}

Item::Item(string n)
{
   name = n;
}

string Item::getName()
{
   return name;
}
