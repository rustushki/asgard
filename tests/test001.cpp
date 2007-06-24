#include <iostream>
using std::cout;
using std::endl;
#include "Coordinate.h"
#include "CircHardpoint.h"


int main()
{
   Coordinate x(1,1);
   Coordinate y(3,4);
   Coordinate z;
   Coordinate o;

   CircHardpoint cp(3,3,3);

   z = x + y;

   x += y;

   if (x == z)
      cout << "x + y == z" << endl; 
  
   x -= y;

   if (x != z)
      cout << "x + y != z" << endl;

   if (x + y == y + x)
      cout << "x + y == y + x" << endl;

   if (x - x == o)
      cout << "x - x = (0,0)" << endl;

   cout << distance(x,y) << endl;

   if (cp.conflict(y))
      cout << "cp conflicts with y" << endl;
   
   if (cp.conflict(o))
      cout << "cp conflicts with o" << endl;

   z = x + 1;
   z = 1 + x;
   z = x - 1;
   z = 1 - x;
   z = x * 1;
   z = 1 * x;
   z = x / 1;
   z = 1 / x;

   return 0;
}
