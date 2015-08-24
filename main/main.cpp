#include <iostream>
#include "statistics.hpp"

const std::string training_data_filename = "training_data.csv";
const std::string ground_truth_filename = "training_ground_truth.csv";
const std::string testing_data_filename = "testing_data.csv";
//for the results of the running
const std::string result_filename = "results.csv";

int main()
{
  Statistics stats(training_data_filename, ground_truth_filename);
  stats.calculate_and_save_results("boci", "buu");
  /*if (!stats.calculate_oddsVector())
    {
      std::cerr << "Global Error: calculating oddsVector was unsuccessful" << std::endl;
      return 1;
    }
  if (!stats.calculate_and_save_results(testing_data_filename, result_filename))
    {
      std::cerr << "Global Error: calculating results was unsuccessful" << std::endl;
      return 2;
    }*/
  return 0;
}
