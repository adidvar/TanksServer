#include "math_tools/shapes.h"

void PointShape::ToLines(std::back_insert_iterator<std::vector<Line>> inserter) const
{
    for(size_t index = 1 ; index < this->points.size() ; ++index)
    {
        Vector normale = (points[index] - points[index-1]).Rotate(convexity ? M_PI_2 : -M_PI_2).Nomalize();
        *inserter = Line{this->points[index-1],this->points[index],normale};
        ++inserter;
    }
    Vector normale = (points[0]- points[points.size()-1]).Rotate(convexity ? M_PI_2 : -M_PI_2).Nomalize();
    *inserter = Line{this->points[0],this->points[points.size()-1],normale};
    ++inserter;
}

void MultiPointShape::ToLines(std::back_insert_iterator<std::vector<Line>> inserter) const
{
    for(const auto &shape: this->shapes)
        shape.ToLines(inserter);
}

