#include <iostream>
#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "data.hpp"

std::string
trim(char *s)
{
    std::string str(s);
    boost::trim(str);

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

Name::Name(std::string name)
{
    //Remove points from the name
    char_remove(name, std::string("."));

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
