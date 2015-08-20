#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "entity.hpp"
#include "Address.h"
#include <algorithm>

bool IsANumber(char cCharacter){
	return cCharacter >= '0' && cCharacter <= '9';
}

double WordCheck(const std::string& sFirstWord, const std::string& sSecondWord){
	int iMinSize = std::min(sFirstWord.length(), sSecondWord.length());
	int iMaxSize = std::max(sFirstWord.length(), sSecondWord.length());
	double fReturnValue = 0;
	for (int i = 0; i < iMinSize; i++)
		if (sFirstWord[i] == sSecondWord[i])
			fReturnValue++;
	return fReturnValue / iMaxSize;
}


double StringCheck(const std::string& sFirstString, const std::string& sSecondString){
	std::vector<std::string> saFirstString, saSecondString;
	split(sFirstString, ' ', saFirstString);
	split(sSecondString, ' ', saSecondString);
	std::vector<double> faSimilarities;

	for (auto str_a : saFirstString){
		double fMaxSimilarity = 0.0;
		for (auto str_b : saSecondString){
			double fCompare = WordCheck(str_a, str_b);
			if (fCompare > fMaxSimilarity)
				fMaxSimilarity = fCompare;
		}
		faSimilarities.push_back(fMaxSimilarity);
	}

	double fProbabilitySum = 0.0;
	for (int i = 0; i < saFirstString.size(); i++)
		fProbabilitySum += faSimilarities.at(i) * saFirstString.at(i).length();
	return fProbabilitySum / (sFirstString.length() - saFirstString.size() + 1);
}

CAddress::CAddress(std::string sAddressString){
	miHouseNumber = 0;
	miZipCode = 0;
	std::vector<std::string> saFields;
	split(sAddressString, ',', saFields);
	int iFirstFieldsSize = saFields.size();
	///< Separates based on commas, checks if the address is irregular

	std::vector<std::string> saStreetName;
	boost::trim(saFields[0]);
	split(saFields[0], ' ', saStreetName);
	if (saStreetName[0] == "PO"){
		mbIsAPOBox = true;
		if (IsANumber(saStreetName.back()[0]) && IsANumber(saStreetName.back()[saStreetName.back().length()]))
			miHouseNumber = boost::lexical_cast<int>(saStreetName.back());
		else
			msOtherStuff += saStreetName.back();
		// PO Box field is separated
		std::vector<std::string> saSecondaryStreetName;
		boost::trim(saFields[1]);
		split(saFields[1], ' ', saSecondaryStreetName);
		for (int i = 0; i < saSecondaryStreetName.size(); i++)
			msStreet += saSecondaryStreetName[i] + ' ';
	}
	else{
		mbIsAPOBox = false;
		if (IsANumber(saStreetName.front()[0]) && IsANumber(saStreetName.front()[saStreetName.front().length()]))
			miHouseNumber = boost::lexical_cast<int>(saStreetName.front());
		else
			msOtherStuff += saStreetName.front();
		for (int i = 1; i < saStreetName.size(); i++)
			msStreet += saStreetName[i] + ' ';
	}
	boost::trim(msStreet);
	///< Takes the first field and parses it accordingly

	msCountry = trim(saFields[iFirstFieldsSize - 1]);
	std::vector<std::string> saStateAndZipCode;
	boost::trim(saFields[iFirstFieldsSize - 2]);
	split(saFields[iFirstFieldsSize - 2], ' ', saStateAndZipCode);
	msState = trim(saStateAndZipCode[0]);
	///< Parses the country and the State, prepares for parsing the zip code

	std::vector<std::string> saZipCode;
	boost::trim(saStateAndZipCode[1]);
	split(saStateAndZipCode[1], '-', saZipCode);
	if (saZipCode.size() > 1){
		if (IsANumber(saZipCode[0][0]) && IsANumber(saZipCode[1][0]))
			miZipCode = boost::lexical_cast<int>(saZipCode[0]) * 10000 + boost::lexical_cast<int>(saZipCode[1]);
		else{
			msOtherStuff += saZipCode[0];
			msOtherStuff += saZipCode[1];
		}
	}
	else{
		if (IsANumber(saZipCode[0][0]))
			miZipCode = boost::lexical_cast<int>(saZipCode[0]);
		else
			msOtherStuff += saZipCode[0];
	}
	///< Parses the zip code based on 5 and 9 digit variations

	/// Parses the City
	msCity = trim(saFields[iFirstFieldsSize - 3]);
	if (!mbIsAPOBox){
		if (iFirstFieldsSize > 4){
			for (int i = 1; i < iFirstFieldsSize - 3; i++){
				msOtherStuff += saFields[i];
			}
		}
	}
	else if (iFirstFieldsSize > 5){
		for (int i = 2; i < iFirstFieldsSize - 3; i++){
			msOtherStuff += saFields[i];
		}
	}
	///< Parses any and all remaining non-standard fields

	/// Creates the hashes
	char_remove(msCity, ".,");
	char_remove(msStreet, ".,");
	msCityHash = str_hash(msCity);
	msStreetHash = str_hash(msStreet);
	msOtherStuffHash = str_hash(msOtherStuff);

	/// Debug
	std::cout << miHouseNumber << std::endl << mbIsAPOBox << std::endl << msStreet << std::endl;
	std::cout << msCity << std::endl << msState << std::endl << miZipCode << std::endl << msCountry << std::endl;
	std::cout << "Other things:" << std::endl << msOtherStuff << std::endl;

}

int AddressBitMapMaker(const CAddress& qFirstAddress, const CAddress& qSecondAddress){
	double fStreetMatch = StringCheck(qFirstAddress.msStreet, qSecondAddress.msStreet);
	int iReturnValue = 0;
	if (qFirstAddress.miZipCode == qSecondAddress.miZipCode)
		iReturnValue += 1;
	if (qFirstAddress.msCityHash == qSecondAddress.msCityHash)
		iReturnValue += 2;
	if (fStreetMatch < 0.25)
		iReturnValue += 0;
	else if (fStreetMatch >= 0.25 && fStreetMatch < 0.5)
		iReturnValue += 4;
	else if (fStreetMatch >= 0.5 && fStreetMatch < 0.75)
		iReturnValue += 8;
	else
		iReturnValue += 12;
	if (StringCheck(qFirstAddress.msOtherStuff, qSecondAddress.msOtherStuff) > 0.75)
		iReturnValue += 16;
	if (qFirstAddress.miHouseNumber == qSecondAddress.miHouseNumber)
		iReturnValue += 32;
	return iReturnValue;
}