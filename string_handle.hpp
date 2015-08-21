#ifndef STRING_HANDLE_HPP
#define STRING_HANDLE_HPP

#include <string>
#include <vector>

#include "double_metaphone.h"

std::string trim(const std::string&  str);
std::string join(std::vector<std::string>&, char, int , int);
void char_remove(std::string&,const std::string&);
std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
std::string str_hash(const std::string& str);
double WordCheck(const std::string& sFirstWord, const std::string& sSecondWord);
double StringCheck(const std::string& sFirstString, const std::string& sSecondString);
int StringExactMatch(const std::vector<std::string>&, const std::vector<std::string>&);

#endif
