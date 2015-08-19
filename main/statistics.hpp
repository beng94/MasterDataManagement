#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <string>
#include "entity_container.hpp"

const int STASH_COUNT= 12;

class Statistics {
  private:
    const std::string training_data_filename;
    const std::string ground_truth_filename;
    std::vector<double> oddsVector;
    Entity_container* training_ents;  //This will be handled with dinamic allocation
  public:
    Statistics(const std::string& training_data_filename,
               const std::string& ground_truth_filename)
               : training_data_filename(training_data_filename),
                 ground_truth_filename(ground_truth_filename),
                 oddsVector(STASH_COUNT,0.5)
                 {}
    bool calculate_oddsVector();
    const std::vector<double>& get_oddsVector() { return oddsVector; }
};

#endif
