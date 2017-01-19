#ifndef RUNNER_H
#define RUNNER_H

#include "util.h"
#include "config.h"
//#include "property_tree.h"
#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <map>
#include <algorithm>

using std::string;
using std::vector;
using std::map;
using std::tuple;
using std::cout;
using std::endl;

//using Properties = ptree<std::string, std::string>;
using Properties = std::map<std::string, std::string>;
using Arguments = std::vector<std::string>;

#ifndef HELP_RETURN
#define HELP_RETURN 256
#endif

class Runner
{
protected:
    string m_options;
    map<char, string> m_transform;
protected:
    Runner(const string& options = "", const map<char, string>& table = map<char, string>()) :
        m_options(options),
        m_transform(table)
    {}

public:
    const string& options() const
    { return m_options; }

    string transform(char key) const
    {
        auto it = m_transform.find(key);
        if(it != m_transform.end())
        {
            return it->second;
        }
        return string(1, key);
    }

    virtual int printHelps() const = 0;
    virtual int run(const Properties& options, const Arguments& arguments) = 0;
    virtual ~Runner(){};
};

using RunnerPtr = Runner*;

class RunnerManager
{
    struct cmp
    {
        map<string, size_t> mp;
        cmp()
        {
            mp["preprocess"] = 1;
            mp["report_ion_find"] = 2;
        }

        bool operator() (const string& lhs, const string& rhs) const
        {
            auto lIt = mp.find(lhs);
            auto rIt = mp.find(rhs);
            if(lIt != mp.end() && rIt != mp.end())
            {
                return lIt->second < rIt->second;
            }
            else if( lIt != mp.end())
            {
                return true;
            }
            else if(rIt != mp.end())
            {
                return false;
            }
            return lhs < rhs;
        }
    };
    using RunnerInfo = tuple<RunnerPtr, string>;
    using RunnerList = map<string, RunnerInfo, cmp>;

    RunnerList m_runners;
protected:
    RunnerManager()
    {}
public:
    virtual ~RunnerManager()
    {}

    static RunnerManager* get()
    {
        static RunnerManager mgr;
        return &mgr;
    }

    RunnerPtr create(const string& name) const
    {
        RunnerList::const_iterator it = m_runners.find(name);
        if(it != m_runners.end())
        {
            return std::get<0>(it->second);
        }
        return RunnerPtr();
    }

    bool install(const string& name, RunnerPtr runner, const string& introduction)
    {
        if(m_runners.find(name) != m_runners.end())
        {
            return false;
        }
        m_runners[name] = std::make_tuple(runner, introduction);
        return true;
    }

    bool uninstall(const string& name)
    {
        RunnerList::iterator it = m_runners.find(name);
        if(it != m_runners.end())
        {
            m_runners.erase(it);
            return true;
        }
        return false;
    }

    int help(int argc, char** argv) const
    {
        static string option("vh");
        int opt = -1;
        while((opt = getopt(argc, argv, option.c_str())) != -1)
        {
            switch((char) opt)
            {
            case 'v':
                cout << PACKAGE_NAME << " version " << PACKAGE_VERSION << endl;
                return HELP_RETURN;
            }
        }

        cout << PACKAGE_NAME << " version " << PACKAGE_VERSION << ", report bugs to " << PACKAGE_BUGREPORT << endl;
        cout << "usage: "<< PACKAGE_NAME << " <command> [<args>]" << endl;
        cout << endl;
        cout << "The most commonly used " << PACKAGE_NAME << " commands are:" << endl;

        {
            size_t max_name_length = 2;
            {
                vector<size_t> name_length;
                for(auto& runner : m_runners)
                {
                    name_length.push_back(runner.first.length());
                }
                if(!name_length.empty())
                {
                    max_name_length += *std::max_element(name_length.begin(), name_length.end());
                }
            }

            for(auto& runner : m_runners)
            {
                string cmd(runner.first);
                cmd.resize(max_name_length, ' ');
                std::cout << "\t" << cmd << std::get<1>(runner.second) << endl;
            }
        }

        cout << endl;
        cout << "See '" << PACKAGE_NAME << " <command> -h' to read about a specific subcommand." << endl;
        return HELP_RETURN;
    }
};

inline bool Runner_Install(const string& name, const RunnerPtr runner, const string& introduction)
{
    return RunnerManager::get()->install(name, runner, introduction);
}

inline bool Runner_Uninstall(const string& name)
{
    return RunnerManager::get()->uninstall(name);
}


#endif  /*RUNNER_H*/
