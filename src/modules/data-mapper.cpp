#include "data-mapper.h"
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <sqlite3.h>

DataMapper::DataMapper(std::string path_to_file)
{
    const char* home_dir_str = getenv("USERPROFILE");
    std::filesystem::path file_path(home_dir_str);

    file_path /= ".config";
    file_path /= "sigmaker";
    std::filesystem::create_directories(file_path.string().c_str());
    file_path /= "db.sqlite";

    auto uri = file_path.string();

    std::replace(uri.begin(), uri.end(), '\\', '/');
    std::cout << uri << std::endl;
    sqlite3_open(uri.c_str(), &this->handle);

    char* sql = "CREATE TABLE samples("  \
          "id INT     PRIMARY KEY  NOT NULL," \
          "file_hash  CHAR[60]     NOT NULL," \
          "bytes      BLOB         NOT NULL," \
          "length     INT          NOT NULL," \
          "offset     INT          NOT NULL," \
          "size       INT          NOT NULL" \
    ");";

    int rc;
    rc = sqlite3_exec(this->handle, sql, NULL, 0, NULL);

    if (rc != SQLITE_OK)
    {
        throw std::exception("unable to create database or table");
    }
}

void DataMapper::appendSample(std::string id, std::byte* bytes, unsigned len, int offset, unsigned size)
{

    for (unsigned i = 0; i < len; ++i)
    {
        std::cout << std::hex << (int) bytes[i] << " ";
    }

    std::cout << std::endl;
}

DataMapper::~DataMapper() {

    sqlite3_close(this->handle);

}
