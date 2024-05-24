#include "methods.h"

const std::string ERROR = "<INVALID COMMAND>";

using namespace kalashnikova;
using namespace std::placeholders;

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
            double res = accumulatedArea;
            if (method == "EVEN" and current.points.size() % 2 == 0)
            {
                res += current.getArea();
            }
            else if (method == "ODD" and current.points.size() % 2 != 0)
            {
                res += current.getArea();
            }
            else if (method == "MEAN")
            {
                res += current.getArea();
            }
            else if (method == "SPECIAL" and current.points.size() == static_cast<size_t>(num))
            {
                res += current.getArea();
            }
            return res;
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

    std::vector<size_t> vec_size(polygons.size());

    std::transform(polygons.begin(), polygons.end(), vec_size.begin(),
        [](const Polygon& poly)
        {
            return poly.points.size();
        });
    auto polygon = std::max_element(polygons.begin(), polygons.end());
    auto maxSize = std::max_element(vec_size.begin(), vec_size.end());

    if (string == "AREA")
    {
        std::cout << polygon->getArea() << std::endl;
    }
    else if (string == "VERTEXES")
    {
        std::cout << *maxSize << std::endl;
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

    std::vector<size_t> vec_size(polygons.size());

    std::transform(polygons.begin(), polygons.end(), vec_size.begin(),
        [](const Polygon& poly)
        {
            return poly.points.size();
        });

    auto polygon = std::min_element(polygons.begin(), polygons.end());
    auto minSize = std::min_element(vec_size.begin(), vec_size.end());

    if (string == "AREA")
    {
        std::cout << polygon->getArea() << std::endl;
    }
    else if (string == "VERTEXES")
    {
        std::cout << *minSize << std::endl;
    }
    else
    {
        throw ERROR;
    }
}

void methods::getCounter(const std::vector<Polygon>& polygons)
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

void methods::lessarea(std::vector<Polygon>& polygons)
{
    if (polygons.empty())
    {
        throw ERROR;
    }

    Polygon basic;
    std::cin >> basic;

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

    auto concurrent = [&](const Polygon polygon)
        {
            bool res = std::greater<double>()(basic.getArea(), polygon.getArea());
            return res;
        };

    std::cout << std::count_if(polygons.begin(), polygons.end(), concurrent) << std::endl;
}

void methods::same(std::vector<Polygon>& polygons)
{
    if (polygons.empty())
    {
        throw ERROR;
    }

    Polygon basic;
    std::cin >> basic;

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
            if (basic == tPolygon)
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
    count = std::count_if(polygons.begin(), polygons.end(), counter);
    std::cout << count << "\n";
}
