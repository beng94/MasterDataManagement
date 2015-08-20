#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "statistics.hpp"
#include "../csvparser.h"

static char** parse_line(CsvParser *parser)
{
    CsvRow *row = CsvParser_getRow(parser);
    if(row == NULL) throw std::out_of_range("");

    return CsvParser_getFields(row);
}

void Statistics::read_training_data(std::vector<Entity>& vec)
{
    CsvParser *parser = CsvParser_new(training_data_filename.c_str(), ",", 0);
    std::vector<Entity> entities_vec;

    while(true)
    {
        try
        {
            char **rowFields = parse_line(parser);

            int id = boost::lexical_cast<int>(rowFields[0]);
            Name name(trim(std::string(rowFields[1])));
            CAddress address(std::string(trim(rowFields[2])));
            Taxonomies taxonomies(std::string(trim(rowFields[3])));
            Entity entity(id, name, address, taxonomies);

            vec.push_back(entity);
        }
        catch (std::out_of_range& oor) 
          {
            std::cerr << "statistics.cpp: Exception thrown near initializing Entity fields" << std::endl;
            break; 
          }
    }
    CsvParser_destroy(parser);
}

bool Statistics::calculate_oddsVector()
{
    //TODO: LOTS OF FUMCTIONS ABOVE
    std::vector<Entity> entities;
    entities.reserve(450000);
    read_training_data(entities);

    return true;
}

bool Statistics::calculate_and_save_results(const std::string& testing_data_filename, 
                                            const std::string& result_filename)
{
    //TODO: implement functions
    return 0; 
}
