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
    this->handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, this->pid);

    if (this->handle == NULL) {
        throw new std::exception("unable to get process handle");
    }
}

char* Scanner::readMemory(std::string module_name, std::vector<DWORD_PTR> offsets, int offset, unsigned int len)
{
    char* res = new char[len];

    DWORD_PTR base_addr = this->getModuleBaseAddr((TCHAR*)module_name.c_str());
    DWORD_PTR value_addr = this->getPointerAddr(base_addr, offsets);

    return res;
}

DWORD_PTR Scanner::getModuleBaseAddr(TCHAR* moduleName)
{
    DWORD_PTR moduleBaseAddr = NULL;
    DWORD bytesRequired;
    HMODULE modules[1024];

    bool success = EnumProcessModules(this->handle, modules, sizeof(modules), &bytesRequired);

    if (!success) {
        throw std::exception("unable to scan for modules");
    }

    unsigned int moduleCount = bytesRequired / sizeof(HMODULE);

    moduleBaseAddr = (DWORD_PTR)modules[0];

    if (moduleBaseAddr == NULL) {
        throw std::exception("unable to find module");
    }

    return moduleBaseAddr;
}

DWORD_PTR Scanner::getPointerAddr(DWORD_PTR base_addr, std::vector<DWORD_PTR> offsets)
{

    std::size_t pointer_size = sizeof(DWORD_PTR);

    if (this->is32BitPointer()) {
        pointer_size = sizeof(DWORD);
    }

    DWORD_PTR result = base_addr;
    DWORD_PTR new_value = NULL;

    for (auto offset : offsets)
    {
        result = base_addr + offset;
        std::cout << std::hex << result << std::endl;
        bool read = ReadProcessMemory(this->handle, (LPCVOID)(result), &new_value, pointer_size, NULL);

        if (!read) {
            throw new std::exception("unable to read memory");
        }

        base_addr = new_value;
    }

    return result;
}

bool Scanner::is32BitPointer()
{
    BOOL is_32_bit = false;
    return IsWow64Process(this->handle, &is_32_bit) && is_32_bit;
}

