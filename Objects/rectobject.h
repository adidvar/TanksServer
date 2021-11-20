#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include <string>
#include <memory>
#include <mvector.h>

#include "object.h"

class RectObject : public Object
{
protected:

	Vector position;
	Vector size;
    float rotate;

public:
    RectObject(ObjectInterface & interface , Vector position , Vector size , float rotate , bool active);
    MultiPointShape RectObject::Poligon() const;
};

#endif // TANK_H
