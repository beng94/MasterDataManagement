#ifndef NAME_HPP
#define NAME_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include "string_handle.hpp"

void read_nicknames(const char* file);

class Name
{
public:
    /*write members here*/
    std::string name;
    std::vector<std::string> title;
    std::vector<std::string> specs;

    Name(std::string name);

private:
    void get_specs(std::string& name);
    void get_title(std::string& name);
    void get_nickname(std::string& name);
};

#endif
