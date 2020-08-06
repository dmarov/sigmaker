#include "sigmaker.h"
#include "config.h"
#include "scanner.h"
#include <iostream>

void SigMaker::appendRecord(std::string path_to_config)
{
    Config config(path_to_config);
    Scanner scanner(config.getWindowName());

    auto bytes = scanner.readMemory(config.module_name, config.offsets, config.before, config.after);

}

std::string SigMaker::getSignature(std::string path_to_config)
{
    return std::string("00 A1 ?? ?? xx xx xx xx ?? 00 B1 ?? ??");
}

int SigMaker::resetSignature(std::string path_to_config)
{
    return 0;
}

