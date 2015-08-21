#ifndef TAX_HPP
#define TAX_HPP

#include <string>

const int TAX_BITS = 2;

class Taxonomies
{
public:
    /*write members here*/
    //should have an array of taxonomies
    std::string msTaxonomy;

    Taxonomies(const std::string& tax);
};

double TaxonomyBitMapMaker(const Taxonomies&, const Taxonomies&);

#endif
