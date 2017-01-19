#include "stdafx.h"
#include "util.h"
#include "preprocess.h"

#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>



using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::unordered_map;
using std::ifstream;
using std::ofstream;

static const string MODULE_NAME = "preprocess";

Preprocess Preprocess::s_runner;

Preprocess::Preprocess():
    Runner("f:h")
{
    Runner_Install(MODULE_NAME, this, "archive infomation from SEQUEST result");
}

int Preprocess::checkOptions(const Properties& options) const
{
    if(options.find("h") != options.end())
    {
        return printHelps();
    }
    return 0;
}

int Preprocess::printHelps() const
{
    cout << "usage: " << PACKAGE_NAME << " " << MODULE_NAME << " [arguments] [<inputs>]" << endl;
    cout << endl;
    cout << "\t-f[=<file>]      sequest result file" << endl; 
    cout << "\t-h               help" << endl;
    cout << endl;
    return HELP_RETURN;
}

int Preprocess::run(const Properties& options, const Arguments& arguments)
{
    if(!checkEnv())
    {
        return -1;
    }
    ofstream ofs(".tmp/preprocess.out");
    for(const string& filename : arguments)
    {
        ifstream ifs(filename.c_str());
        if(ifs.fail())
        {
            cerr << "cannot open file " << filename << endl;
            continue;
        }
        if(readSequestFile(ifs, ofs) != 0)
        {
            cerr << "read file error: " << filename << endl; 
            ifs.close();
            continue;
        }
        ifs.close();
    }
    ofs.close();
    return 0;
}

int Preprocess::readSequestFile(std::ifstream& ifs, std::ofstream& ofs)
{
    auto rmQuote = [](string s)->string{
        auto endPos = std::remove(s.begin(), s.end(), '\"');
        s.resize(endPos - s.begin());
        return std::forward<string>(s);
    };
    // assert ifs and ofs are valid
    string line;    
    std::getline(ifs, line);
    // first line must have headers
    vector<string> headers = split<string>(line, '\t', rmQuote);
    // generate map of index
    unordered_map<string, size_t> mp;
    for(size_t i = 0; i < headers.size(); ++i)
    {
        mp[headers[i]] = i;
    }
    string outHeaders[] = {
        "Sequence",
        "Modifications",
        "Charge",
        "Spectrum File",
        "First Scan",
        "XCorr",
        "Protein Group Accessions"
    };
    static const size_t COLNUM = sizeof(outHeaders) / sizeof(string);

    //ofs << join(outHeaders, outHeaders + COLNUM, '\t') << endl;

    while(std::getline(ifs, line))
    {
        vector<string> values = split<string>(line, '\t', rmQuote);
        vector<std::string> outValues;
        for(size_t i = 0;  i < COLNUM; ++i)
        {
            size_t index = mp[outHeaders[i]];
            outValues.push_back(values[index]);
        }

        ofs << join(outValues.begin(), outValues.end(), '\t') << endl;
    }
    return 0;
}

bool Preprocess::checkEnv() const
{
    static const char TMP_DIR[] = ".tmp";
    if(!dir_exists(TMP_DIR) && mkdir(TMP_DIR) != 0)
    {
        cerr << "mkdir fails!" << endl;
        return false;
    }
    return true;
}
