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

double TaxonomyProbabilityCalcuate(const Taxonomies& qFirstTaxonomy, const Taxonomies& qSecondTaxonomy){
	return StringCheck(qFirstTaxonomy.msTaxonomy, qSecondTaxonomy.msTaxonomy);
}

int TaxonomyBitMapMaker(const Taxonomies& qFirstTaxonomy, const Taxonomies& qSecondTaxonomy){
	std::vector<std::string> saFirstTax, saSecondTax;
	split(qFirstTaxonomy.msTaxonomy, ' ', saFirstTax);
	split(qSecondTaxonomy.msTaxonomy, ' ', saSecondTax);
	double fWordMatch = StringExactMatch(saFirstTax, saSecondTax) / (double) qFirstTaxonomy.msTaxonomy.size();
	if (fWordMatch < 0.25)
		return 0;
	else if (fWordMatch < 0.5)
		return 1;
	else if (fWordMatch < 0.75)
		return 2;
	else
		return 3;
}

