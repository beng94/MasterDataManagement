#include "csvparser.h"
#include <stdexcept>

char** parse_line(CsvParser *parser)
{
    CsvRow *row = CsvParser_getRow(parser);
    if(row == NULL)
        throw std::out_of_range("");

    return CsvParser_getFields(row);
}

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
        }
        catch (std::out_of_range& oor) { break; }
    }

    CsvParser_destroy(parser);
}


int main() {
    read_file("training_data.csv");
}
