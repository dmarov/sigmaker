#include "sigmaker.h"
#include <iostream>

int SigMaker::appendRecord(std::string path_to_config)
{
    return 0;
}

std::string SigMaker::getSignature(std::string path_to_config)
{
    return std::string("00 A1 ?? ?? xx xx xx xx ?? 00 B1 ?? ??");
}

int SigMaker::resetSignature(std::string path_to_config)
{
    return 0;
}
