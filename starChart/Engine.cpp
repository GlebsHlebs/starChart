#include <vector>
#include "Color.h"
#include "Engine.h"

using namespace std;

template<class InputIt1, class InputIt2, class T>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init)
{
	while (first1 != last1)
	{
		init = std::move(init) + (*first1) * (*first2);
		++first1;
		++first2;
	}

	return init;
}

Color Engine::BACKGROUND_COLOR = { 0, 0, 0, 255 };

Engine::Engine() : canvas_width(640), canvas_height(480) {}
Engine::Engine(int canvas_width, int canvas_height) : canvas_width(canvas_width), canvas_height(canvas_height) {}

vector<double> Engine::subtractVectors(Coordinates first_point, Coordinates second_point) {
	vector<double> vector;
	vector.push_back( second_point.x - first_point.x );
	vector.push_back( second_point.y - first_point.y );
	vector.push_back( second_point.z - first_point.z );
	return vector;
}

bool Engine::canvasToViewPort(double x, double y, vector<double>* ray) {
	ray->push_back(x * static_cast<double>(viewPort_width) / static_cast<double>(canvas_width));
	ray->push_back(y * static_cast<double>(viewPort_height) / static_cast<double>(canvas_height));
	ray->push_back(1.0);
	return true;
}

bool Engine::intersectRaySphere(Coordinates point, vector<double> ray, Sphere sphere, double* t1, double* t2) {
	double radius = sphere.getRadius();
	vector<double> sphere_to_source = subtractVectors(point, sphere.getCoordinates());

	double a = inner_product(begin(ray), end(ray), begin(ray), 0.0);
	double b = 2 * inner_product(begin(sphere_to_source), end(sphere_to_source), begin(ray), 0.0);
	double c = inner_product(begin(sphere_to_source), end(sphere_to_source), begin(sphere_to_source), 0.0) - radius * radius;

	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0.0) {
		*t1 = 999999.0;
		*t2 = 999999.0;
		return false;
	}

	*t1 = (-b + sqrt(discriminant)) / (2 * a);
	*t2 = (-b - sqrt(discriminant)) / (2 * a);
	return true;
}


Color Engine::traceRay(Coordinates point, vector<double> ray, double t_min, double t_max, vector<Sphere> spheres) {
	double closest_t = 999999.0;
	Sphere closest_sphere;
	Sphere* Pclosest_sphere = &closest_sphere;
	Pclosest_sphere = NULL;

	for (Sphere sphere : spheres) {
		double t1;
		double t2;
		intersectRaySphere(point, ray, sphere, &t1, &t2);

		if (t1 >= t_min && t2 <= t_max) {
			closest_t = t2;
			Pclosest_sphere = &sphere;
		}
	}

	if (Pclosest_sphere == NULL) {
		return BACKGROUND_COLOR;
	}
	return Pclosest_sphere->getColor();
}

int Engine::getCanvasWidth() const { return canvas_width; }
int Engine::getCanvasHeight() const { return canvas_height; }
int Engine::getViewPortWidth() const { return viewPort_width; }
int Engine::getViewPortHeight() const { return viewPort_height; }

void Engine::setCanvasWidth(int canvas_width) { this->canvas_width = canvas_width; }
void Engine::setCanvasHeight(int canvas_height) { this->canvas_height = canvas_height; }