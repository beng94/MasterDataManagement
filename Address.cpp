#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "data.hpp"
#include "Address.h"

void ConvertStreetIdentifier(std::string *spStreetIdentifier){
	if (*spStreetIdentifier == "RD")
		*spStreetIdentifier = "Road";
	if (*spStreetIdentifier == "BLVD" || *spStreetIdentifier == "BLV")
		*spStreetIdentifier = "Boulevard";
}

bool IsANumber(char cCharacter){
	if (cCharacter >= '0' && cCharacter <= '9')
		return true;
	return false;
}

void ConvertStateName(std::string *spStateName){

}


CAddress::CAddress(std::string sAddressString){
	std::vector<std::string> saCommaSeparatedFields;
	split(sAddressString, ',', saCommaSeparatedFields);
	int iFirstFieldsSize = saCommaSeparatedFields.size();
	if (iFirstFieldsSize > 4){
		for (int i = 0; i < iFirstFieldsSize; i++)
			std::cout << saCommaSeparatedFields[i] << std::endl;
	}
	std::vector<std::string> saHouseNumberToStreetIdentifier;
	boost::trim(saCommaSeparatedFields[0]);
	split(saCommaSeparatedFields[0], ' ', saHouseNumberToStreetIdentifier);
	if (saHouseNumberToStreetIdentifier[0] == "PO"){
		mbIsAPOBox = true;
		miHouseNumber = boost::lexical_cast<int>(saHouseNumberToStreetIdentifier.back());
	}
	else{
		mbIsAPOBox = false;
		miHouseNumber = boost::lexical_cast<int>(saHouseNumberToStreetIdentifier.front());
		for (int i = 1; i < saHouseNumberToStreetIdentifier.size(); i++)
			msStreet += saHouseNumberToStreetIdentifier[i];
	}
	msCountry = trim(saCommaSeparatedFields[iFirstFieldsSize-1]);
	std::vector<std::string> saStateAndZipCode;
	boost::trim(saCommaSeparatedFields[iFirstFieldsSize - 2]);
	split(saCommaSeparatedFields[iFirstFieldsSize-2], ' ', saStateAndZipCode);
	msState = trim(saStateAndZipCode[0]);
	std::vector<std::string> saZipCode;
	boost::trim(saStateAndZipCode[1]);
	split(saStateAndZipCode[1], '-', saZipCode);
	if (saZipCode.size() > 1)
		miZipCode = boost::lexical_cast<int>(saZipCode[0]) * 10000 + boost::lexical_cast<int>(saZipCode[1]);
	else
		miZipCode = boost::lexical_cast<int>(saZipCode[0]);
	msCity = trim(saCommaSeparatedFields[iFirstFieldsSize - 3]);
	if (iFirstFieldsSize > 4){
		for (int i = 1; i < iFirstFieldsSize - 2; i++){
			msOtherStuff += saCommaSeparatedFields[i];
		}
	}
	std::cout << miHouseNumber << std::endl << mbIsAPOBox << std::endl << msStreet << std::endl << msStreetIdentifier << std::endl;
	std::cout << miApartmentNumber << std::endl << msCity << std::endl << msState << std::endl << miZipCode << std::endl << msCountry << std::endl;
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
