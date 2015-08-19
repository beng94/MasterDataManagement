#include <iostream>
#include <vector>
#include <string>
#include "../entity.hpp"

class Entity_container {
  private:
    const std::vector<double>& oddsVector;
    const std::string& result_filename;
    std::vector<Entity> entities;
  public:
    Entity_container(const std::vector<double>& oddsVector,
                     const std::string& result_filename)
                     : oddsVector(oddsVector),
                       result_filename(result_filename)
                       {}
    bool calculate_and_save_results(const std::string& result_filename);
};
