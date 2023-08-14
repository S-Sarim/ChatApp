#ifndef __SQLITE_HPP__
#define __SQLITE_HPP__

#include "C:\MinGW64\opt\include\sqlite3.h"
#include <string>
#include <cassert>
#include <exception>

class SQLite
{
private:
    sqlite3 *db;
    SQLite() ;

public:
    static void run(const std::string &command, int (*callback)(void *, int, char **, char **) = nullptr, void *callbackArg = nullptr);
    ~SQLite() ;
    SQLite(const SQLite &) = delete;
    SQLite operator=(const SQLite &) = delete;
};

class SQLiteEx : public std::exception
{
private:
    std::string message;

public:
    SQLiteEx(char *message, bool freeMemory = true);
    SQLiteEx(const std::string &message);
    const char *what() const noexcept override;
};

SQLite::SQLite() 
{
    if (sqlite3_open("ChatApp.db", &db) != SQLITE_OK) {
        throw "Cannot open database.";
    }
    // assert(sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr) == SQLITE_OK);
}

void SQLite::run(const std::string &command, int (*callback)(void *, int, char **, char **), void *callbackArg)
{
    static SQLite database;
    char *errorMsg = nullptr;
    if (sqlite3_exec(database.db, command.c_str(), callback, callbackArg, &errorMsg) != SQLITE_OK)
    {
        throw SQLiteEx(errorMsg);
    }
}

SQLite::~SQLite() 
{
    sqlite3_close(db);
}

SQLiteEx::SQLiteEx(char *message, bool freeMemory) : SQLiteEx(std::string(message))
{
    if (freeMemory)
    {
        sqlite3_free(message);
    }
}

SQLiteEx::SQLiteEx(const std::string &message) : message("SQLiteEx: " + message)
{
}

const char *SQLiteEx::what() const noexcept
{
    return message.c_str();
}



#endif // __SQLITE_HPP__