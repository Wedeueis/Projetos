#include <vector>
#include <string>
#include <fstream>
#include "../inc/statistics.hpp"

/*
Container class from the samples stored in csv format
The datatype parameter defines if the features are labeled(for supervised tasks)
*/

enum datatype{
	LABELED,
	UNLABELED
};

class Data{
public:
	Data(datatype);
	Data(std::string filename, datatype);
	~Data();

	void init(std::string filename);
	void read(std::string filename);
	void add(Sample newsample);
	void remove(int id);

	std::vector<double> mean();
	std::vector<double> variance();
	std::vector<double> std_dev();
	void normalize();

	std::vector<Sample> getData();
	std::vector<Sample> getNormalizedData();
	int size();
	bool empty();

private:
	int setSize;
	Statistics st;
	std::vector<Sample> data;
	std::vector<Sample> norm_data;
	datatype type;
};