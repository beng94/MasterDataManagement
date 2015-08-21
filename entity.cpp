#include "entity.hpp"

double Entity::BitMapMake(const Entity& rhs_entity)
{
    double name_cmp = this->name.NameBitMapMaker(rhs_entity.name) / 100.0;
    double addr_cmp = AddressBitMapMaker(this->address, rhs_entity.address) / 100.0;
    double tax_cmp = TaxonomyBitMapMaker(this->taxonomies, rhs_entity.taxonomies);

    return name_cmp * 0.4 + addr_cmp * 0.4 + tax_cmp * 0.2;
}
