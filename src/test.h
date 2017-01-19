#ifndef TEST_H
#define TEST_H

#include "runner.h"

class Test : public Runner
{
public:
    virtual int run(const Properties& options, const Arguments& arguments) override;
    virtual ~Test(){};
private:
    Test();

public:
    int checkOptions(const Properties& options) const;
    virtual int printHelps() const override;

private:
    static Test s_runner;
};

#endif  /*TEST_H*/
