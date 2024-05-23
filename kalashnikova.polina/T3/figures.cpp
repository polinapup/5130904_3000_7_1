#include "figures.h"

double kalashnikova::Point::getDistance(const Point& point) const
{
    double dist = 0;
    dist = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
    return dist;
}

bool kalashnikova::Point::operator !=(const Point& other) const
{
    return x != other.x or y != other.y;
}

double kalashnikova::getTriangleArea(const Point& point, const Point& point2, const Point& point3)
{
    double side = point.getDistance(point2);
    double side2 = point2.getDistance(point3);
    double side3 = point.getDistance(point3);
    double perimeter = (side + side2 + side3) / 2;
    double area = 0;
    area = sqrt(perimeter * (perimeter - side) * (perimeter - side2) * (perimeter - side3));
    return area;
}

double kalashnikova::Polygon::getArea() const
{
  const Point point = points[0];
  Point pointLast = points[1];
  return std::accumulate(points.begin() + 2, points.end(), 0.0, [&point, &pointLast](double accumulatedArea, const Point& current)
    {
      double triangleArea = getTriangleArea(point, pointLast, current);
      accumulatedArea += triangleArea;
      pointLast = current;
      return accumulatedArea;
    }
  );
}

bool kalashnikova::Polygon::operator <(const Polygon& other) const
{
    return getArea() < other.getArea();
}

bool kalashnikova::Polygon::operator ==(const Polygon& other) const
{
    if (points.size() != other.points.size())
    {
        return false;
    }
    for (size_t i = 0; i < points.size(); i++)
    {
        if (points[i] != other.points[i])
        {
            return false;
        }
    }
    return true;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char zero = '0';
    in >> zero;
    if (in && (zero != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::Point& point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> kalashnikova::DelimiterIO{ '(' } >> point.x >> kalashnikova::DelimiterIO{ ';' } >> point.y >> kalashnikova::DelimiterIO{ ')' };
    return in;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    size_t amtPoints;
    in >> amtPoints;
    if (amtPoints < 3)
    {
        in.setstate(std::istream::failbit);
        return in;
    }

    polygon.points.clear();
    polygon.points.resize(amtPoints);

    for (kalashnikova::Point& point : polygon.points)
    {
        in >> point;
    }

    return in;
}

std::ostream& kalashnikova::operator<<(std::ostream& out, const kalashnikova::Point& point)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << "(" << point.x << ";" << point.y << ")";
    return out;
}

std::ostream& kalashnikova::operator<<(std::ostream& out, const kalashnikova::Polygon& polygon)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }

    out << polygon.points.size() << " ";

    for (const kalashnikova::Point& point : polygon.points)
    {
        out << point << " ";
    }

    return out;
}
