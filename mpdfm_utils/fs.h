#pragma once
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

namespace fs_util
{
    class path
    {
    public:
        path();
        static char* get_cwd()
        {
            static char cwd_buffer[256];
            getcwd(cwd_buffer, sizeof(cwd_buffer));
            
            return cwd_buffer;
        }
        static char* get_home()
        {
            char *homedir;

            if ((homedir = getenv("HOME")) == NULL)
                homedir = getpwuid(getuid())->pw_dir;

            return homedir;
        }
	static int move(std::string target, std::string new_dir)
        {
            return rename(target.data(), new_dir.data());
        }
    };

    class soft_link
    {
    public:
        static int create(std::string dir_path, std::string link_path)
        {
            return symlink(dir_path.data(), link_path.data());
        }
        static int remove(std::string path)
        {
            return unlink(path.data());
        }
	static char* get_origin(std::string link_path)
	{
	    static char buf[1024];
	    ssize_t len;
	    if ((len = readlink(link_path.data(), buf, sizeof(buf)-1)) != -1)
    	        buf[len] = '\0';

	    return buf;
	}
    };
}
