#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <experimental/filesystem>  // we're compiling on C++11 if you've forgotten

namespace fs = std::experimental::filesystem;

namespace fs_util
{
    class path
    {
    public:
        path();
        static std::string get_cwd()
        {           
            return fs::current_path().string();
        }
        static std::string get_home()
        {
            char *homedir;

            if ((homedir = getenv("HOME")) == NULL)
                homedir = getpwuid(getuid())->pw_dir;

            return std::string(homedir);
        }
        static std::string expand_path(std::string rel_path)
        {
            // note to self: apparently "~/" expands by itself
            // when it's in the terminal, so like when i do
            //   $ ./mpdfm undot ~/test_file.txt
            // `cmdl[2]` (on mpdfm.cpp ofc) would already
            // spit out `/Users/Makiyu/test_file.txt` ???
            return fs::canonical(rel_path.c_str()).string();
        }
        static void move(std::string target, std::string new_dir)
        {
            fs::rename(target, new_dir);
            std::cout << "Moved " << target << " to " << new_dir << std::endl;
        }
        static bool exists(std::string path)
        {
            return fs::exists(path) && !fs::is_empty(path);
        }
    };

    class soft_link
    {
    public:
        static void create(std::string dir_path, std::string link_path)
        {
            fs::create_symlink(dir_path, link_path);
    	    std::cout << "Added a symlink to " << link_path << " from " << dir_path << std::endl;
        }
        static void remove(std::string path)
        {
            if (!fs::is_symlink(path)) {
                throw std::invalid_argument("Path '" + path + "' is not a symlink.");
            }

            if (fs::remove(path))
                std::cout << "Removed symlink on " << path << " that was pointed at " << soft_link::get_origin(path) << std::endl;
            else
                throw std::invalid_argument("Path '" + path + "' does not exist.");
        }
	static std::string get_origin(std::string link_path)
	{
	    static char buf[1024];
	    ssize_t len;
	    if ((len = readlink(link_path.data(), buf, sizeof(buf)-1)) != -1)
    	        buf[len] = '\0';

	    return std::string(buf);
	}
    };
}
