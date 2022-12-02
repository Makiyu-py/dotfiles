#include <iostream>
#include "mpdfm_utils/fs.h"
#include "mpdfm_utils/cli.h"
#include "./include/argh/argh.h"

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

    if (fs_util::path::exists(new_dir))
    {
      if (
        !cli_util::get_input_by_bool(
          "It looks like the path that'll replace the original path (" + 
          new_dir + 
          ") already exists!\nIf we proceed, we'll delete that path in favor of moving the original path (" +
          target +
          ") to it.\nAfterwards, we'll make a symlink on the original path that'll point to its replacement (" +
          new_dir +
          ") with the contents of the deleted original path.\nWould you like to proceed?"
        )
      )
      {
        cout << "Aborted dot." << endl;
        return 0;
      }

      if (fs_util::path::delete_path(new_dir))
      {
        cout << "Deleted '" << new_dir << "'" << endl;
      }
    }

    cout << target << " -> " << new_dir << endl;

    fs_util::path::move(target, new_dir);

    fs_util::soft_link::create(new_dir, target);
  }
  else if (command == "link")
  {
    string fn = cwd + "/" + cmdl[2];
    string to_symlink = cmdl[3].empty() ? home_dir + "/" + cmdl[2] : cmdl[3];

    if (fs_util::path::exists(to_symlink))
    {
      if (
        !cli_util::get_input_by_bool(
          "It looks like the path '" + 
          to_symlink + 
          "' already exists! If we proceed, we'll delete that path in favor of the symlink.\nWould you still like to proceed?"
        )
      )
      {
        cout << "Aborted link." << endl;
        return 0;
      }

      if (fs_util::path::delete_path(to_symlink))
      {
        cout << "Deleted '" << to_symlink << "'" << endl;
      }
    }

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
