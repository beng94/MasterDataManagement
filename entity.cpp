#include "entity.hpp"

double Entity::ProbabilityCalculate(const Entity& rhs_entity)
{
		double fname_cmp = this->name.ProbabilityCalculate(rhs_entity.name) / 100.0;
		double faddr_cmp = AddressProbabilityCalculate(this->address, rhs_entity.address) / 100.0;
		double ftax_cmp = TaxonomyProbabilityCalculate(this->taxonomies, rhs_entity.taxonomies);

		return fname_cmp * 0.4 + faddr_cmp * 0.4 + ftax_cmp * 0.2;
}

int Entity::BitMapMake(const Entity& rhs_entity)
{
	int name_cmp = this->name.NameBitMapMaker(rhs_entity.name);
	int addr_cmp = AddressBitMapMaker(this->address, rhs_entity.address);
	int tax_cmp = TaxonomyBitMapMaker(this->taxonomies, rhs_entity.taxonomies);

	return name_cmp + (addr_cmp << NAME_BITS) + (tax_cmp << (NAME_BITS + ADDR_BITS));
}