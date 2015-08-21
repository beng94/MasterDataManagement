#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <vector>

#include "Address.h"
#include "Taxonomy.h"

//TODO: write a program to get the data out from the ground_truth file

std::string trim(std::string str);
std::string join(std::vector<std::string>&, char, int , int);
void char_remove(std::string&, std::string);
std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
std::string str_hash(std::string& str);
std::string StringWordRemove(std::string sString);

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

class Taxonomies{

public:

	//std::vector<std::string> msaTaxonomies;
	std::string msTaxonomy;

	Taxonomies(std::string sTaxonomyString);
};

int TaxonomyBitMapMaker(const Taxonomies& qFirstTaxonomy, const Taxonomies& qSecondTaxonomy);

class Entity
{
public:
    int id;
    Name name;
    CAddress address;
    Taxonomies taxonomies;

    Entity(int id, Name name, CAddress addr, Taxonomies tax) :
           id{id}, name{name}, address{addr}, taxonomies{tax}
    {}
};
#endif