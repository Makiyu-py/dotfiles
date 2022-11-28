#include <fstream>
#include <iostream>
#include <ios>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "argh.h"

using namespace std;

char* get_home_dir()
{
  char *homedir;

  if ((homedir = getenv("HOME")) == NULL)
  {
    homedir = getpwuid(getuid())->pw_dir;
  }

  return homedir;
}

void create_soft_link(const char *dir_path, const char *link_path)
{
  symlink(dir_path, link_path);
  cout << "Added a symlink to " << link_path << " from " << dir_path << endl;
}

int main(int, char* argv[])
{
  argh::parser cmdl(argv);

  string command = cmdl[1];

  char cwd_buffer[256]; // current working dir
  getcwd(cwd_buffer, sizeof(cwd_buffer));
  const char *home_dir = get_home_dir();

  if (command == "dot")
  {
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
   create_soft_link(new_dir_cstr, target_cstr);
  }
  else if (command == "link")
  {
    string fn = string(cwd_buffer) + "/" + cmdl[2];
    string to_symlink = cmdl[3].empty() ? string(home_dir) + "/" + cmdl[2] : cmdl[3];

    create_soft_link(fn.data(), to_symlink.data());
  }
  else
  {
    cout << command << endl;
  }
}
