#ifndef __DATA_MAPPER_H__
#define __DATA_MAPPER_H__

#include <string>
#include <sqlite3.h>

class DataMapper {

private:
    sqlite3 *handle;

public:
    DataMapper(std::string path_to_file);

    void appendSample(std::string id, std::byte* bytes, unsigned len, int offset, unsigned size);

    ~DataMapper();
private:
};

#endif
