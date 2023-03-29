#include "Color.h"
#include "Sphere.h"

Sphere::Sphere() : Object(), radius(0.0) {}
Sphere::Sphere(Coordinates coords, Color color, double radius) : Object(coords, color), radius(radius) {}

double Sphere::getRadius() const { return radius; }

void Sphere::setRadius(double radius) { this->radius = radius; }