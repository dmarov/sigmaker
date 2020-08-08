#include "data-mapper.h"
#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <sqlite3.h>

DataMapper::DataMapper() throw(std::exception)
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
          "id         INTEGER PRIMARY KEY AUTOINCREMENT," \
          "file_hash  CHARACTER(32) NOT NULL," \
          "bytes      BLOB NOT NULL," \
          "length     INTEGER NOT NULL," \
          "offset     INTEGER NOT NULL," \
          "size       INTEGER NOT NULL" \
    ");";

    int rc;
    rc = sqlite3_exec(this->handle, sql, NULL, 0, NULL);

    if (rc != SQLITE_OK)
    {
        throw std::exception("unable to create database or table");
    }
}

void DataMapper::appendSample(std::string file_hash, std::byte* bytes, unsigned len, int offset, unsigned size) throw(std::exception)
{
    int rc;
    sqlite3_stmt* statement = NULL;

    rc = sqlite3_prepare_v2(
        this->handle,
        "INSERT INTO samples (file_hash, bytes, length, offset, size) VALUES (?,?,?,?,?);",
        -1,
        &statement,
        NULL
    );

    if (rc != SQLITE_OK)
    {
        throw new std::exception("unable to prepare statement");
    }

    std::cout << file_hash << std::endl;
    sqlite3_bind_text(statement, 1, file_hash.c_str(), file_hash.length(), NULL);
    sqlite3_bind_blob(statement, 2, bytes, len, SQLITE_STATIC);
    sqlite3_bind_int(statement, 3, len);
    sqlite3_bind_int(statement, 4, offset);
    sqlite3_bind_int(statement, 5, size);

    rc = sqlite3_step(statement);

    if (rc != SQLITE_DONE)
    {
        throw new std::exception("unable to insert sample");
    }

    sqlite3_finalize(statement);
}

DataMapper::~DataMapper()
{
    sqlite3_close(this->handle);
}
