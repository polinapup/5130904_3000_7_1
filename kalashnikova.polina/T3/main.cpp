#include "methods.h"

using namespace kalashnikova;
using namespace methods;

const std::string ERROR = "<INVALID COMMAND>";
const std::string ERROR_2 = "ERROR: Filename is incorrect";
const std::string ERROR_3 = "ERROR: File is not exist";

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << ERROR_2 << "\n";
        return EXIT_FAILURE;
    }

    const std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << ERROR_3 <<"\n";
        return EXIT_FAILURE;
    }

    std::cout << std::setprecision(1) << std::fixed;

    std::vector<Polygon> vector;

    while (!file.eof())
    {
        std::copy(std::istream_iterator<Polygon>(file),
            std::istream_iterator<Polygon>(),
            std::back_inserter(vector));

        if (file.fail() and !file.eof())
        {
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (!std::cin.eof())
    {
        std::string command;
        std::cin >> command;
        try
        {
            if (command == "AREA")
            {
                getWholeArea(vector);
            }
            else if (command == "MAX")
            {
                getMax(vector);
            }
            else if (command == "MIN")
            {
                getMin(vector);
            }
            else if (command == "COUNT")
            {
                getQuantity(vector);
            }
            else if (command == "LESSAREA")
            {
                lessArea(vector);
            }
            else if (command == "SAME")
            {
                same(vector);
            }
            else if (command != "")
            {
                throw ERROR;
            }
        }
        catch (const char* error)
        {
            std::cout << error << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return EXIT_SUCCESS;
}
