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

    for (unsigned i = 0; i < config.getLength(); ++i)
    {
        std::cout << std::hex << (int) bytes[i] << " ";
    }

    std::cout << std::endl;
}

std::string SigMaker::getSignature(std::string path_to_config)
{
    return std::string("");
}

int SigMaker::resetSignature(std::string path_to_config)
{
    return 0;
}

