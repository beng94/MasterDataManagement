#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "name.hpp"
#include "Address.h"
#include "tax.hpp"

class Entity
{
public:
    int id;
    Name name;
    CAddress address;
    Taxonomies taxonomies;

    Entity(int id, std::string name, std::string addr, std::string tax) :
           id{id}, name{name}, address{addr}, taxonomies{tax}
    {}
};

int entities_cmp(Entity&, Entity&);

#endif
