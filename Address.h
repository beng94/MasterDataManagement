#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>

void ConvertStreetIdentifier(std::string *spStreetIdentifier);
bool IsANumber(char cCharacter);
void ConvertStateName(std::string *spStateName);

class CAddress{
	int miHouseNumber;
	int miApartmentNumber;
	int miZipCode;
    bool mbIsAPOBox;
	std::string msStreet;
	std::string msStreetIdentifier;
	std::string msCity;
	std::string msState;
	std::string msCountry;
    std::string msOtherStuff;

public:

	CAddress(std::string sAddressString);

	double IsTheSame(CAddress qOtherAddress);
};

#endif
