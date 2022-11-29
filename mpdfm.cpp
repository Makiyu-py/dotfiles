#include <iostream>
#include "mpdfm_utils/fs.h"
#include "argh.h"

using namespace std;

int main(int, char* argv[])
{
  argh::parser cmdl(argv);

  string command = cmdl[1];

  string cwd = fs_util::path::get_cwd();
  string home_dir = fs_util::path::get_home();

  if (command == "dot")
  {
    string target = cmdl[2];
    string new_dir = cwd + "/" + ( cmdl[3].empty() ? target.substr(target.find_last_of("/\\") + 1) : cmdl[3] );

    cout << target << " -> " << new_dir << endl;

    fs_util::path::move(target, new_dir);

    fs_util::soft_link::create(new_dir, target);
  }
  else if (command == "link")
  {
    string fn = cwd + "/" + cmdl[2];
    string to_symlink = cmdl[3].empty() ? home_dir + "/" + cmdl[2] : cmdl[3];

    fs_util::soft_link::create(fn, to_symlink);
  }
  else if (command == "undot")
  {
    string sym = cmdl[2];
    string to_move = fs_util::soft_link::get_origin(sym);
    
    fs_util::soft_link::remove(sym);
    fs_util::path::move(to_move, sym);
  }
  else
  {
    cout << command << endl;
  }
}
