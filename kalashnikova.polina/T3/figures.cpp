#include "figures.h"

double kalashnikova::Point::getDistance(const Point& point_) const
{
    double dist = 0;
    dist = sqrt((x - point_.x) * (x - point_.x) + (y - point_.y) * (y - point_.y));
    return dist;
}

bool kalashnikova::Point::operator !=(const Point& other) const
{
    return x != other.x or y != other.y;
}

double kalashnikova::getTriangleArea(const Point& point_, const Point& point2, const Point& point3)
{
    double side_ = point_.getDistance(point2);
    double side2 = point2.getDistance(point3);
    double side3 = point_.getDistance(point3);
    double perimeter = (side_ + side2 + side3) / 2;
    double tr_area = 0;
    tr_area = sqrt(perimeter * (perimeter - side_) * (perimeter - side2) * (perimeter - side3));
    return tr_area;
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

double kalashnikova::Polygon::getArea() const
{
    const Point point_ = points[0];
    Point last = points[1];
    return std::accumulate(points.begin() + 2, points.end(), 0.0, [&point_, &last](double accumulatedArea, const Point& current)
        {
            double tr_area = getTriangleArea(point_, last, current);
            accumulatedArea += tr_area;
            last = current;
            return accumulatedArea;
        }
    );
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::DelimiterIO&& dest)
{
    std::istream::sentry sentry_(in);
    if (!sentry_)
    {
        return in;
    }
    char char_ = '0';
    in >> char_;
    if (in && (char_ != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::Point& point_)
{
    std::istream::sentry sentry_(in);
    if (!sentry_)
    {
        return in;
    }

    in >> kalashnikova::DelimiterIO{ '(' } >> point_.x >> kalashnikova::DelimiterIO{ ';' } >> point_.y >> kalashnikova::DelimiterIO{ ')' };
    return in;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::Polygon& polygon)
{
    std::istream::sentry sentry_(in);
    if (!sentry_)
    {
        return in;
    }

    size_t sumPoints;
    in >> sumPoints;
    if (sumPoints < 3)
    {
        in.setstate(std::istream::failbit);
        return in;
    }

    polygon.points.clear();
    polygon.points.resize(sumPoints);

    for (kalashnikova::Point& point : polygon.points)
    {
        in >> point;
    }

    return in;
}

std::ostream& kalashnikova::operator<<(std::ostream& out, const kalashnikova::Point& point_)
{
    std::ostream::sentry sentry_(out);
    if (!sentry_)
    {
        return out;
    }
    out << "(" << point_.x << ";" << point_.y << ")";
    return out;
}

std::ostream& kalashnikova::operator<<(std::ostream& out, const kalashnikova::Polygon& polygon)
{
    std::ostream::sentry sentry_(out);
    if (!sentry_)
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
