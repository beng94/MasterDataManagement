#include <iostream>
#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <fstream>

#include "data.hpp"

std::string
trim(char *s)
{
    std::string str(s);
    boost::trim(str);

    return str;
}

std::string
trim(std::string str)
{
    boost::trim(str);
    return str;
}

std::string
join(std::vector<std::string>& vec, char sep, int start, int end)
{
    std::string str = "";
    for(int i = start; i <= end; i++)
    {
        if(i != end)
            str += vec.at(i) + sep;
        else
            str += vec.at(i);
    }

    return str;
}

void
char_remove(std::string& str, std::string remove_chars)
{
    for(auto c: remove_chars)
        str.erase (std::remove(str.begin(), str.end(), c), str.end());
}

/*splits the given str by delim and stores the chunks in elems*/
std::vector<std::string>&
split(const std::string &str, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

//TODO: what about INC?
std::unordered_map<std::string, std::string> specs_map =
{
    {"PHD", "majom"},
    {"MD", ""},
    {"PA", ""},
    {"DDS", ""},
    {"CNP", ""},
    {"ATC", ""},
    {"LAT", ""},
    {"CRNA", ""},
    {"DPM", ""},
    {"OD", ""},
    {"ANP", ""},
    {"MSW", "MASTER OF SOCIAL WORK"},
    {"LCSW", "LICENSED CLINICAL SOCIAL WORKER"},
    {"RPH", "REGISTERED PHARMACIST"},
    {"MSPT", "MASTER OF SCIENCE IN PHYSICAL THERAPY"},
    {"DO", ""},
    {"DDS", ""},
    {"MS", ""},
    {"FNP", "FAMILY NURSE PRACTIONER"},
    {"ACSW", "ACADEMY OF CERTIFIED SOCIAL WORKERS"},
    {"PA-C", "PHYSICIAN ASSISTANT CERTIFIED"},
    {"AA-C", "CERTIFIED ANESTHESIOLOGIST ASSISTANT"},
    {"RPH", "REGISTERED PHARMACIST"}
};

std::unordered_map<std::string, std::string> title_map =
{
    {"DR", ""},
    {"MR", ""},
    {"MRS", ""},
    {"MS", ""}
};

std::unordered_map<std::string, std::vector<std::string>> nicknames_map;

/* Generates an unordered_map with the nicknames as the key
 * and a vector of 'normal' names that can be associated with
 * the nickname.
*/
void
read_nicknames(const char *file_name)
{
    std::ifstream file(file_name);

    std::string line;
    while(std::getline(file, line))
    {
        //Make it uppercase
        boost::to_upper(line);

        std::vector<std::string> chunks;
        split(line, ',', chunks);

        for(uint i = 1; i < chunks.size(); i++)
        {
            //Look for the nickname in nicknames_map
            auto search = nicknames_map.find(chunks.at(i));
            if(search != nicknames_map.end())
            {
                search->second.push_back(chunks.at(0));
                //std::cout << "pushed: " << search->first + " " + chunks.at(0);
            }
            else
            {
                nicknames_map.insert({trim(chunks.at(i)), {trim(chunks.at(0))}});
                //std::cout << "inserted: " << trim(chunks.at(i)) + " " + trim(chunks.at(0));
            }
        }
    }

    file.close();
}

void
Name::get_specs(std::string& name)
{
    //Split name by ',' to separate the end
    std::vector<std::string> items;
    split(name, ',', items);

    //TODO: write it with a reverser iterator
    for(int i = items.size()-1; i >= 0; i--)
    {
        //Looking for the known specs int the specs_map
        auto search = specs_map.find(trim(items.at(i)));
        if(search != specs_map.end())
        {
            this->specs.push_back(search->first);
            std::cout << "specs found: " << search->first << std::endl;
        }
        else
        {
            //this->specs.push_back("UNKNOWN");
            std::cout << "specs NOT FOUND: " << items.at(i) << std::endl;

            //To remove the found specs from the end of the name
            name = join(items, ' ', 0, i);
            std::cout << "new name: " << name << std::endl;
            break;
        }
    }
}

void
Name::get_title(std::string& name)
{
    std::vector<std::string> chunks;
    split(name, ' ', chunks);

    //I think it's enough if we just check the first chunk
    auto search = title_map.find(trim(chunks.front()));
    if(search != title_map.end())
    {
        this->title = search->first;
        std::cout << "title found: " << search->first << std::endl;
    }
    else
        std::cout << "title NOT FOUND" << std::endl;

    name = join(chunks, ' ', 1, chunks.size()-1);
    std::cout << "new name: " << name << std::endl;
}

void
Name::get_nickname(std::string& name)
{
    //TODO: There're names that can be a name and a nickname as well like 'ellen'
    std::vector<std::string> chunks;
    split(name, ' ', chunks);
    for(auto str: chunks)
    {
        auto search = nicknames_map.find(trim(str));
        if(search != nicknames_map.end())
        {
            std::cout << "nickname found: " << str << std::endl;
            getchar();
        }
    }
}

Name::Name(std::string name)
{
    std::cout << name << std::endl;

    //Remove points from the name
    char_remove(name, std::string("."));

    //To separate the specs
    this->get_specs(name);

    //To separate the title (mr, mrs, dr, ms..)
    this->get_title(name);

    this->get_nickname(name);
}

Address::Address(std::string addr)
{
    //TODO
    std::cout << addr << std::endl;
}

Taxonomies::Taxonomies(std::string tax)
{
    //TODO
    std::cout << tax << std::endl;
}
