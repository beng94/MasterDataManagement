#ifndef NAME_HPP
#define NAME_HPP

#include <string>
#include <vector>

void read_nicknames(const char* file);

class Name
{
public:
    /*write members here*/
    std::string name;
    std::vector<std::string> title;
    std::vector<std::string> specs;

    Name(std::string name);

    int NameBitMapMaker(const Name& name_a);

private:
    void get_specs(std::string& name);
    void get_title(std::string& name);
    void get_nickname(std::string& name);
    int name_cmp(const Name& name);
    int title_cmp(const Name& name);
    int specs_cmp(const Name& name);
};

#endif
