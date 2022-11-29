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
	    fs::path path;
	
            if (rel_path.rfind("~/", 0) == 0)  // searched everywhere for an in-built solution... NONE!
                path = fs::absolute(std::string(path::get_home()) + rel_path.substr(1));
            else
                path = fs::canonical(rel_path.c_str());

	    return path.string();
	}
	static void move(std::string target, std::string new_dir)
        {
            fs::rename(target, new_dir);
            std::cout << "Moved " << target << " to " << new_dir << std::endl;
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
        static int remove(std::string path)
        {
            std::string pointed = soft_link::get_origin(path);

            if (fs::remove(path))
		std::cout << "Removed symlink on " << path << " that was pointed at " << pointed << std::endl;
	    else
		std::cerr << "Path '" << path << "' does not exist." << std::endl;
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
