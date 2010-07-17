#include <iostream>
#include <string>
#include <fstream>
#include <sqlite3.h>
#include <sstream>

using std::cout;
using std::string;
using std::ifstream;
using std::stringstream;
using std::endl;

int callback(void *NotUsed, int argc, char ** argv, char **azColName)
{
   cout << "foo";
   return 0;
}

int main(int argc, char **argv)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char line[1024];
   ifstream sqlite_script;
   string query;

   if (argc >= 1 && argc < 3)
   {
      cout << "usage: runquery <database> <sqlite_script>\n";
      return 0;
   }

      
   query = "";
   sqlite_script.open(argv[2]);
   while (!sqlite_script.eof())
   {
      sqlite_script.getline(line,1024);
      query += string(line) + "\n";
   }

   sqlite_script.close();

   rc = sqlite3_open(argv[1], &db);
   rc = sqlite3_exec(db, query.c_str(), callback, 0, &zErrMsg);

   if (rc > 0)
   {
      cout << "Error " << rc << endl;
      cout << sqlite3_errmsg(db);
      cout << endl;
      return 1;
   }
   else
      return 0;

   sqlite3_close(db);

   return 0;
}
