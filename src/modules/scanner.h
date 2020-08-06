#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <string>
#include <vector>

class Scanner {

public:
    Scanner(std::string window_name);

    std::vec<char> readMemory(std::string moduleName, std::vec<char> pointer, int before, int after);

private:
};

#endif
