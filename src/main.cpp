#include "runner.h"
#include <iostream>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        return RunnerManager::get()->help(argc, argv);
    }

    RunnerPtr runner = RunnerManager::get()->create(argv[1]);
    if(!runner)
    {
        return RunnerManager::get()->help(argc, argv);
    }
    if(argc == 2)
    {
        return runner->printHelps();
    }

    Properties options;
    {
        // command line options
        Properties cmd;
        const string& opt_string = runner->options();
        int opt = -1;
        while((opt = getopt(argc - 1, argv + 1, opt_string.c_str())) != -1)
        {
            string key = runner->transform((char)opt);
            if(optarg == NULL)
            {
                cmd.insert(make_pair(key, string()));
            }
            else
            {
                string val = optarg;
                if(cmd.find(key) != cmd.end())
                {
                    val = cmd[key] + val;
                }
                cmd.insert(make_pair(key, val));
            }
        }

        options = cmd;
    }

    Arguments arguments;
    for(int i = optind + 1; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }
    return runner->run(options, arguments);
}
