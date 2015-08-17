#include <iostream>
#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <unordered_map>

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

    //Split name by ',' to separate the end
    std::vector<std::string> items;
    split(name, ',', items);

    std::cout << name << std::endl;
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
