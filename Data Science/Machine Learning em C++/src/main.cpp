#include "../inc/data.hpp"

/*
Usage test for the Data class
*/

int main(){
  Data set("../../inc/data.csv", LABELED);
  std::cout << "Data" << std::endl;
  if(!set.empty())
    for(int i=0; i< set.size(); i++){
      for(int j = 0; j<set.getData()[i].size; j++)
        std::cout << set.getData()[i].features[j] << " ";
      std::cout << set.getData()[i].label << std::endl;
    }
   set.mean();
   set.variance();
   set.std_dev();
   set.normalize();
   std::cout << std::endl;

   std::cout << "Normalized Data" << std::endl;
   for(int i=0; i< set.size(); i++){
      for(int j = 0; j<set.getNormalizedData()[i].size; j++)
      	std::cout << set.getNormalizedData()[i].features[j] << " ";
      std::cout << std::endl;
   }

   std::cout << "Mean" << std::endl;
   for(size_t j = 0; j<set.mean().size(); j++)
      	std::cout << set.mean()[j] << " ";
    std::cout << std::endl;

   std::cout << "Variance" << std::endl;
   for(size_t j = 0; j<set.mean().size(); j++)
      	std::cout << set.variance()[j] << " ";
   std::cout << std::endl;

   std::cout << "Standard Deviation" << std::endl;
   for(size_t j = 0; j<set.mean().size(); j++)
      	std::cout << set.std_dev()[j] << " ";
   std::cout << std::endl;

   std::cout << "Sucess!" << std::endl;
}