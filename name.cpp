#include "name.hpp"

#include <unordered_map>
#include <sstream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <omp.h>

#include "string_handle.hpp"

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
/*void
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
*/

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
    //Remove points from the name
    char_remove(name, std::string("."));

    //To separate the specs
    this->get_specs(name);

    //To separate the title (mr, mrs, dr, ms..)
    this->get_title(name);

    this->name = name;
}

bool find_abbrev(const std::string& c, const std::vector<std::string>& rhs_chunks)
{
    for(auto str: rhs_chunks)
        if(str[0] == c[0]) return true;

    return false;
}

bool contains_abbrev(const std::vector<std::string>& lhs_chunks,
                     const std::vector<std::string>& rhs_chunks)
{
    for(auto str: lhs_chunks)
    {
        if(str.length() == 1)
        {
            if(find_abbrev(str, rhs_chunks)) return true;
        }
    }

    for(auto str: rhs_chunks)
    {
         if(str.length() == 1)
         {
            if(find_abbrev(str, lhs_chunks)) return true;
         }
    }

    return false;
}

int Name::name_cmp(const Name& rhs_name)
{
    std::vector<std::string> lhs_chunks;
    std::vector<std::string> rhs_chunks;
    split(this->name, ' ', lhs_chunks);
    split(rhs_name.name, ' ', rhs_chunks);

    double name_cmp = StringCheck(this->name, rhs_name.name);

    if(name_cmp > 0.5 && contains_abbrev(lhs_chunks, rhs_chunks))
    {
         name_cmp *= 0.8;
         name_cmp += 0.2;
    }

    if(name_cmp >= 0.75) return 3;
    else if(name_cmp >= 0.5 && name_cmp < 0.75) return 2;
    else if(name_cmp >= 0.25 && name_cmp < 0.5) return 1;
    else return 0;
}

int Name::title_cmp(const Name& rhs_name)
{
    int same_titles = StringExactMatch(this->title, rhs_name.title);
    int title_min_cnt = std::min(this->title.size(), rhs_name.title.size());

    if(title_min_cnt == 0) return 0;
    else return same_titles / title_min_cnt;
}

int Name::specs_cmp(const Name& rhs_name)
{
   int same_specs = StringExactMatch(this->specs, rhs_name.specs);
   int specs_min_cnt = std::min(this->specs.size(), rhs_name.specs.size());

   if(specs_min_cnt == 0) return 0;
   else return (same_specs / (double) specs_min_cnt) >= 0.5;
}

int Name::NameBitMapMaker(const Name& rhs_name)
{
    int name_sim, title_sim, specs_sim;
    #pragma omp parallel
    {
        name_sim = this->name_cmp(rhs_name); //2 bits
        title_sim = this->title_cmp(rhs_name); //1 bit
        specs_sim = this->specs_cmp(rhs_name); //1 bit
    }

    int result = name_sim + (title_sim << 2) + (specs_sim << 3);
    return result;
}
