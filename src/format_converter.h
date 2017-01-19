#ifndef FORMAT_CONVERTER_H
#define FORMAT_CONVERTER_H

#include "runner.h"
#include <fstream>

class FormatConverter : public Runner
{
public:
    virtual int run(const Properties& options, const Arguments& arguments) override;
    virtual ~FormatConverter(){};
    virtual int printHelps() const override;

    int checkOptions(const Properties& options) const;

private:
    FormatConverter();

    static FormatConverter s_runner;

}


#endif  /*FORMAT_CONVERTER_H*/
