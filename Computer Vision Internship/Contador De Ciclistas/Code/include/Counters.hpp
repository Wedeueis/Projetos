#ifndef COUNTERS_HPP
#define COUNTERS_HPP

#include "Persistence.hpp"
#include <map>
#include <string>

/**
 * @brief Data abstraction for object classification to be persisted
 */
class Counters {
private:
    std::map <std::string, int> countMap;
    Persistence persistence;
    void PersistUpdate(std::string name, int value);
    std::string moduleName;
public:
    void SetModuleName(std::string);
    void Add(std::string name, int value);
    void Increment(std::string name);
    int Get(std::string name);

};

#endif
