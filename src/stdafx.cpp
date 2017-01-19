#include "stdafx.h"
#include <cstring>
#include <string>
#include <iostream>

using std::cerr;
using std::endl;
using std::string;

#ifdef WIN32

bool dir_exists(const char* _Path)
{
    struct _stat fileStat;
    if((_stat(_Path, &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
    {
        return true;
    }
    return false;
}

#else
bool dir_exists(const char* _Path)
{
    struct stat fileStat;
    if((stat(_Path, &fileStat) == 0) && S_ISDIR(fileStat.st_mode))
    {
        return true;
    }
    return false;
}

#endif

enum RDT{
    RDT_FILE = 8,
    RDT_LINK_FILE = 10,
    RDT_DIR = 4
};
int cleandir_force(const char* _Path)
{
    DIR* dir;
    struct dirent* ptr;
    char base[1000];

    if((dir = opendir(_Path)) == NULL)
    {
        cerr << "Open dir " << _Path << " error" << endl;
        return -1;
    }

    while((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) // current dir OR parent dir
            continue;
        else if(ptr->d_type == RDT::RDT_FILE || ptr->d_type == RDT::RDT_LINK_FILE)
        {
            remove((string(_Path) + "/" + ptr->d_name).c_str());
        }
        else if(ptr->d_type == RDT::RDT_DIR)
        {
            rmdir_force((string(_Path) + "/" + ptr->d_name).c_str());
        }
    }

    closedir(dir);
    return 0;

}

int rmdir_force(const char* _Path)
{
    if(cleandir_force(_Path) != 0)
        return -1;
    rmdir(_Path);
    return 0;
}

