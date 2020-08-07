#include "sigmaker.h"
#include "config.h"
#include "scanner.h"
#include <iostream>

void SigMaker::appendSample(std::string path_to_config)
{
    Config config(path_to_config);
    Scanner scanner(config.getWindowName());

    auto bytes = scanner.readMemory(
        config.getModuleName(),
        config.getOffsets(),
        config.getOffset(),
        config.getLength()
    );

    std::cout << config.getLength() << std::endl;
    for (unsigned i = 0; i < config.getLength(); ++i)
    {
        std::cout << std::hex << bytes[i] << " ";
    }
    std::cout << std::endl;
}

std::string SigMaker::getSignature(std::string path_to_config)
{
    return std::string("00 A1 ?? ?? xx xx xx xx ?? 00 B1 ?? ??");
}

int SigMaker::resetSignature(std::string path_to_config)
{
    return 0;
}

