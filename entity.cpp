#include "entity.h"
#include <sstream>

void entity::write_state(std::stringstream &s, char sep)
{
    s << position.x << sep << position.y << sep << rotation << sep;
}
