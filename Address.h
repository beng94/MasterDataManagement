#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>


class CAddress{
public:
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


	CAddress(std::string sAddressString);
};

int AddressBitMapMaker(const CAddress& qFirstAddress, const CAddress& qSecondAddress);

#endif