#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "entity.hpp"
#include "Address.h"
#include <algorithm>
#include "string_handle.hpp"

bool IsANumber(char cCharacter){
	return cCharacter >= '0' && cCharacter <= '9';
}

double ZipCodeCheck(const std::string& sFirstZip, const std::string& sSecondZip){
	if (sFirstZip == sSecondZip)
		return 1.0;
	if (sFirstZip.length() > sSecondZip.length())
		return StringCheck(sFirstZip.substr(0, 5), sSecondZip);
	if (sFirstZip.length() < sSecondZip.length())
		return StringCheck(sFirstZip, sSecondZip.substr(0, 5));
	return StringCheck(sFirstZip, sSecondZip);
}

CAddress::CAddress(std::string& sAddressString){
	sAddressString = trim(sAddressString);
	std::vector<std::string> saFields;
	split(sAddressString, ',', saFields);
	int iFirstFieldsSize = saFields.size();
	///< Separates based on commas, checks if the address is irregular

	std::vector<std::string> saStreetName;
	boost::trim(saFields[0]);
	split(saFields[0], ' ', saStreetName);
	if (saStreetName[0] == "PO"){
		mbIsAPOBox = true;
		msHouseNumber = saStreetName.back();
		// PO Box field is separated
		std::vector<std::string> saSecondaryStreetName;
		boost::trim(saFields[1]);
		split(saFields[1], ' ', saSecondaryStreetName);
		msStreet = join(saSecondaryStreetName, ' ', 0, saSecondaryStreetName.size() - 1);
	}
	else{
		mbIsAPOBox = false;
		msHouseNumber = saStreetName.front();
		msStreet = join(saStreetName, ' ', 0, saStreetName.size() - 1);
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
	if (saZipCode.size() > 1){
		msZipCode = saZipCode[0] + saZipCode[1];
	}
	else{
		msZipCode = saZipCode[0];
	}
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
	char_remove(msCity, ".,");
	char_remove(msStreet, ".,");
	msCityHash = str_hash(msCity);
	msStreetHash = str_hash(msStreet);
	msOtherStuffHash = str_hash(msOtherStuff);

	/// Debug
	//std::cout << msHouseNumber << std::endl << mbIsAPOBox << std::endl << msStreet << std::endl;
	//std::cout << msCity << std::endl << msState << std::endl << msZipCode << std::endl << msCountry << std::endl;
	//std::cout << "Other things:" << std::endl << msOtherStuff << std::endl;

}

/*int AddressBitMapMaker(const CAddress& qFirstAddress, const CAddress& qSecondAddress){
	double fStreetMatch = StringCheck(qFirstAddress.msStreet, qSecondAddress.msStreet);
	int iReturnValue = 0;
	if (ZipCodeCheck(qFirstAddress.msZipCode, qSecondAddress.msZipCode) > 0.8)
		iReturnValue += 1;
	if (qFirstAddress.msCityHash == qSecondAddress.msCityHash)
		iReturnValue += 2;
	if (fStreetMatch < 0.25)
		iReturnValue += 0;
	else if (fStreetMatch >= 0.25 && fStreetMatch < 0.5)
		iReturnValue += 4;
	else if (fStreetMatch >= 0.5 && fStreetMatch < 0.75)
		iReturnValue += 8;
	else
		iReturnValue += 12;
	if (StringCheck(qFirstAddress.msOtherStuff, qSecondAddress.msOtherStuff) > 0.75)
		iReturnValue += 16;
	if (StringCheck(qFirstAddress.msHouseNumber, qSecondAddress.msHouseNumber) > 0.9)
		iReturnValue += 32;
	return iReturnValue;
}*/

int AddressBitMapMaker(const CAddress& qFirstAddress, const CAddress& qSecondAddress){
	int iReturnValue = 50;
	double fStreetMatch = StringCheck(qFirstAddress.msStreet, qSecondAddress.msStreet);
	if (ZipCodeCheck(qFirstAddress.msZipCode, qSecondAddress.msZipCode) > 0.8)
		iReturnValue += 10;
	if (qFirstAddress.msCityHash == qSecondAddress.msCityHash)
		iReturnValue += 20;
	if (fStreetMatch < 0.25)
		iReturnValue -= 20;
	else if (fStreetMatch >= 0.25 && fStreetMatch < 0.5)
		iReturnValue -= 10;
	else if (fStreetMatch >= 0.5 && fStreetMatch < 0.75)
		iReturnValue += 10;
	else
		iReturnValue += 20;
	if (StringCheck(qFirstAddress.msOtherStuff, qSecondAddress.msOtherStuff) > 0.75)
		iReturnValue += 10;
	if (StringCheck(qFirstAddress.msHouseNumber, qSecondAddress.msHouseNumber) > 0.9)
		iReturnValue += 10;
	if (iReturnValue > 100)
		return 100;
	if (iReturnValue < 0)
		return 0;
	return iReturnValue;
}
