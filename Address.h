#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>

bool IsANumber(char cCharacter);
void ConvertStateName(std::string *spStateName);

class CAddress{
	int miHouseNumber;
	int miZipCode;
	std::string msStreet;
	std::string msCity;
	std::string msState;
	std::string msCountry;
	std::string msOtherStuff;
	std::string msStreetHash;
	std::string msCityHash;
	std::string msOtherStuffHash;
	bool mbIsAPOBox;

public:

	CAddress(std::string sAddressString);

	double IsTheSame(CAddress qOtherAddress);
};

#endif