#include "entity.hpp"

Taxonomies::Taxonomies(std::string sTaxonomyString){
	std::vector<std::string> saSpaceSplit, saAmpersandSplit, saSlashSplit, saCommaSplit;
	split(sTaxonomyString, ' ', saSpaceSplit);
	for (int i = 0; i < saSpaceSplit.size(); i++)
		split(saSpaceSplit[i], '&', saAmpersandSplit);
	for (int i = 0; i < saAmpersandSplit.size(); i++)
		split(saAmpersandSplit[i], '/', saSlashSplit);
	for (int i = 0; i < saSlashSplit.size(); i++)
		split(saSlashSplit[i], ',', saCommaSplit);
	msTaxonomy = join(saCommaSplit, ' ', 0, saCommaSplit.size() - 1);
	char_remove(msTaxonomy, ".'");
	msTaxonomy = StringWordRemove(msTaxonomy);
	std::cout << msTaxonomy << std::endl;
}

int TaxonomyBitMapMaker(const Taxonomies& qFirstTaxonomy, const Taxonomies& qSecondTaxonomy){
	if (StringCheck(qFirstTaxonomy.msTaxonomy, qSecondTaxonomy.msTaxonomy) < 0.25)
		return 0;
	else if (StringCheck(qFirstTaxonomy.msTaxonomy, qSecondTaxonomy.msTaxonomy) < 0.5)
		return 1;
	else if (StringCheck(qFirstTaxonomy.msTaxonomy, qSecondTaxonomy.msTaxonomy) < 0.75)
		return 2;
	else
		return 3;
}

std::string StringWordRemove(std::string sString){
	std::vector<std::string> saSpaceSplit, saResultString;
	bool bFlag;
	split(sString, ' ', saSpaceSplit);
	for (int i = 0; i < saSpaceSplit.size() - 1; i++){
		bFlag = true;
		for (int j = i + 1; j < saSpaceSplit.size(); j++){
			if (str_hash(saSpaceSplit[i]) == str_hash(saSpaceSplit[j]))
				bFlag = false;
		}
		if (bFlag)
			saResultString.push_back(saSpaceSplit[i]);
	}
	saResultString.push_back(saSpaceSplit[saSpaceSplit.size()-1]);
	return join(saResultString, ' ', 0, saResultString.size() - 1);
}