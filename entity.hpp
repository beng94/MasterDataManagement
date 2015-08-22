#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "name.hpp"
#include "Address.h"
#include "tax.hpp"

const int BITMAP_SIZE = NAME_BITS + ADDR_BITS + TAX_BITS;

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

    int BitMapMake(const Entity& rhs_entity);
    double ProbabilityCalculate(const Entity& rhs_entity);
};

#endif
