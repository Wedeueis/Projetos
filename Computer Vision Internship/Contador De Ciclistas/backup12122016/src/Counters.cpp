#include "Counters.hpp"
#include <map>
#include <string>

void Counters::SetModuleName(std::string name) {
    this->moduleName = name;
}

void Counters::Add(std::string name, int value) {
    if (!this->countMap.count(name)) {
        this->countMap[name] = 0;
    }
    
    this->countMap[name] += value;
    this->PersistUpdate(name, value);
}

void Counters::Increment(std::string name) {
    this->Add(name, 1);
#ifdef DEBUG
    printf("Incrementing %s: %d\n", name.c_str(), countMap[name]);
#endif
}

void Counters::PersistUpdate(std::string name, int value) {
    std::map<std::string, int> record_map;
    record_map[name] = value;
    this->persistence.Persist(this->moduleName, record_map);
}

int Counters::Get(std::string name) {
    int retVal = 0;
    if (this->countMap.count(name)) {
        retVal = this->countMap[name];
    }
    return retVal;
}

