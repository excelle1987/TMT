#ifndef LOAD_SPECTRUM_H
#define LOAD_SPECTRUM_H

#include <string>
#include <fstream>

class LoadSpectrum
{
public:
    LoadSpectrum() : 
        m_id(0),
        m_eol(0x0A),
        m_size(4096*4096)
    {}

    virtual ~LoadSpectrum(){}

    virtual bool get() const= 0;
    //virtual bool get(msSpectrum)
    virtual open(const string& path) = 0;
    int load_test(const char* path)

protected:
    size_t m_id;            // the id number of a spectrum
    std::streamsize m_size;
    std::string m_path;     // the path information for data file
    std::string m_test;

    char m_ecol; // the character chosen to mark the end-of-line, 0X0A or 0X0D

    std::ifstream m_ifs;
};

/** LoadDTA is publicly derived from LoadSpectrum. It overrides get and open to work with DTA files. Multiple ms/ms spectra can be placed in a single file by separating the spectra with at least one blank line. The DTA file format is as follows:

parent charge
mz1 I1
mz2 I2
...

where parent = the M+H mass of the parent ion in units
charge = the parent ion charge (1,2,3, etc.)
mzX = the mass-to-charge ratio of the Xth fragment ion
IX = the intensity of the Xth fragment ion
*/

class LoadDTA : public LoadSpectrum
{
public:
    LoadDTA();
    virtual ~LoadDTA();

    //virtual bool get(MsSpectrum& spec);
    virtual bool open(const std::string& filename);
    virtual bool open_force(const std::string& filename);

};


#endif  /*LOAD_SPECTRUM_H*/
