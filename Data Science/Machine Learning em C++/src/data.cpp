#include "../inc/data.hpp"

/*
Container class from the samples stored in csv format
The datatype parameter defines if the features are labeled(for supervised tasks)
*/

Data::Data(std::string filename, datatype type){
  init(filename);
  this->type = type;
}

Data::Data(datatype type){
  this->type = type;
}

Data::~Data(){
}

void Data::init(std::string filename){
  read(filename);
  st = Statistics(data.size());
  norm_data = data;
}

int Data::size(){
  return setSize;
}

bool Data::empty(){
  if(data.data()) return false;
  else return true;
}

void Data::read(std::string filename) {
  std::ifstream in(filename.data(), std::ios::in);
    if (!in) {
        std::cerr << "Failed to open input file" << std::endl;
        return;
    }
    std::string row;
    int lines = 0;
    while (true) {
        std::getline(in, row);
        if (in.bad() || in.eof()) {
            break;
        }
        lines++;
        int state = 0;
        std::vector<std::string> fields {""};
        size_t i = 0; // index of the current field
        for (char c : row) {
            switch (state) {
                case 0:
                    switch (c) {
                        case ',': // end of field
                                  fields.push_back(""); i++;
                                  break;
                        case '"': state = 1;
                                  break;
                        default:  fields[i].push_back(c);
                                  break; }
                    break;
                case 1:
                    switch (c) {
                        case '"': state = 2;
                                  break;
                        default:  fields[i].push_back(c);
                                  break; }
                    break;
                case 2:
                    switch (c) {
                        case ',': // , after closing quote
                                  fields.push_back(""); i++;
                                  state = 0;
                                  break;
                        case '"': // "" -> "
                                  fields[i].push_back('"');
                                  state = 1;
                                  break;
                        default:  // end of quote
                                  state = 0;
                                  break; }
                    break;
            }
        }
        Sample sample;
        if(type == LABELED){
          sample.label = std::stoi(fields.back());
          fields.pop_back();
        }
        std::vector<double> doubleVector(fields.size());
        std::transform(fields.begin(), fields.end(), doubleVector.begin(),
                [](std::string const& val) {return std::stod(val);});
        sample.features = doubleVector;
        sample.size = fields.size();
        data.push_back(sample);
        }
        setSize = lines;

}

std::vector<Sample> Data::getData(){
  return this->data;
}

std::vector<Sample> Data::getNormalizedData(){
  return this->norm_data;
}

std::vector<double> Data::mean(){
  return st.getMean(data);
}

std::vector<double> Data::variance(){
  return st.getVariance(data);
}

std::vector<double> Data::std_dev(){
  return st.getStdDev(data);
}

void Data::normalize(){
  norm_data = st.normalize(data);
}

