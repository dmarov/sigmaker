#include "data-mapper.h"
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <sqlite3.h>

DataMapper::DataMapper()
{
    const char* home_dir_str = getenv("USERPROFILE");
    std::filesystem::path file_path(home_dir_str);

    file_path /= ".config";
    file_path /= "sigmaker";
    std::filesystem::create_directories(file_path.string().c_str());
    file_path /= "sigmaker.sqlite";

    auto uri = file_path.string();

    std::replace(uri.begin(), uri.end(), '\\', '/');
    sqlite3_open(uri.c_str(), &this->handle);

    char* sql = "CREATE TABLE IF NOT EXISTS samples("  \
          "id         INT PRIMARY KEY NOT NULL," \
          "file_hash  CHAR[60] NOT NULL," \
          "bytes      BLOB NOT NULL," \
          "length     INT NOT NULL," \
          "offset     INT NOT NULL," \
          "size       INT NOT NULL" \
    ");";

    int rc;
    rc = sqlite3_exec(this->handle, sql, NULL, 0, NULL);

    if (rc != SQLITE_OK)
    {
        throw std::exception("unable to create database or table");
    }
}

void DataMapper::appendSample(std::string file_hash, std::byte* bytes, unsigned len, int offset, unsigned size)
{

    /* int rc; */
    /* sqlite3_stmt* statement = NULL; */

    /* rc = sqlite3_prepare( */
    /*     this->handle, */
    /*     "INSERT INTO samples(file_hash, bytes, length, offset, size) VALUES(?,?,?,?,?)", */
    /*     -1, */
    /*     &statement, */
    /*     NULL */
    /* ); */

    /* if (rc != SQLITE_OK) */
    /* { */
    /*     throw new std::exception("unable to prepare statement"); */
    /* } */

    /* sqlite3_bind_text(statement, 1, file_hash.c_str(), file_hash.length(), NULL); */
    /* sqlite3_bind_blob(statement, 2, bytes, len, SQLITE_STATIC); */
    /* sqlite3_bind_int(statement, 3, len); */
    /* sqlite3_bind_int(statement, 4, offset); */
    /* sqlite3_bind_int(statement, 5, size); */

    /* rc = sqlite3_step(statement); */
    /* sqlite3_finalize(statement); */

    /* if (rc != SQLITE_DONE) */
    /* { */
    /*     throw new std::exception("unable to insert sample"); */
    /* } */

    for (unsigned i = 0; i < len; ++i)
    {
        std::cout << std::hex << (int) bytes[i] << " ";
    }

    std::cout << std::endl;
}

DataMapper::~DataMapper() {

    sqlite3_close(this->handle);

}
