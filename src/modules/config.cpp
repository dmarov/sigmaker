#include "config.h"
#include <iostream>
#include <windows.h>
#include <yaml-cpp/yaml.h>

Config::Config(std::string path_to_file)
{
    try {

        YAML::Node config = YAML::LoadFile(path_to_file);
        this->module_name = config["module"].as<std::string>();
        this->window_name = config["window"].as<std::string>();
        this->size = config["size"].as<unsigned int>();
        auto offsets = config["offsets"].as<std::vector<std::string>>();
        this->offsets = std::vector<DWORD_PTR>();
        this->offset = -50;
        this->len = 100;

        if (config["offset"]) {
            this->offset = config["offset"].as<unsigned int>();
        }

        if (config["length"]) {
            this->len = config["length"].as<unsigned int>();
        }

        std::cout << this->module_name << std::endl;

        for(auto offset : offsets)
        {
            unsigned long offset_int;
            std::stringstream ss;

            ss << std::hex << offset;
            ss >> offset_int;
            this->offsets.push_back(offset_int);
        }

    } catch(std::exception &e) {
        std::cerr << "failed to parse config" << std::endl;
        throw e;
    }
}


std::string Config::getWindowName()
{
    return this->window_name;
}

std::string Config::getSessionId()
{
    return this->session_id;
}

std::string Config::getModuleName()
{
    return this->module_name;
}

std::vector<DWORD_PTR> Config::getOffsets()
{
    return this->offsets;
}

unsigned int Config::getSize()
{
    return this->size;
}

int Config::getOffset()
{
    return this->offset;
}

unsigned int Config::getLength()
{
    return this->len;
}
