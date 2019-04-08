#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include "Config.hpp"

/**
 * @brief Base class to be extended by classes that read configuration
 */
class ConfigReader {
private:
    int processorId;
    Conf *cfg;
protected:
    /**
     * @param processorId Id of processo for which class applies
     * @param cfg Configuration instance
     */
    ConfigReader(int, Conf &);
    
    int GetProcessorId();
    int GetRoiId();
    Conf *GetConfiguration();
    
    /**
     * @brief Read processor specific configuration
     */
    int GetSpecificConf(std::string);
};

#endif
