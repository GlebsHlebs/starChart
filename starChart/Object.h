#pragma once

#include "Color.h"
#include "Cooridnates.h"

class Object {
protected:
    Coordinates coords;
    Color color;
public:
    Object();
    Object(Coordinates, Color);

    Coordinates getCoordinates() const;
    Color getColor() const;

    void getCoordinates(Coordinates);
    void setColor(Color);
};