#ifndef  MAIN_H
#define  MAIN_H

#include <fstream>
#include <algorithm>

#include "mib/algorithm.h"
#include "mib/io.h"
#include "mib/string_operations.h"

using namespace std;
using namespace mvc_utils::io;
using namespace mvc_utils::algorithm;
using namespace mvc_utils::string_operations;

class header_guard
{
  public:
    header_guard() = delete;
    header_guard(string fname) : file_name(fname)  { open_file();  }

    void guard();
    void guard(const string &, const string &);
    void open_file(string &fname) { file_name = fname; open_file(); }
    void print()     { ::print(guarded); }
    void print_src() { ::print(original); }
    string source()  { return original; }
    void   write();

  private:
    void open_file();

  private:
    string file_name = "output", guarded = "", original = "";
};

void header_guard::open_file()
{
  std::ifstream in_stream(file_name.c_str());
  if (in_stream.is_open())
  {
    string stmp = "";
    while (!in_stream.eof())
    {
      getline(in_stream, stmp);
      original += stmp + "\n";
    }
  }

  in_stream.close();
}

void header_guard::guard()
{
  using namespace mvc_utils::string_operations;

#ifdef OS_WIN
  string stmp = to_upper(find_n_replace(file_name_w_ext(file_name, '\\'), '.', '_'));
#else
  string stmp = (find_n_replace(file_name_w_ext(file_name), '.', '_'));
#endif // OS_WIN

  guarded += "#ifndef " + stmp + "\n";
  guarded += "#define " + stmp + "\n\n";

  guarded += original;
  guarded += "#endif//" + stmp + "\n";
}

void header_guard::write()
{
  ofstream out_stream(file_name);
  if (out_stream.is_open())
  {
    out_stream.write(guarded.c_str(), guarded.size());
    out_stream.close();
  }
}

#endif//MAIN_H
