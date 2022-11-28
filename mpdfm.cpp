#include <iostream>
#include "mpdfm_utils/fs.h"
#include "argh.h"

using namespace std;

int main(int, char* argv[])
{
  argh::parser cmdl(argv);

  string command = cmdl[1];

  char *cwd_buffer = fs_util::path::get_cwd();
  const char *home_dir = fs_util::path::get_home();

  if (command == "dot")
  {
    string target = cmdl[2];
    string new_dir = string(cwd_buffer) + "/" + ( cmdl[3].empty() ? target.substr(target.find_last_of("/\\") + 1) : cmdl[3] );

    cout << target << " -> " << new_dir << endl;

    if (fs_util::path::move(target, new_dir) != 0)
    {
      cerr << "Error moving file!" << endl;
      return 1;
    }
    else
    {
      cout << "Moved " << target << " to " << new_dir << endl;
    }

   if (fs_util::soft_link::create(new_dir, target) != 0)
    {
      cerr << "Error adding a symlink to " << target << " from " << new_dir << endl;
      return 1;
    }
    else
    {
      cout << "Added a symlink to " << target << " from " << new_dir << endl;
    }
  }
  else if (command == "link")
  {
    string fn = string(cwd_buffer) + "/" + cmdl[2];
    string to_symlink = cmdl[3].empty() ? string(home_dir) + "/" + cmdl[2] : cmdl[3];

    if (fs_util::soft_link::create(fn, to_symlink) != 0)
    {
      cerr << "Error adding a symlink to " << to_symlink << " from " << fn << endl;
      return 1;
    }
    else
    {
      cout << "Added a symlink to " << to_symlink << " from " << fn << endl;
    }
  }
  else
  {
    cout << command << endl;
  }
}
