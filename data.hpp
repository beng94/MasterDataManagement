#include <string>
#include <vector>

//TODO: write a program to get the data out from the ground_truth file

std::string trim(char *);
std::string trim(std::string str);
std::string join(std::vector<std::string>&, char, int , int);
void char_remove(std::string&, std::string);
std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);

class Name
{
public:
    /*write members here*/
    std::string title;
    std::vector<std::string> specs;

    Name(std::string name);

private:
    void get_specs(std::string& name);
    void get_title(std::string& name);
};

class Address
{
public:
    /*write members here*/
    //country
    //state
    //zip code

    Address(std::string addr);
private:
    /* TODO:
     * - convert zip code
     */
};

class Taxonomies
{
public:
    /*write members here*/
    //should have an array of taxonomies

    Taxonomies(std::string tax);
};

class Entity
{
public:
    int id;
    Name name;
    Address address;
    Taxonomies taxonomies;

    Entity(int id, Name name, Address addr, Taxonomies tax) :
           id{id}, name{name}, address{addr}, taxonomies{tax}
    {}
};
