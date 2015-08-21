#include "entity.hpp"

int Entity::BitMapMake(const Entity& rhs_entity)
{
    int name_cmp = this->name.NameBitMapMaker(rhs_entity.name);
    int addr_cmp = AddressBitMapMaker(this->address, rhs_entity.address);
    int tax_cmp = 0;

    int result = name_cmp + (addr_cmp << NAME_BITS) + (tax_cmp << (NAME_BITS + ADDR_BITS));
    return result;
}
