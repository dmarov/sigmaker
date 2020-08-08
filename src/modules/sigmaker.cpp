#include "sigmaker.h"
#include "config.h"
#include "scanner.h"
#include "data-mapper.h"

void SigMaker::appendSample(std::string path_to_config)
{
    Config config(path_to_config);
    Scanner scanner(config.getWindowName());

    auto len = config.getLength();
    auto offset = config.getOffset();

    std::byte* bytes = scanner.readMemory(
        config.getModuleName(),
        config.getOffsets(),
        offset,
        len
    );

    DataMapper mapper(path_to_config);
    mapper.appendSample(config.getSessionId(), bytes, len, offset, config.getSize());

    delete [] bytes;
}

std::string SigMaker::getSignature(std::string path_to_config)
{
    return std::string("");
}

int SigMaker::resetSignature(std::string path_to_config)
{
    return 0;
}

