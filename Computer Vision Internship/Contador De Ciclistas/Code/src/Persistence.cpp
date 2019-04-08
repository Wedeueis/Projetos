#include "Persistence.hpp"

Persistence::Persistence() {
    int ret = sqlite3_open(PERSIST_DB, &this->db);
    
    if (!SQLITE_OK == ret) {
            char error[20];
            sprintf(error, "Error opening database: %d", ret);
            LOG(error);
            sqlite3_free(error);
    }
}
    
Persistence::~Persistence() {
    sqlite3_close(this->db);
}

#include <sstream>
bool Persistence::Persist(std::string table, std::map<std::string, int> &tablemap) {
    std::stringstream ss;
    
    ss << "INSERT INTO " << table << " (";
    
    int num = tablemap.size();
    for (auto key: tablemap) {
        ss << key.first;
        if ((--num) > 0) {
            ss << ",";
        }
    }
    ss << ") values (";
    
    num = tablemap.size();
    for (auto key: tablemap) {
        ss << key.second;
        if ((--num) > 0) {
            ss << ",";
        }
    }
    ss << ")";
    
    char *error;
    int ret;
    
    ret = sqlite3_exec(this->db, ss.str().c_str(), NULL, NULL, &error);
    if(SQLITE_OK != ret){
      LOG(error);
      sqlite3_free(error);
    }
    
}
