#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>

bool IsANumber(char cCharacter);
double StringCheck(const std::string& sFirstString, const std::string& sSecondString);
double WordCheck(const std::string& sFirstWord, const std::string& sSecondWord);
double ZipCodeCheck(const std::string& sFirstZip, const std::string& sSecondZip);

class CAddress{
public:
	std::string msHouseNumber;
	std::string msZipCode;

	bool mbIsAPOBox;

	std::string msStreet;
	std::string msCity;
	std::string msState;
	std::string msCountry;
	std::string msOtherStuff;

	std::string msStreetHash;
	std::string msCityHash;
	std::string msOtherStuffHash;


	CAddress(std::string sAddressString);
};

int AddressBitMapMaker(const CAddress& qFirstAddress, const CAddress& qSecondAddress);

#endif