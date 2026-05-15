#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <iostream>
#include <string>

extern "C" {
    #include "sqlite3.h"
}

class DatabaseManager {
public:
    DatabaseManager(const std::string& dbName) : dbName(dbName) {
        this->DB = nullptr;
        if (sqlite3_open(dbName.c_str(), &this->DB) != SQLITE_OK) {
            std::cerr << "Database connection failed: " << sqlite3_errmsg(this->DB) << std::endl;
            this->DB = nullptr;
        }
    }

    ~DatabaseManager() {
        if (this->DB != nullptr) {
            sqlite3_close(this->DB);
        }
    }

    bool executeQuery(const std::string& query) {
        if (this->DB == nullptr) return false;

        int result = sqlite3_exec(this->DB, query.c_str(), nullptr, nullptr, nullptr);
        return (result == SQLITE_OK);
    }

    sqlite3* getHandle() const {
        return this->DB;
    }

    // Returns true if the database connection is open and ready
    bool isConnected() const {
        return this->DB != nullptr;
    }

    // Returns the last SQLite error message, or empty string if no error
    std::string getLastError() const {
        if (this->DB == nullptr) return "";
        return std::string(sqlite3_errmsg(this->DB));
    }

    // Returns the name/path of the database file this manager was opened with
    std::string getDatabaseName() const {
        return this->dbName;
    }

private:
    sqlite3* DB;
    std::string dbName;
};

#endif // DATABASE_MANAGER_HPP
