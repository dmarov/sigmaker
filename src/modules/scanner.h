#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <string>
#include <vector>
#include <windows.h>

class Scanner {

private:
    std::string window_name;
    DWORD pid;
    HWND window;
    HANDLE handle;

public:
    Scanner(std::string window_name);

    std::vector<char> readMemory(std::string module_name, std::vector<long int> offsets, int before, int after);

private:
    DWORD_PTR getModuleBaseAddr(TCHAR* moduleName);
    DWORD getPointerAddr(DWORD_PTR baseAddr, std::vector<DWORD> offsets);
};

#endif
