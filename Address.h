#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

bool IsANumber(char cCharacter);
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
