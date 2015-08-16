#include <string>
#include <vector>

//TODO: write a program to get the data out from the ground_truth file

std::string trim(char *);
void char_remove(std::string&, std::string);
std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);

class Name
{
public:
    /*write members here*/
    //title: DR, MD, INC, DDS, MS, DPM, OD, etc
    //name: store it in an array

    Name(std::string name);
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
