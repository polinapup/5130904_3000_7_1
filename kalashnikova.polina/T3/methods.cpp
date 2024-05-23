#include "methods.h"

using namespace kalashnikova;
using namespace std::placeholders;

const std::string ERROR = "<INVALID COMMAND>";

int methods::makeNumber(const std::string& str)
{
    try
    {
        return std::stoi(str);
    }
    catch (const std::invalid_argument&)
    {
        return -1;
    }
    catch (const std::out_of_range&)
    {
        return -1;
    }
}

void methods::getWholeArea(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;
    int num = makeNumber(string);
    auto accumulateArea = [&polygons, &num]
    (double accumulatedArea, const Polygon& current, const std::string method)
        {
            double result = accumulatedArea;
            if (method == "EVEN" and current.points.size() % 2 == 0)
            {
                result += current.getArea();
            }
            else if (method == "ODD" and current.points.size() % 2 != 0)
            {
                result += current.getArea();
            }
            else if (method == "MEAN")
            {
                result += current.getArea();
            }
            else if (method == "SPECIAL" and current.points.size() == static_cast<size_t>(num))
            {
                result += current.getArea();
            }
            return result;
        };

    if (num == -1)
    {
        if (string == "EVEN" or string == "ODD")
        {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                std::bind(accumulateArea, _1, _2, string)) << std::endl;
        }
        else if (string == "MEAN" and polygons.size() != 0)
        {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                std::bind(accumulateArea, _1, _2, string)) / polygons.size() << std::endl;
        }
        else
        {
            throw ERROR;
        }
    }
    else if (num > 2)
    {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            std::bind(accumulateArea, _1, _2, "SPECIAL")) << std::endl;
    }
    else
    {
        throw ERROR;
    }
}

void methods::getMax(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;

    if (polygons.size() == 0)
    {
        throw ERROR;
    }

    std::vector<size_t> vecSize(polygons.size());

    std::transform(polygons.begin(), polygons.end(), vecSize.begin(),
        [](const Polygon& poly)
        {
            return poly.points.size();
        });
    auto polygon = std::max_element(polygons.begin(), polygons.end());
    auto sizeMax = std::max_element(vecSize.begin(), vecSize.end());

    if (string == "AREA")
    {
        std::cout << polygon->getArea() << std::endl;
    }
    else if (string == "VERTEXES")
    {
        std::cout << *sizeMax << std::endl;
    }
    else
    {
        throw ERROR;
    }
}

void methods::getMin(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;

    if (polygons.size() == 0)
    {
        throw ERROR;
    }

    std::vector<size_t> vectorSize(polygons.size());

    std::transform(polygons.begin(), polygons.end(), vectorSize.begin(),
        [](const Polygon& poly)
        {
            return poly.points.size();
        });

    auto polygon = std::min_element(polygons.begin(), polygons.end());
    auto sizeMin = std::min_element(vectorSize.begin(), vectorSize.end());

    if (string == "AREA")
    {
        std::cout << polygon->getArea() << std::endl;
    }
    else if (string == "VERTEXES")
    {
        std::cout << *sizeMin << std::endl;
    }
    else
    {
        throw ERROR;
    }
}

void methods::getQuantity(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;
    int num = makeNumber(string);
    auto count = [&num](const Polygon& polygon, const std::string& method)
        {
            if (method == "EVEN")
            {
                return polygon.points.size() % 2 == 0;
            }
            else if (method == "ODD")
            {
                return polygon.points.size() % 2 != 0;
            }
            else if (method == "SPECIAL")
            {
                return polygon.points.size() == static_cast<size_t>(num);
            }
            return false;
        };

    if (num == -1)
    {
        if (string == "EVEN" or string == "ODD")
        {
            std::cout << std::count_if(polygons.begin(), polygons.end(),
                std::bind(count, _1, string)) << std::endl;
        }
        else
        {
            throw ERROR;
        }
    }
    else if (num > 2)
    {
        std::cout << std::count_if(polygons.begin(), polygons.end(),
            std::bind(count, _1, "SPECIAL")) << std::endl;
    }
    else
    {
        throw ERROR;
    }
}

void methods::lessArea(std::vector<Polygon>& polygons)
{
    if (polygons.empty())
    {
        throw ERROR;
    }

    Polygon base;
    std::cin >> base;

    auto space = std::find_if_not(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), isspace);
    if (*space == std::iostream::traits_type::eof() or *space == int('n'))
    {
        throw ERROR;
    }
    if (!isspace(*space))
    {
        std::cin.setstate(std::ios_base::failbit);
        throw ERROR;
    }

    auto comparison = [&](const Polygon polygon)
        {
            bool result = std::greater<double>()(base.getArea(), polygon.getArea());
            return result;
        };

    std::cout << std::count_if(polygons.begin(), polygons.end(), comparison) << std::endl;
}

void methods::same(std::vector<Polygon>& polygons)
{
    if (polygons.empty())
    {
        throw ERROR;
    }

    Polygon base;
    std::cin >> base;

    auto space = std::find_if_not(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), isspace);
    if (*space == std::iostream::traits_type::eof() or *space == int('n'))
    {
        throw ERROR;
    }
    if (!isspace(*space))
    {
        std::cin.setstate(std::ios_base::failbit);
        throw ERROR;
    }

    int count = 0;

    auto counter = [&](const Polygon tPolygon)
        {
            if (base == tPolygon)
            {
                count++;
            }
            else
            {
                count = 0;
                return false;
            }
            return true;
        };
    std::cout << std::count_if(polygons.begin(), polygons.end(), counter) << "\n";
}
