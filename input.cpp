#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "data.hpp"
#include "csvparser.h"
#include "Address.h"

static char** parse_line(CsvParser *parser)
{
    CsvRow *row = CsvParser_getRow(parser);
    if(row == NULL)
        throw std::out_of_range("");

    return CsvParser_getFields(row);
}

//TODO: should return a ref to a container
void
read_file(const char* file)
{
    CsvParser *parser = CsvParser_new(file, ",", 0);

    while(true)
    {
        char **rowFields;
        try
        {
            rowFields = parse_line(parser);

            int id = boost::lexical_cast<int>(rowFields[0]);
            Name name(trim(rowFields[1]));
            CAddress address(trim(rowFields[2]));
            Taxonomies taxonomies(trim(rowFields[3]));

            //TODO: Store the entities in a container
            Entity entity(id, name, address, taxonomies);
            getchar();
        }
        catch (std::out_of_range& oor) { break; }
    }

    CsvParser_destroy(parser);
}
