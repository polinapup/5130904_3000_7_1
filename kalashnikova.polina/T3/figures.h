#ifndef FIGURES_H
#define FIGURES_H

#include "local.h"

namespace kalashnikova
{
    struct Point
    {
        int x, y;
        double getDistance(const Point& point) const;
        bool operator !=(const Point& other) const;
    };

    double getTriangleArea(const Point& point, const Point& point2, const Point& point3);

    struct Polygon
    {
        std::vector<Point> points;
        double getArea() const;
        bool operator <(const Polygon& other) const;
        bool operator ==(const Polygon& other) const;
    };

    struct DelimiterIO
    {
        char exp;
    };

    std::istream& operator>>(std::istream& in, kalashnikova::DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, kalashnikova::Point& point);
    std::istream& operator>>(std::istream& in, kalashnikova::Polygon& polygon);
    std::ostream& operator<<(std::ostream& out, const kalashnikova::Point& point);
    std::ostream& operator<<(std::ostream& out, const kalashnikova::Polygon& polygon);
}

#endif

