#include "../inc/statistics.hpp"

/*
Auxiliary class to calculate characteristics from the data distribution 
*/

using namespace std;

Statistics::Statistics(size_t featuresSize){
	for(size_t j = 0; j<featuresSize; j++){
		mean.push_back(0);
		variance.push_back(0);
		std_dev.push_back(0);
	}
	for(size_t i = 0; i<3; i++)
		changed[i] = true;
}

Statistics::Statistics(){}

Statistics::~Statistics(){}

vector<double> Statistics::getMean(vector<Sample> data){
    if(changed[0]){
      vector<double> sum = data[0].features;
      for(size_t i = 1; i<data.size(); i++)
      	for(size_t j = 0; j<sum.size(); j++)
        	sum[j] += data[i].features[j];

      for(size_t j = 0; j<sum.size(); j++)
      	mean[j] = sum[j]/data.size();

      changed[0] = false;
    }
    return mean;
}

vector<double> Statistics::getVariance(vector<Sample> data) {
  if(changed[1]){
    vector<double> mean = getMean(data);
    vector<double> temp(mean.size());
    for(size_t i = 0; i<data.size(); i++)
    	for(size_t j = 0; j<mean.size(); j++)
        	temp[j] += (data[i].features[j]-mean[j])*(data[i].features[j]-mean[j]);

    for(size_t j = 0; j<mean.size(); j++)
    	variance[j] = temp[j]/data.size();

    changed[1] = false;
  }
  return variance;
}

vector<double> Statistics::getStdDev(vector<Sample> data) {
  if(changed[2]){
  	vector<double> var = getVariance(data);
  	for(size_t j = 0; j<std_dev.size(); j++)
    	std_dev[j] = sqrt(var[j]);

    changed[2] = false;
  }
  return std_dev;
}

vector<Sample> Statistics::normalize(vector<Sample> data){
	vector<Sample> samples;
	vector<double> norm(data[0].features.size());

	for(size_t i = 0; i<data.size(); i++){
		double max =  (double)*max_element(begin(data[i].features), end(data[i].features));
		for(size_t j = 0; j < norm.size(); j++){
			norm[j] = data[i].features[j]/ max;
		}
		Sample s;
		s.label = data[i].label;
		s.features = norm;
		s.size = norm.size();
		samples.push_back(s);
	}
	return samples;
}

void Statistics::setChange(int pos, bool value){
	changed[pos] = value;
}