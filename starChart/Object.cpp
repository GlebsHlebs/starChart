#include "Object.h"

Object::Object() {
	coords = {0.0, 0.0, 0.0};
	color = { 0, 0, 0, 255 };
}
Object::Object(Coordinates coords, Color color) : coords(coords), color(color) {}

Coordinates Object::getCoordinates() const { return coords; }
Color Object::getColor() const { return color; }

void Object::getCoordinates(Coordinates coords) { this->coords = coords; }
void Object::setColor(Color color) { this->color = color; }