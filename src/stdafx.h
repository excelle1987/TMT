#ifndef STDAFX_H
#define STDAFX_H

//#include "../config.h"

#ifdef WIN32
#include <io.h>
#include <direct.h>

// int mkdir(const char* _Path); // already have

#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

inline int mkdir(const char* _Path)
{
    return mkdir(_Path, S_IRWXU|S_IRWXG|S_IRWXO);
}

#endif

#include <iostream>

// Common functions, but different including files

/** AccessMode:
  * R_OK: judge read authority
  * W_OK: judge write authority
  * X_OK: judge execute authority
  * F_OK: judge file exists
  */
//int access(const char* _Filename, int _AccessMode);

//int rmdir(const char* _Path);

bool dir_exists(const char* _Path);

#include <cstdio>

// int remove(const char* filename);

int rmdir_force(const char* _Path);

int cleandir_force(const char* _Path);

#endif  /*STDAFX_H*/
