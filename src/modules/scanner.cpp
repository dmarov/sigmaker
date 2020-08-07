#include "scanner.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <psapi.h>

Scanner::Scanner(std::string window_name)
{
    this->window_name = window_name;
    this->window = FindWindowA(NULL, window_name.c_str());
    GetWindowThreadProcessId(this->window, &(this->pid));
    this->handle = OpenProcess(PROCESS_VM_READ, FALSE, this->pid);

    if (this->handle == NULL) {
        throw new std::exception("unable to get process handle");
    }
}

char* Scanner::readMemory(std::string module_name, std::vector<DWORD_PTR> offsets, int offset, unsigned int len)
{
    char* res = new char[len];

    DWORD_PTR base_addr = this->getModuleBaseAddr((TCHAR*)module_name.c_str());
    /* DWORD_PTR value_addr = this->getPointerAddr(base_addr, offsets); */

    return res;
}

DWORD_PTR Scanner::getModuleBaseAddr(TCHAR* moduleName)
{
    DWORD_PTR moduleBaseAddr = NULL;
    DWORD bytesRequired;

    bool success = EnumProcessModules(this->handle, NULL, 0, &bytesRequired);

    if (!success) {
        throw std::exception("unable to scan for modules");
    }

    LPBYTE moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);

    unsigned int moduleCount;

    moduleCount = bytesRequired / sizeof(HMODULE);
    HMODULE* moduleArray = (HMODULE *)moduleArrayBytes;

    success = EnumProcessModules(this->handle, moduleArray, bytesRequired, &bytesRequired);

    if (!success) {
        throw std::exception("unable to scan for modules");
    }

    moduleBaseAddr = (DWORD_PTR)moduleArray[0];

    LocalFree(moduleArrayBytes);

    if (moduleBaseAddr == NULL) {
        throw std::exception("unable to find module");
    }

    return moduleBaseAddr;
}

DWORD_PTR Scanner::getPointerAddr(DWORD_PTR baseAddr, std::vector<DWORD_PTR> offsets)
{
    DWORD_PTR result = baseAddr;
    DWORD_PTR new_value;

    for (auto offset : offsets)
    {
        result = baseAddr + offset;
        bool read = ReadProcessMemory(this->handle, (LPCVOID)(result), &new_value, sizeof(new_value), NULL);

        if (!read) {
            throw new std::exception("unable to read memory");
        }

        baseAddr = new_value;
    }

    return result;
}

