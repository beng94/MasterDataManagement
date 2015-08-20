#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <string>
#include "../entity.hpp"

const int BITMAP_SIZE = 12;

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
    {
        oddsVector.reserve(1 << BITMAP_SIZE);
    }

    void read_training_data(std::vector<Entity>&);
    bool calculate_oddsVector();
    bool calculate_and_save_results(const std::string& testing_data_filename,
                                    const std::string& result_filename);

    const std::vector<double>& get_oddsVector() { return oddsVector; }
};

#endif
