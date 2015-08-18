#include <string>
#include <iostream>

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

public:

	CAddress(std::string sAddressString);

	double IsTheSame(CAddress qOtherAddress);
};