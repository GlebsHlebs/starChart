#include <iostream>
#include <SDL.h>
#include <vector>
#include "Color.h"
#include "Cooridnates.h"
#include "Engine.h"
#include "Sphere.h"

using namespace std;

#define WHITE {255, 255, 255, 255}

int main(int argc, char* argv[]) {

    int window_width = 640;
    int window_height = 480;

    SDL_Window* window; // Declare a pointer to an SDL_Window

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);

    // Check if the window was created successfully
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Engine e(window_width / 2, window_height / 2);
    Coordinates camera = {0.0, 0.0, 0.0};
    Sphere S1({ 0.0, -1.0, 3.0 }, WHITE, 1.0);
    Sphere S2({ 2.0, 0.0, 4.0 }, WHITE, 1.0);
    Sphere S3({ -2.0, 0.0, 4.0 }, WHITE, 1.0);
    Sphere S4({ 3.0, 5.0, 7.0 }, WHITE, 1.0);
    Sphere S5({ -1.0, 10.0, 5.0 }, WHITE, 1.0);

    vector<Sphere> spheres;
    spheres.push_back(S1);
    spheres.push_back(S2);
    spheres.push_back(S3);
    spheres.push_back(S4);
    spheres.push_back(S5);

    for (int x = -e.getCanvasWidth(); x <= e.getCanvasWidth(); x++) {
        for (int y = -e.getCanvasHeight(); y <= e.getCanvasHeight(); y++) {
            vector<double> ray;
            e.canvasToViewPort(static_cast<double>(x), static_cast<double>(y), &ray);
            Color color = e.traceRay(camera, ray, 1.0, 999999.0, spheres);
            SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);
            SDL_RenderDrawPoint(renderer, e.getCanvasWidth() + x, e.getCanvasHeight() - y);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
    }

    // Destroy the window and quit SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}