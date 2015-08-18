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
	miHouseNumber = miApartmentNumber = miZipCode = 0;
	char cParsingCharacter;
	int iIterator = 1;
	cParsingCharacter = sAddressString[iIterator];
	while (!isspace(cParsingCharacter)){ //Getting the House Number
		miHouseNumber = miHouseNumber * 10 + (cParsingCharacter - '0');
		iIterator++;
		cParsingCharacter = sAddressString[iIterator];
	}
	iIterator++;
	cParsingCharacter = sAddressString[iIterator];
	while (!isspace(cParsingCharacter)){ //Getting the Street
		msStreet += cParsingCharacter;
		iIterator++;
		cParsingCharacter = sAddressString[iIterator];
	}
	iIterator++;
	cParsingCharacter = sAddressString[iIterator];
	while (cParsingCharacter != ','){ // Getting the Street Identifier (Road, Boulevard etc.)
		msStreetIdentifier += cParsingCharacter;
		iIterator++;
		cParsingCharacter = sAddressString[iIterator];
	}
	ConvertStreetIdentifier(&msStreetIdentifier);
	iIterator += 2;
	cParsingCharacter = sAddressString[iIterator];
	if (cParsingCharacter != '#' && !IsANumber(cParsingCharacter)){// Getting City or Apartment Number and City
		while (cParsingCharacter != ','){
			msCity += cParsingCharacter;
			iIterator++;
			cParsingCharacter = sAddressString[iIterator];
		}
	}
	else{
		while (cParsingCharacter != ','){
			if (cParsingCharacter == '#'){
				iIterator++;
				cParsingCharacter = sAddressString[iIterator];
			}
			miApartmentNumber = miApartmentNumber * 10 + (cParsingCharacter - '0');
			iIterator++;
			cParsingCharacter = sAddressString[iIterator];
		}
		iIterator += 2;
		cParsingCharacter = sAddressString[iIterator];
		while (cParsingCharacter != ','){
			msCity += cParsingCharacter;
			iIterator++;
			cParsingCharacter = sAddressString[iIterator];
		}
	}
	iIterator += 2;
	cParsingCharacter = sAddressString[iIterator];
	while (!isspace(cParsingCharacter)){ //Getting the State
		msState += cParsingCharacter;
		iIterator++;
		cParsingCharacter = sAddressString[iIterator];
	}
	// ConvertStateName(msState);
	iIterator++;
	cParsingCharacter = sAddressString[iIterator];
	while (cParsingCharacter != ','){ //Getting and converting the Zip Code
		if (cParsingCharacter == '-'){
			iIterator++;
			cParsingCharacter = sAddressString[iIterator];
		}
		miZipCode = miZipCode * 10 + (cParsingCharacter - '0');
		iIterator++;
		cParsingCharacter = sAddressString[iIterator];
	}
	iIterator += 2;
	cParsingCharacter = sAddressString[iIterator];
	while (cParsingCharacter != '"'){ //Getting the Country
		msCountry += cParsingCharacter;
		iIterator++;
		cParsingCharacter = sAddressString[iIterator];
	}
	std::cout << miHouseNumber << std::endl << msStreet << std::endl << msStreetIdentifier << std::endl;
	std::cout << miApartmentNumber << std::endl << msCity << std::endl << msState << std::endl << miZipCode << std::endl << msCountry << std::endl;
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