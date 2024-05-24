#ifndef METHODS_H
#define METHODS_H

#include "local.h"
#include "figures.h"

namespace methods
{
    int makeNumber(const std::string& str);
    void getWholeArea(const std::vector<kalashnikova::Polygon>& polygons);
    void getMax(const std::vector<kalashnikova::Polygon>& polygons);
    void getMin(const std::vector<kalashnikova::Polygon>& polygons);
    void getQuantity(const std::vector<kalashnikova::Polygon>& polygons);
    void lessarea(std::vector<kalashnikova::Polygon>& polygons);
    void same(std::vector<kalashnikova::Polygon>& polygons);
}

#endif
