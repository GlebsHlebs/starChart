#pragma once

#include "Color.h"
#include "Cooridnates.h"
#include "Object.h"

class Sphere : public Object {
private:
    double radius;
public:
    Sphere();
    Sphere(Coordinates, Color, double);

    double getRadius() const;

    void setRadius(double radius);
};