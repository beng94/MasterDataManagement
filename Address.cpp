#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "data.hpp"
#include "Address.h"

bool IsANumber(char cCharacter){
	if (cCharacter >= '0' && cCharacter <= '9')
		return true;
	return false;
}

void ConvertStateName(std::string *spStateName){

}


CAddress::CAddress(std::string sAddressString){

	std::vector<std::string> saFields;
	split(sAddressString, ',', saFields);
	int iFirstFieldsSize = saFields.size();
	if (iFirstFieldsSize > 4){
		for (int i = 0; i < iFirstFieldsSize; i++)
			std::cout << saFields[i] << std::endl;
	}
	///< Separates based on commas, checks if the address is irregular

	std::vector<std::string> saStreetName;
	boost::trim(saFields[0]);
	split(saFields[0], ' ', saStreetName);
	if (saStreetName[0] == "PO"){
		mbIsAPOBox = true;
		miHouseNumber = boost::lexical_cast<int>(saStreetName.back());
		std::vector<std::string> saSecondaryStreetName;
		boost::trim(saFields[1]);
		split(saFields[0], ' ', saSecondaryStreetName);
		for (int i = 0; i < saSecondaryStreetName.size(); i++)
			msStreet += saSecondaryStreetName[i];
	}
	else{
		mbIsAPOBox = false;
		miHouseNumber = boost::lexical_cast<int>(saStreetName.front());
		for (int i = 1; i < saStreetName.size(); i++)
			msStreet += saStreetName[i];
	}
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
	if (saZipCode.size() > 1)
		miZipCode = boost::lexical_cast<int>(saZipCode[0]) * 10000 + boost::lexical_cast<int>(saZipCode[1]);
	else
		miZipCode = boost::lexical_cast<int>(saZipCode[0]);
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
	msCityHash = str_hash(msCity);
	msStreetHash = str_hash(msStreet);
	msOtherStuffHash = str_hash(msOtherStuff);

	/// Debug
	std::cout << miHouseNumber << std::endl << mbIsAPOBox << std::endl << msStreet << std::endl;
	std::cout << msCity << std::endl << msState << std::endl << miZipCode << std::endl << msCountry << std::endl;
	std::cout << "Other things:" << std::endl << msOtherStuff << std::endl;

}

double CAddress::IsTheSame(CAddress qOtherAddress){
	double fProbability = 0.5;
	if (msState != qOtherAddress.msState)
		fProbability -= 0.25;
	else
		fProbability += 0.25;
	if (msCity != qOtherAddress.msCity)
		fProbability -= 0.2;
	else
		fProbability += 0.2;
	if (msStreet != qOtherAddress.msStreet)
		fProbability -= 0.1;
	else
		fProbability += 0.1;
	if (fProbability < 0)
		return 0;
	if (fProbability > 1)
		return 1;
	return fProbability;
}