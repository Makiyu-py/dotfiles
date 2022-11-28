#include <fstream>
#include <iostream>
#include <ios>
#include <cstdio>
#include <unistd.h>
#include "argh.h"

using namespace std;

int main(int, char* argv[])
{
  argh::parser cmdl(argv);

  string command = cmdl[1];

  char cwd_buffer[256]; // current working dir
  getcwd(cwd_buffer, sizeof(cwd_buffer));

  if (command == "dot") {
    string target = cmdl[2];
    string new_dir = string(cwd_buffer) + "/" + ( cmdl[3].empty() ? target.substr(target.find_last_of("/\\") + 1) : cmdl[3] );

    const char *target_cstr = target.data();
    const char *new_dir_cstr = new_dir.data();

    cout << target << " -> " << new_dir << endl;

    // move the dotfile to the repo
    if (rename(target_cstr, new_dir_cstr) != 0)
    {
      cerr << "Error moving file!" << endl;
      return 1;
    }
    else
    {
      cout << "Moved " << target << " to " << new_dir << endl;
    }

   // add symlink to the target
   symlink(new_dir_cstr, target_cstr);
   cout << "Added a symlink to " << target << " from " << new_dir << endl;
  } else {
    cout << command << endl;
  }
}
