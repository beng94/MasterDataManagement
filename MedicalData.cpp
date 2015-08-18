// MedicalData.cpp : Defines the entry point for the console application.
//

#include "Address.h"


int main()
{
	std::string Balfasz = "1990 INDUSTRIAL BLVD, HOUMA, LA 70363, US";
	std::string MasikBalfasz = "30400 TELEGRAPH RD, #379, BINGHAM FARMS, MI 59857, US";
	std::string HarmadikBalfasz = "PO BOX 19450, 7 DEZ JUNCOS STAITON, SAN JUAN, PR 00910, US";
	std::string NegyedikBalfasz = "800 IIVRNG AVE, PSYCHIATRY SERIVCE 116A, VAMC, SYRACUSE, NY 13210-2716, US";
	CAddress Valami(Balfasz);
	CAddress MasikValami(MasikBalfasz);
	CAddress HarmadikValami(HarmadikBalfasz);
	CAddress NegyedikValami(NegyedikBalfasz);
	std::cout << Valami.IsTheSame(MasikValami);
	return 0;
}

