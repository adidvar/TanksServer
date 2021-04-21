#include "wall.h"

void wall::write_state(std::stringstream &s, char sep)
{
    s << positions.x << sep << positions.y << sep << size.x << sep << size.y << sep << rotation << sep;
}
