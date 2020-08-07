#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <vector>
#include <windows.h>

class Config {

public:
    Config(std::string path_to_file);

    std::string getWindowName();
    std::string getSessionId();
    std::string getModuleName();
    std::vector<DWORD_PTR> getOffsets();
    unsigned int getSize();
    int getOffset();
    unsigned int getLength();

private:
    std::string session_id;
    std::string window_name;
    std::string module_name;
    std::vector<DWORD_PTR> offsets;
    unsigned int size;
    int offset;
    unsigned int len;
};

#endif
