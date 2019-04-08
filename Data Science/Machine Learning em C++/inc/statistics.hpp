#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

/*
Auxiliary class to calculate characteristics from the data distribution 
*/

struct Sample{
	std::vector<double> features;
	int label;
	int size;
};

class Statistics {
public:
	Statistics();
	Statistics(std::size_t);
	~Statistics();
	std::vector<double> getMean(std::vector<Sample>);
	std::vector<double> getVariance(std::vector<Sample>);
	std::vector<double> getStdDev(std::vector<Sample>);
	std::vector<Sample> normalize(std::vector<Sample>);
	void setChange(int, bool);
private:
	std::vector<double> mean;
	std::vector<double> variance;
	std::vector<double> std_dev;
	bool changed[3];
};
