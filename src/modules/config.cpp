#include "config.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

Config::Config(std::string path_to_file)
{
    try {

        YAML::Node config = YAML::LoadFile(path_to_file);
        this->module_name = config["module"].as<std::string>();
        this->size = config["size"].as<unsigned int>();
        auto offsets = config["offsets"].as<std::vector<std::string>>();
        this->offsets = std::vector<long int>();

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
