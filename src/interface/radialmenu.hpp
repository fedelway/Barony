#pragma once

#include "../main.hpp"

struct Point {

    Point();
    Point(int x, int y);

    int x;
    int y;

    real_t getAngle();
};

class SpellRadialMenu {

public:
    void draw();

private:
    bool shouldDraw();
    void recordMouseCoordinates();

    bool isDrawing;
    Point startCoord;
};
