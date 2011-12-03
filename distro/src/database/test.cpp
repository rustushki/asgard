#include <iostream>
#include "Database.h"

int main()
{

   Database* d = Database::getInstance();

   d->loadBoundingBox(1);

   return 0;
}
