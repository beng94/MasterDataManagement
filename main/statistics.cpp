#include "statistics.hpp"

#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <tuple>

#include "../csvparser.h"
#include "../string_handle.hpp"

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

            Entity entity(boost::lexical_cast<int>(rowFields[0]),
                          trim(std::string(rowFields[1])),
                          std::string(trim(rowFields[2])),
                          std::string(trim(rowFields[3])));

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

static bool isDuplicate(int i, int j)
{

}

bool Statistics::calculate_oddsVector()
{
    //TODO: LOTS OF FUMCTIONS ABOVE
    std::vector<Entity> entities;
    entities.reserve(450000);
    read_training_data(entities);

    //first for good guess, second for bad
    std::vector<std::pair<int, int>> counts;
    //counts size should be 2^bits
    counts.reserve(1 << BITMAP_SIZE);

    //size or length or sth else?
    for(int i = 0; i < entities.size(); i++)
    {
        for(int j = i + 1; j < entities.size(); j++)
        {
            //to generate the bitmap, that we'll use as an index for the
            //oddsVector and counts
            int cmp = entities_cmp(entities[i], entities[j]);

            //isDuplicate should look for the given ids in the ground_truth file
            if(isDuplicate(i, j)) counts[cmp].first++;
            else counts[cmp].second++;
        }
    }

    //Fill the oddsVector with probabilities
    for(int i = 0; i < counts.size(); i++)
    {
        oddsVector[i] = counts[i].first / (counts[i].first + counts[i].second);
    }

    return true;
}

bool Statistics::calculate_and_save_results(const std::string& testing_data_filename,
                                            const std::string& result_filename)
{
    //TODO: implement functions
    return 0;
}

