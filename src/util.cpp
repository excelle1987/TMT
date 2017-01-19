#include "stdafx.h"
#include "util.h"
#include <iostream>

using std::vector;
using std::string;

vector<string> split(const string& s, char delim) 
{
    std::vector<std::string> result;
    size_t start = 0, find = 0;
    while((find = s.find(delim, start)) != string::npos)
    {
        result.push_back(s.substr(start, find - start));
        start = find + 1;
    }
    result.push_back(s.substr(start));
    return result;
}
