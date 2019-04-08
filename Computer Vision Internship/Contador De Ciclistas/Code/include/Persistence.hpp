#ifndef PERSISTENCE_HPP
#define PERSISTENCE_HPP

#define PERSIST_DB "EOC.db"
#define LOG(msg) printf("LOG: %s\n", msg)

#include "Config.hpp"
#include <sqlite3.h> 
#include <map>

/**
 * @brief Data persistence functionality
 */
class Persistence {
private:
    sqlite3 *db;
public:
    Persistence();    
    ~Persistence();
    bool Persist(std::string, std::map<std::string, int> &);
};

#endif
