#include "geometry.h"

double abrosimov::Point::getDistance(const Point& point) const
{
    double distance = 0;
    distance = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
    return distance;
}
bool abrosimov::Point::operator !=(const Point& other) const
{
    return x != other.x or y != other.y;
}
double abrosimov::getTriangleArea(const Point& point1, const Point& point2, const Point& point3)
{
    double firstSide = point1.getDistance(point2);
    double secondSide = point2.getDistance(point3);
    double thirdSide = point1.getDistance(point3);
    double halfPerimeter = (firstSide + secondSide + thirdSide) / 2;
    double triangleArea = 0;
    triangleArea = sqrt(halfPerimeter * (halfPerimeter - firstSide) * (halfPerimeter - secondSide) * (halfPerimeter - thirdSide));
    return triangleArea;
}
bool abrosimov::Polygon::operator <(const Polygon& other) const
{
    return getArea() < other.getArea();
}
bool abrosimov::Polygon::operator ==(const Polygon& other) const
{
    return points == other.points;
}
double abrosimov::Polygon::getArea() const
{
    const Point pointFirst = points[0];
    Point prev = points[1];
    return std::accumulate(points.begin() + 2, points.end(), 0.0,[&pointFirst, &prev]
    (double accumulatedArea, const Point& current)
        {
            double TriangleArea = getTriangleArea(pointFirst, prev, current);
            accumulatedArea += TriangleArea;
            prev = current;
            return accumulatedArea;
        }
    );
}
std::istream& abrosimov::operator>>(std::istream& in, abrosimov::DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char null = '0';
    
    in >> null;
    
    if (in && (null != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}
std::istream& abrosimov::operator>>(std::istream& in, abrosimov::Point& point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    
    in >> abrosimov::DelimiterIO{ '(' } >> point.x >> abrosimov::DelimiterIO{ ';' } >> point.y >> abrosimov::DelimiterIO{ ')' };
    return in;
}
std::istream& abrosimov::operator>>(std::istream& in, abrosimov::Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    size_t numPoints;
    
    in >> numPoints;
    
    if (numPoints < 3)
    {
        in.setstate(std::istream::failbit);
        return in;
    }
    
    polygon.points.clear();
    polygon.points.resize(numPoints);
    
    std::copy_n(std::istream_iterator<abrosimov::Point>(in), numPoints, std::back_inserter(polygon.points));
    
    return in;
}
std::ostream& abrosimov::operator<<(std::ostream& out, const abrosimov::Point& point)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << "(" << point.x << ";" << point.y << ")";
    return out;
}
std::ostream& abrosimov::operator<<(std::ostream& out, const abrosimov::Polygon& polygon)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    
    out << polygon.points.size() << " ";
    
    std::copy(polygon.points.begin(), polygon.points.end(), std::ostream_iterator<abrosimov::Point>(out, " "));
    
    return out;
}

