#ifndef __cplusplus
#define __cplusplus 201103L
#endif

#include <mib/io.h>
#include "main.h"

using namespace std;
using namespace mvc_utils::io;
using namespace mvc_utils::algorithm;

int main(int argc, char *argv[])
{
   string help[2] = {"-h", "--help"};

   if (argc > 1)
   {
      if (help[0] == argv[1] || help[1] == argv[1])
      {
         print_ln("Help Page");
         print_ln("  e.g: header_gurad source_file");
         print_ln("     : header_gurad source_file(s)");
         return 0;
      }

      for (uint i = 1; i != static_cast<uint>(argc); ++i)
      {
         header_guard h(argv[i]);
         h.guard();
         h.write();
         h.print();
         //print_ln(argv[i]);
      }
   }
   else
   {
      print_ln(argv[0]);
      print("Too few arguements"); DL
      print("Usage: header_guard file(s)\n");
   }

   return 0;
}
