class Name
{
public:
    /*write members here*/
    //title: DR, MD, INC, DDS, MS, DPM, OD, etc
    //name: store it in an array

    Name(const char* name);

private:
    /* TODO:
     * -trim the name
     */
};

class Address
{
public:
    /*write members here*/
    //country
    //state
    //zip code

    Address(const char* address);
private:
    /* TODO:
     * - convert zip code
     */
};

class Taxonomies
{
public:
    /*write members here*/
    //should have an array of taxonomies

    Taxonomies(const char* taxonomies);
};

class Entity
{
public:
    int id;
    Name name;
    Address address;
    Taxonomies taxonomies;
}
