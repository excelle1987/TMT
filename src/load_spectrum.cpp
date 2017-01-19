#include "stdafx.h"
#include "load_spectrum.h"
#include <iostream>

using std::string;
using std::cerr;
using std::cout;
using std::endl;

//int LoadSpectrum::load_test(const char* path)
//{
//    m_ifs.open(m_path.c_str());
//    if(m_ifs.fail())
//    {
//        cerr << "Fatal error: input file could not be opened." << endl;
//        return 0;
//    }
//
//    // test for the file extension .mzdata
//    string test = m_path;
//    transform(test.begin(), test.end(), test.begin(), ::tolower);
//    if(test.find(path) != string::npos)
//    {
//        m_ifs.close();
//        return 2;
//    }
//
//    m_test.clear();
//    string line;
//    std::getline(m_ifs, line);
//    m_test += line;
//    while(m_ifs.good() && m_ifs.eof() && m_test.size() < bufSize)
//}




