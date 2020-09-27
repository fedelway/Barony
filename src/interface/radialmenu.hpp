#pragma once

#include "../main.hpp"

struct Point {

    Point();
    Point(int x, int y);

    int x;
    int y;

    real_t getAngle();
};

class RadialMenu {

public:
    RadialMenu();
    void draw();

private:
    bool shouldDraw();
    void recordMouseCoordinates();
    void changeInventory();

    int selectedOption;
    bool isDrawing;
    Point startCoord;
};
