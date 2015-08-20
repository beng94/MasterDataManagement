#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "name.hpp"
#include "Address.h"

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
    CAddress address;
    Taxonomies taxonomies;

    Entity(int id, Name name, CAddress addr, Taxonomies tax) :
           id{id}, name{name}, address{addr}, taxonomies{tax}
    {}
};

#endif
