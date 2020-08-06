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
}

std::vector<char> readMemory(std::string module_name, std::vector<DWORD_PTR> offsets, int before, int after)
{
    std::vector<char> res;

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

DWORD Scanner::getPointerAddr(DWORD_PTR baseAddr, std::vector<DWORD> offsets)
{
    DWORD_PTR result = baseAddr;
    DWORD_PTR newValue;

    for (auto offset : offsets)
    {
        result = baseAddr + offset;
        bool read = ReadProcessMemory(this->handle, (LPCVOID)(result), &newValue, sizeof(newValue), NULL);

        if (!read) {
            throw new std::exception("unable to read memory");
        }

        baseAddr = newValue;
    }

    return result;
}

