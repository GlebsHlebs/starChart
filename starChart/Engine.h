#pragma once

#include <vector>
#include "Cooridnates.h"
#include "Color.h"
#include "Sphere.h"

using namespace std;

class Engine {
private:
	int canvas_width;
	int canvas_height;
	int viewPort_width = 100;
	int viewPort_height = 100;
	static Color BACKGROUND_COLOR;
public:
	Engine();
	Engine(int, int);

	bool canvasToViewPort(double, double, vector<double>*);
	Color traceRay(Coordinates, vector<double>, double, double, vector<Sphere>);
	bool intersectRaySphere(Coordinates, vector<double>, Sphere, double*, double*);
	vector<double> subtractVectors(Coordinates, Coordinates);

	int getCanvasWidth() const;
	int getCanvasHeight() const;
	int getViewPortWidth() const;
	int getViewPortHeight() const;

	void setCanvasWidth(int canvas_width);
	void setCanvasHeight(int canvas_height);
};