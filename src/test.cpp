#include "stdafx.h"
#include "test.h"
#include <iostream>
using namespace std;

static const string MODULE_NAME = "test";

Test Test::s_runner;

Test::Test():
    Runner("rh")
{
    Runner_Install(MODULE_NAME, this, "test code correction only");
}

int Test::checkOptions(const Properties& options) const
{
    if(options.find("h") != options.end())
    {
        return printHelps();
    }
    return 0;
}

int Test::printHelps() const
{
    cout << "usage: " << PACKAGE_NAME << " " << MODULE_NAME << " -r"<< endl;
    cout << endl;
    return HELP_RETURN;
}

int Test::run(const Properties& options, const Arguments& arguments)
{
    cout << "clean dir" << endl;
    if(cleandir_force(".tmp") != 0)
    {
        cerr << "error!" << endl;
        return -1;
    }
    cout << "clean dir done!" << endl;

    return 0;
}
