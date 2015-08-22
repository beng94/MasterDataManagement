#include "statistics.hpp"

#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <omp.h>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <boost/progress.hpp>

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
    //CsvParser *parser = CsvParser_new("testing_data.csv", ",", 0);
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

static int sum_of_pows_of_two(int bits)
{
    int sum = 0;
    int pow = 1;
    for(int i = 0; i < bits; i++)
    {
         sum += pow;
         pow <<= 1;
    }

    return sum;
}

void Statistics::read_ground_truth_file(std::unordered_map<int, std::vector<int>>& map)
{
    std::ifstream file(ground_truth_filename);
    try
    {
        std::string line;
        while(std::getline(file, line))
        {
            std::vector<std::string> chunks;
            split(line, ',', chunks);
            boost::trim(chunks[1]);

            int id_a = boost::lexical_cast<int>(chunks[0]);
            int id_b = boost::lexical_cast<int>(chunks[1]);

            auto find = map.find(id_a);
            if(find != map.end())
                find->second.push_back(id_b);
            else
                map.insert({id_a, {id_b}});
        }
        file.close();
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

static bool isDuplicate(int i, int j, std::unordered_map<int, std::vector<int>>& map)
{
    auto find = map.find(i);
    if(find != map.end())
    {
        std::vector<int> vec = find->second;
        return std::find(vec.begin(), vec.end(), j) != vec.end();
    }
    return false;
}

bool Statistics::calculate_oddsVector()
{
    std::vector<Entity> entities;
    entities.reserve(500000);
    read_training_data(entities);
    std::cout << "Training data read in" << std::endl;

    std::unordered_map<int, std::vector<int>> ground_truth_map;
    read_ground_truth_file(ground_truth_map);
    std::cout << "Ground truth file read in" << std::endl;

    //first for good guess, second for bad
    std::vector<std::pair<int, int>> counts (4096, {0, 0});

    std::cout << "Calculating state's shit" << std::endl;
    std::unordered_map<std::string, std::vector<Entity>> cluster_map;
    for(auto ent: entities)
    {
        auto find = cluster_map.find(ent.address.msState);
        if(find != cluster_map.end())
        {
            find->second.push_back(ent);
        }
        else
        {
            std::vector<Entity> new_vec;
            new_vec.reserve(15000);
            new_vec.push_back(ent);
            cluster_map.insert({ent.address.msState, new_vec});
        }
    }

    /*std::cout << "Calculating city's shit" << std::endl;
    for(auto state: cluster_map)
    {
        int size = state.second.size();
        if(size > 15000)
        {
            for(auto ent: state.second)
            {
                auto find = cluster_map.find(ent.address.msCityHash);
                if(find != cluster_map.end())
                {
                    find->second.push_back(ent);
                }
                else
                {
                    std::vector<Entity> new_vec;
                    new_vec.reserve(15000);
                    new_vec.push_back(ent);
                    cluster_map.insert({ent.address.msCityHash, new_vec});
                }
            }
        }
    }*/

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    std::time_t start_t = std::chrono::system_clock::to_time_t(start);

    std::cout << "" << std::ctime(&start_t) << " " << "Calculating output" << std::endl;
    std::cout << cluster_map.size() << std::endl;

    int cnt = 0;
    for(auto state: cluster_map)
    {
        std::cout << state.second[0].address.msState << " " << state.second[0].address.msCity << " " << state.second.size() << std::endl;
        int size = state.second.size();

        //if(size > 15000) continue;

        #pragma omp parallel for
        for(int i = 0; i < size; i++)
        {
            #pragma omp parallel for
            for(int j = i + 1; j < size; j++)
            {
                int cmp = state.second[i].BitMapMake(state.second[j]);
                if(isDuplicate(state.second[i].id, state.second[j].id, ground_truth_map))
                {
                    #pragma omp critical
                    counts[cmp].first++;
                }
                else
                {
                    #pragma omp critical
                    counts[cmp].second++;
                }
            }
        }
        std::cout << cluster_map.size() << "/" << cnt++ << std::endl;
        if(cnt == 47) break;
    }

    //Fill the oddsVector with probabilities
    oddsVector.reserve(counts.size());
    for(int i = 0; i < counts.size(); i++)
    {
        oddsVector.push_back(-1);
    }
    for(uint i = 0; i < counts.size(); i++)
    {
        if(counts[i].first == 0)
        {
            if(counts[i].second == 0)
            {
                oddsVector[i] = -1.0;
            }
            else oddsVector[i] = 0.0;
        }
        else if(counts[i].second == 0)
        {
            oddsVector[i] = 1.0;
        }
        else
        {
            //TODO: size < 50 -> -1
            oddsVector[i] = ((double)(counts[i].first)) / (double)(counts[i].first + counts[i].second);
        }
    }
    std::cout << "OddsVector calculated" << std::endl;

    std::ofstream file;
    file.open("oddsVector.txt");
    /*for(auto d: oddsVector)
    {
        file << (double)d << std::endl;
    }*/
    for(int i = 0; i< counts.size(); i++)
    {
         file << oddsVector[i] << " "<< counts[i].first << " " << counts[i].second << std::endl;
    }
    file.close();

    return true;
}

bool Statistics::calculate_and_save_results(const std::string& testing_data_filename,
                                            const std::string& result_filename)
{
    //TODO: implement functions
    return 0;
}

