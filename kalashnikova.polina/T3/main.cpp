#include "methods.h"

const std::string ERROR = "<INVALID COMMAND>";
const std::string ERROR_FILENAME = "ERROR: Filename isn't correct";
const std::string ERROR_NO_FILE = "ERROR: No file found";

using namespace kalashnikova;
using namespace methods;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << ERROR_FILENAME << "\n";
        return EXIT_FAILURE;
    }

    const std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << ERROR_NO_FILE << "\n";
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
        std::string cmd;
        std::cin >> cmd;
        try
        {
            if (cmd == "AREA")
            {
                getWholeArea(vector);
            }
            else if (cmd == "MAX")
            {
                getMax(vector);
            }
            else if (cmd == "MIN")
            {
                getMin(vector);
            }
            else if (cmd == "COUNT")
            {
                getCounter(vector);
            }
            else if (cmd == "LESSAREA")
            {
                lessarea(vector);
            }
            else if (cmd == "SAME")
            {
                same(vector);
            }
            else if (cmd != "")
            {
                throw ERROR;
            }
        }
        catch (const std::string &error)
        {
            std::cout << error << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return EXIT_SUCCESS;
}
