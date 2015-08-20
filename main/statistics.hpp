#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include "../entity.hpp"
#include "../csvparser.h"
#include "../string_handle.hpp"

const int STASH_COUNT= 12;

class Statistics {
  private:
    const std::string training_data_filename;
    const std::string ground_truth_filename;
    std::vector<double> oddsVector;
  public:
    Statistics(const std::string& training_data_filename,
               const std::string& ground_truth_filename)
               : training_data_filename(training_data_filename),
                 ground_truth_filename(ground_truth_filename),
                 oddsVector(STASH_COUNT,0.5)
                 {}

    void read_training_data(std::vector<Entity>&);
    bool calculate_oddsVector();
    bool calculate_and_save_results(const std::string& testing_data_filename,
                                    const std::string& result_filename);

    const std::vector<double>& get_oddsVector() { return oddsVector; }
};

#endif
