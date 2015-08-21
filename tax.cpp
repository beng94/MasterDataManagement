#include "tax.hpp"
#include "entity.hpp"
#include "string_handle.hpp"

Taxonomies::Taxonomies(const std::string& sTaxonomyString){
	std::vector<std::string> saSpaceSplit, saAmpersandSplit, saSlashSplit, saCommaSplit;
	split(sTaxonomyString, ' ', saSpaceSplit);
	for (uint i = 0; i < saSpaceSplit.size(); i++)
		split(saSpaceSplit[i], '&', saAmpersandSplit);
	for (uint i = 0; i < saAmpersandSplit.size(); i++)
		split(saAmpersandSplit[i], '/', saSlashSplit);
	for (uint i = 0; i < saSlashSplit.size(); i++)
		split(saSlashSplit[i], ',', saCommaSplit);
	msTaxonomy = join(saCommaSplit, ' ', 0, saCommaSplit.size() - 1);
	char_remove(msTaxonomy, ".'");
	msTaxonomy = StringWordRemove(msTaxonomy);
	//std::cout << msTaxonomy << std::endl;
}

double TaxonomyBitMapMaker(const Taxonomies& qFirstTaxonomy, const Taxonomies& qSecondTaxonomy){
	return fStringSim = StringCheck(qFirstTaxonomy.msTaxonomy, qSecondTaxonomy.msTaxonomy);
}

