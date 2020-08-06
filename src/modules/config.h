#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <vector>

class Config {

public:
    Config(std::string path_to_file);

private:
    std::string session_id;
    unsigned int before;
    unsigned int after;
    std::string module_name;
    std::vec<long int> offsets;
};

#endif
