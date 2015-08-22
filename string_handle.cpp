#include "string_handle.hpp"

#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <sstream>

std::string
trim(const std::string& str)
{
    int cnt_beg = 0;
    int cnt_end = 0;

    for(auto c: str)
    {
        if(c == ' ' || c == ',') cnt_beg++;
        else break;
    }

    for(int i = str.length(); i >= 0; i--)
    {
         if(str[i] == ' ' || str[i] == ',') cnt_end++;
         break;
    }

    return str.substr(cnt_beg, str.length() - cnt_beg - cnt_end);
}

std::string
join(std::vector<std::string>& vec, char sep, int start, int end)
{
    std::string str = "";
    for(int i = start; i <= end; i++)
    {
        if(i != end) str += vec.at(i) + sep;
        else str += vec.at(i);
    }

    return str;
}

void
char_remove(std::string& str,const std::string& remove_chars)
{
    for(auto c: remove_chars)
        str.erase (std::remove(str.begin(), str.end(), c), str.end());
}

/*splits the given str by delim and stores the chunks in elems*/
std::vector<std::string>&
split(const std::string &str, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

std::string
str_hash(const std::string& str)
{
    std::vector<std::string> codes;
    DoubleMetaphone(str, &codes);
    return codes[0] + codes[1];
}

double WordCheck(const std::string& sFirstWord, const std::string& sSecondWord){
    int iMinSize = sFirstWord.length();
    int iMaxSize = sSecondWord.length();
    if (iMinSize > iMaxSize)
    {
        int tmp = iMinSize;
        iMinSize = iMaxSize;
        iMaxSize = tmp;
    }

	double fReturnValue = 0;

	for (int i = 0; i < iMinSize; i++)
		if (sFirstWord[i] == sSecondWord[i]) fReturnValue++;

	return fReturnValue / iMaxSize;
}


double StringCheck(const std::string& sFirstString, const std::string& sSecondString){
	std::vector<std::string> saFirstString, saSecondString;
	split(sFirstString, ' ', saFirstString);
	split(sSecondString, ' ', saSecondString);
	std::vector<double> faSimilarities;

	for (auto str_a : saFirstString){
		double fMaxSimilarity = 0.0;
		for (auto str_b : saSecondString){
			double fCompare = WordCheck(str_a, str_b);
			if (fCompare > fMaxSimilarity)
				fMaxSimilarity = fCompare;
		}
		faSimilarities.push_back(fMaxSimilarity);
	}

	double fProbabilitySum = 0.0;
	for (uint i = 0; i < saFirstString.size(); i++)
		fProbabilitySum += faSimilarities.at(i) * saFirstString.at(i).length();
	return fProbabilitySum / (sFirstString.length() - saFirstString.size() + 1);
}

int StringExactMatch(const std::vector<std::string>& lhs_string,
                     const std::vector<std::string>& rhs_string)
{
    int matches = 0;
    for(auto str_lhs: lhs_string)
    {
        for(auto str_rhs: rhs_string)
        {
            if(str_lhs == str_rhs) matches++;
        }
    }

    return matches;
}


std::string StringWordRemove(std::string sString){
	std::vector<std::string> saSpaceSplit, saResultString;
	bool bFlag;
	split(sString, ' ', saSpaceSplit);
	for (int i = 0; i < saSpaceSplit.size() - 1; i++){
		bFlag = true;
		for (int j = i + 1; j < saSpaceSplit.size(); j++){
			if (str_hash(saSpaceSplit[i]) == str_hash(saSpaceSplit[j]))
				bFlag = false;
		}
		if (bFlag)
			saResultString.push_back(saSpaceSplit[i]);
	}
	saResultString.push_back(saSpaceSplit[saSpaceSplit.size()-1]);
	return join(saResultString, ' ', 0, saResultString.size() - 1);
}
