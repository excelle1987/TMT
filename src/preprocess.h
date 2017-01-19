#ifndef PREPROCESS_H
#define PREPROCESS_H

#include "runner.h"
#include <fstream>

class Preprocess : public Runner
{
public:
    virtual int run(const Properties& options, const Arguments& arguments) override;
    virtual ~Preprocess(){};
    virtual int printHelps() const override;

    int checkOptions(const Properties& options) const;

private:
    Preprocess();
    bool checkEnv() const;
    static int readSequestFile(std::ifstream& ifs, std::ofstream& ofs);

    static Preprocess s_runner;

};

#endif  /*PREPROCESS_H*/
