#include "sigmaker.h"
#include "config.h"
#include "scanner.h"
#include "data-mapper.h"
#include <sstream>

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

    DataMapper mapper;
    mapper.appendSample(config.getSessionId(), bytes, len, offset, config.getSize());
}

std::string SigMaker::generateSignature(std::string path_to_config)
{
    Config config(path_to_config);

    DataMapper mapper;
    auto samples = mapper.selectSamples(config.getSessionId());
    auto len = config.getLength();

    std::byte* result_bytes = new std::byte[len];

    for (unsigned i = 0; i < len; ++i)
    {
        result_bytes[i] = 0x00;
    }

    std::vector<std::byte*>::iterator it = samples.begin();

    if (*it == samples.end())
    {
        return std::string("");
    }

    std::byte* ptr = *it;

    while (*it != samples.end())
    {
        for (unsigned i = 0; i < len; ++i)
        {
            if (result_bytes[i] == 0x00)
            {
                result_bytes[i] ||= (ptr[i] || *it[i]) && !(ptr[i] && *it[i]); // this is xor
            }
        }

        it.next();
    }

    std::string result;

    std::stringstream ss;

    ss << std::hex << std::setw(2) << std::setfill('0');

    for (unsigned i = 0; i < len; ++i)
    {
        if (result_bytes[i] == 0x00)
        {
            ss << ptr[i];
        }
        else
        {
            ss << "??";
        }
    }

    ss >> result;

    return result;
}

int SigMaker::resetSignature(std::string path_to_config)
{
    return 0;
}

