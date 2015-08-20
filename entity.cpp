#include <iostream>
#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <fstream>

#include "entity.hpp"
#include "double_metaphone.h"

std::string
trim(std::string str)
{
    int cnt_beg = 0;
    int cnt_end = 0;

    for(auto c: str)
        if(c == ' ' || c == ',')
            cnt_beg++;
        else
            break;

    for(int i = str.length(); i >= 0; i--)
    {
         if(str[i] == ' ' || str[i] == ',')
             cnt_end++;
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
        if(i != end)
            str += vec.at(i) + sep;
        else
            str += vec.at(i);
    }

    return str;
}

void
char_remove(std::string& str, std::string remove_chars)
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
str_hash(std::string& str)
{
    std::vector<std::string> codes;
    DoubleMetaphone(str, &codes);
    return codes[0] + codes[1];
}

//TODO: what about INC, LLC?
std::unordered_map<std::string, std::string> specs_map =
{
    {"INC", ""},
    {"LLC", ""},
    {"PHD", "majom"},
    {"MD", ""},
    {"M D", ""},
    {"PA", ""},
    {"DDS", ""},
    {"CNP", ""},
    {"ATC", ""},
    {"LAT", ""},
    {"CRNA", ""},
    {"DPM", ""},
    {"OD", ""},
    {"ANP", ""},
    {"MSW", "MASTER OF SOCIAL WORK"},
    {"LCSW", "LICENSED CLINICAL SOCIAL WORKER"},
    {"RPH", "REGISTERED PHARMACIST"},
    {"MSPT", "MASTER OF SCIENCE IN PHYSICAL THERAPY"},
    {"DO", ""},
    {"DDS", ""},
    {"MS", ""},
    {"FNP", "FAMILY NURSE PRACTIONER"},
    {"ACSW", "ACADEMY OF CERTIFIED SOCIAL WORKERS"},
    {"PA-C", "PHYSICIAN ASSISTANT CERTIFIED"},
    {"AA-C", "CERTIFIED ANESTHESIOLOGIST ASSISTANT"},
    {"RPH", "REGISTERED PHARMACIST"},
    {"OTR", "REGISTERED OCCUPATIONAL THERAPIST"},
    {"OTR/L", "OCCUPATIONAL THERAPIST"},
    //{"JR", ""},
    {"CLL", ""},
    {"ANP", "ADVANCED NURSE PRACTITIONER"},
    {"RNC", "REGISTERED NURSE CERTIFIED"},
    {"DC", "DOCTOR OF CHIROPRACTIC"},
    {"PAAA", ""}, //MRS ALISA A KEATS
    {"PC", ""},
    {"TS", ""}, //example
    {"AUD", "AUDIOLOGIST"},
    {"DPH", "DOCTOR OF PHARMACY"}, //PHARMACIST
    //{"LLC", ""},
    {"PT", "PHYSICAL THERAPIST"},
    {"PAC", "CERTIFIED PHYSICIAN ASSISTANT"},
    {"ARNP", "ADVANCED REGISTERED NURSE PRACTITIONER"},
    {"SCLW", "SOCIAL WORKER"}, //LSCW mistyped?
    {"LP", "LICENSED PSYCHOLOGIST"},
    {"LMFT", "LICENSED MARRIAGE AND FAMILY THERAPIST"},
    {"PA", "PHYSICIAN ASSISTANT"},
    {"GNP", "GERONTOLOGICAL NURSE PRACTITIONER"},
    {"CNM", "CERTIFIED NURSE MIDWIFE"},
    {"ACNP", ""},
    {"DMD", ""},
    {"D C", ""},
    {"MBA", ""},
    {"PSY", ""},
    {"LTD", ""},
    {"MSD", ""},
    {"NP", ""},
    {"LICSW", ""},
    {"SCO", ""},
    {"PT", ""},
    {"CRNP", ""},
    {"APRN", ""},
    {"MDD", ""},
    {"LLP", ""},
    {"ARPN", ""},
    {"FAAP", ""},
    {"BMBS", ""},
    {"LSW", ""},
    {"LP", ""},
    {"ART", ""},
    {"ACDC", ""},
    {"CLPC", ""},
    {"RPT", ""},
    {"PTA", ""},
    {"RD", ""},
    {"CFNP", ""},
    {"LTA", ""},
    {"PT", ""},
    {"LMHC", ""},
    {"DNP", ""},
    {"NIC", ""},
    {"PHARMD", ""},
    {"SC", ""},
    {"HSPP", ""},
    {"MHP", ""},
    {"PDM", ""},
    {"PSYD", ""},
    {"OTHALMIC DISPENSER", ""}, //like OD
    {"FACR", ""},
    {"CRPN", ""},
    {"CAP", ""},
    {"ACT", ""},
    //{"PA C", ""},
    {"LDN", ""},
    {"OCS", ""},
    //{"PH D", ""},
    {"HPD", ""},
    {"OT", ""},
    {"CDER", ""},
    {"D C", ""},
    {"MSN", ""},
    {"RN", ""},
    {"MTD", ""},
    {"MPH", ""},
    {"CSCS", ""},
};

std::unordered_map<std::string, std::string> title_map =
{
    {"DR", "DR"},
    {"RD", "DR"},
    {"MR", "MR"},
    {"MRS", "MRS"},
    {"MS", "MS"},
    {"JR", "JR"}
};

std::unordered_map<std::string, std::vector<std::string>> nicknames_map;

/* Generates an unordered_map with the nicknames as the key
 * and a vector of 'normal' names that can be associated with
 * the nickname.
*/
void
read_nicknames(const char *file_name)
{
    std::ifstream file(file_name);

    std::string line;
    while(std::getline(file, line))
    {
        //Make it uppercase
        boost::to_upper(line);

        std::vector<std::string> chunks;
        split(line, ',', chunks);

        for(uint i = 1; i < chunks.size(); i++)
        {
            //Look for the nickname in nicknames_map
            auto search = nicknames_map.find(chunks.at(i));
            if(search != nicknames_map.end())
            {
                search->second.push_back(chunks.at(0));
                //std::cout << "pushed: " << search->first + " " + chunks.at(0);
            }
            else
            {
                nicknames_map.insert({trim(chunks.at(i)), {trim(chunks.at(0))}});
                //std::cout << "inserted: " << trim(chunks.at(i)) + " " + trim(chunks.at(0));
            }
        }
    }

    file.close();
}

void
Name::get_specs(std::string& name)
{
    //Split name by ',' to separate the end
    std::vector<std::string> items;
    split(name, ',', items);

    try
    {
        for(int i = items.size()-1; i >= 0; i--)
        {
            std::vector<std::string> chunks;
            split(trim(items[i]), ' ', chunks);

            for(int j = chunks.size()-1; j >= 0; j--)
            {
                auto find = specs_map.find(trim(chunks.at(j)));
                if(find != specs_map.end())
                {
                    this->specs.push_back(find->first);
                }
                else
                {
                    if(i == 0)
                        name = join(chunks, ' ', 0, j);

                    else
                        name = join(items, ' ', 0, i-1);
                    throw true;
                }
            }
        }
    }
    catch (bool e) {};
}

void
Name::get_title(std::string& name)
{
    std::vector<std::string> chunks;
    split(name, ' ', chunks);

    //I think it's enough if we just check the first chunk
    auto search = title_map.find(trim(chunks.front()));
    if(search != title_map.end())
    {
        this->title.push_back(search->second);
        name = join(chunks, ' ', 1, chunks.size()-1);
    }

    search = title_map.find(trim(chunks.back()));
    if(search != title_map.end())
    {
        this->title.push_back(search->second);

        std::vector<std::string> new_chunks;
        split(name, ' ', new_chunks);
        name = join(new_chunks, ' ', 0, new_chunks.size()-2);
    }
}

void
Name::get_nickname(std::string& name)
{
    //TODO: There're names that can be a name and a nickname as well like 'ellen'
    std::vector<std::string> chunks;
    split(name, ' ', chunks);
    for(auto str: chunks)
    {
        auto search = nicknames_map.find(trim(str));
        if(search != nicknames_map.end())
        {
            //std::cout << "nickname found: " << str << std::endl;
            //getchar();
        }
    }
}

Name::Name(std::string name)
{
    //std::cout << name << std::endl;

    //Remove points from the name
    char_remove(name, std::string("."));

    //To separate the specs
    this->get_specs(name);

    //To separate the title (mr, mrs, dr, ms..)
    this->get_title(name);

    this->get_nickname(name);
}

Taxonomies::Taxonomies(std::string tax)
{
    //TODO
    //std::cout << tax << std::endl;
}
