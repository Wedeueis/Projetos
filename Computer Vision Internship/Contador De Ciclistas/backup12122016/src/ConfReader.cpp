#include "ConfigReader.hpp"

ConfigReader::ConfigReader(int processorId, Conf &cfg) {
    this->processorId = processorId;
    this->cfg = &cfg;
}

int ConfigReader::GetProcessorId() {
    return this->processorId;
}

Conf *ConfigReader::GetConfiguration() {
    return this->cfg;
}

int ConfigReader::GetRoiId() {
    int processorId = this->GetProcessorId();
    int roiId = this->GetConfiguration()->processorIdROI(processorId);
    return roiId;
}

int ConfigReader::GetSpecificConf(std::string propertyName) {
    return this->GetConfiguration()->processorIntConf(this->GetProcessorId(), propertyName);
}
