#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <string>
#include <vector>

class Scanner {

public:
    Scanner(std::string window_name);

    std::vector<char> readMemory(std::string module_name, std::vector<long int> offsets, int before, int after);

private:
};

#endif
