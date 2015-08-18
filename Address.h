#ifndef ADDRESS_H
#define ADDRESS_H

#include "stdafx.h"
#include <string>
#include <iostream>
#include "data.hpp"

void ConvertStreetIdentifier(std::string *spStreetIdentifier);
bool IsANumber(char cCharacter);
void ConvertStateName(std::string *spStateName);

class CAddress{
	int miHouseNumber;
	int miApartmentNumber;
	int miZipCode;
	std::string msStreet;
	std::string msStreetIdentifier;
	std::string msCity;
	std::string msState;
	std::string msCountry;
	std::string msOtherStuff;
	bool mbIsAPOBox;

public:

	CAddress(std::string sAddressString);

	double IsTheSame(CAddress qOtherAddress);
};

#endif