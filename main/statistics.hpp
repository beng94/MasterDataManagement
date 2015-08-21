#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "../entity.hpp"

class Statistics {
  private:
    const std::string training_data_filename;
    const std::string ground_truth_filename;
    std::vector<double> oddsVector;
  public:
    Statistics(const std::string& training_data_filename,
               const std::string& ground_truth_filename)
               : training_data_filename(training_data_filename),
                 ground_truth_filename(ground_truth_filename)
    {}

    void read_training_data(std::vector<Entity>&);
    void read_ground_truth_file(std::unordered_map<int, std::vector<int>>&);
    bool calculate_oddsVector();
    bool calculate_and_save_results(const std::string& testing_data_filename,
                                    const std::string& result_filename);

    const std::vector<double>& get_oddsVector() { return oddsVector; }
};

#endif
