#include "radialmenu.hpp"
#include "../draw.hpp"
#include "../player.hpp"
#include "../colors.hpp"
#include "interface.hpp"

SpellRadialMenu spellRadialMenu;

void SpellRadialMenu::draw() {

    if (!this->shouldDraw()) {
        this->isDrawing = false;
        return;
    }

    this->recordMouseCoordinates();

    SDL_Rect src;
    src.x = xres / 2;
    src.y = yres / 2;

    int numoptions = 10;
    real_t angleStart = PI / 2 - (PI / numoptions);
    real_t angleMiddle = angleStart + PI / numoptions;
    real_t angleEnd = angleMiddle + PI / numoptions;
    int radius = 140;
    int thickness = 70;
    src.h = radius;
    src.w = radius;
    if ( yres <= 768 )
    {
        radius = 110;
        thickness = 70;
        src.h = 125;
        src.w = 125;
    }
    int highlight = -1;
    int i = 0;

    int width = 0;
    TTF_SizeUTF8(ttf12, language[3036], &width, nullptr);
    if ( yres < 768 )
    {
        ttfPrintText(ttf12, src.x - width / 2, src.y - radius - thickness - 14, language[3036]);
    }
    else
    {
        ttfPrintText(ttf12, src.x - width / 2, src.y - radius - thickness - 24, language[3036]);
    }

    drawImageRing(fancyWindow_bmp, nullptr, radius, thickness, 40, 0, PI * 2, 156);

    for ( i = 0; i < numoptions; ++i )
    {
        // draw borders around ring.
        drawLine(xres / 2 + (radius - thickness) * cos(angleStart), yres / 2 - (radius - thickness) * sin(angleStart),
            xres / 2 + (radius + thickness) * cos(angleStart), yres / 2 - (radius + thickness) * sin(angleStart), uint32ColorGray(*mainsurface), 192);
        drawLine(xres / 2 + (radius - thickness) * cos(angleEnd), yres / 2 - (radius - thickness) * sin(angleEnd),
            xres / 2 + (radius + thickness - 1) * cos(angleEnd), yres / 2 - (radius + thickness - 1) * sin(angleEnd), uint32ColorGray(*mainsurface), 192);

        drawArcInvertedY(xres / 2, yres / 2, radius - thickness, std::round((angleStart * 180) / PI), ((angleEnd * 180) / PI), uint32ColorGray(*mainsurface), 192);
        drawArcInvertedY(xres / 2, yres / 2, (radius + thickness), std::round((angleStart * 180) / PI), ((angleEnd * 180) / PI) + 1, uint32ColorGray(*mainsurface), 192);

        angleStart += 2 * PI / numoptions;
        angleMiddle = angleStart + PI / numoptions;
        angleEnd = angleMiddle + PI / numoptions;
    }

    angleStart = PI / 2 - (PI / numoptions);
    angleMiddle = angleStart + PI / numoptions;
    angleEnd = angleMiddle + PI / numoptions;

    // Determine selected options
    auto mousePosition = Point(this->startCoord.x - omousex, this->startCoord.y - omousey);
    real_t angle = mousePosition.getAngle();
    //Make the angle negative to advance clockwise
    angle -= 2*PI;
    real_t stepSize = 2*PI / numoptions;

    int selectedOption = angle/stepSize;
    //ajust option
    selectedOption = std::abs( (selectedOption*-1) + 3) % numoptions;

    for ( i = 0; i < numoptions; ++i )
    {
        // see if mouse cursor is within an option.
        if ( highlight == -1 )
        {
            if(i == selectedOption) {
                highlight = i;
                drawImageRing(fancyWindow_bmp, &src, radius, thickness, (numoptions) * 8, angleStart, angleEnd, 192);

                // draw borders around highlighted item.
                Uint32 borderColor = uint32ColorBaronyBlue(*mainsurface);
                drawLine(xres / 2 + (radius - thickness) * cos(angleStart), yres / 2 - (radius - thickness) * sin(angleStart),
                    xres / 2 + (radius + thickness) * cos(angleStart), yres / 2 - (radius + thickness) * sin(angleStart), borderColor, 192);
                drawLine(xres / 2 + (radius - thickness) * cos(angleEnd), yres / 2 - (radius - thickness) * sin(angleEnd),
                    xres / 2 + (radius + thickness - 1) * cos(angleEnd), yres / 2 - (radius + thickness - 1) * sin(angleEnd), borderColor, 192);

                drawArcInvertedY(xres / 2, yres / 2, radius - thickness, std::round((angleStart * 180) / PI), ((angleEnd * 180) / PI), borderColor, 192);
                drawArcInvertedY(xres / 2, yres / 2, (radius + thickness), std::round((angleStart * 180) / PI), ((angleEnd * 180) / PI) + 1, borderColor, 192);
            }
        }

        SDL_Rect txt;
        txt.x = src.x + src.w * cos(angleMiddle);
        txt.y = src.y - src.h * sin(angleMiddle);
        txt.w = 0;
        txt.h = 0;
        SDL_Rect img;
        img.x = txt.x - sidebar_unlock_bmp->w / 2;
        img.y = txt.y - sidebar_unlock_bmp->h / 2;
        img.w = sidebar_unlock_bmp->w;
        img.h = sidebar_unlock_bmp->h;

        // draw the text for the menu wheel.
        //drawImage(sidebar_unlock_bmp, nullptr, &img); // locked menu options

        // Write option number
        auto iStr = std::to_string(i);
        TTF_SizeUTF8(ttf12, iStr.c_str(), &width, nullptr);
        ttfPrintText(ttf12, txt.x - width / 2, txt.y - 4, iStr.c_str());

        angleStart += 2 * PI / numoptions;
        angleMiddle = angleStart + PI / numoptions;
        angleEnd = angleMiddle + PI / numoptions;
    }
}

bool SpellRadialMenu::shouldDraw() {
    return *inputPressed(impulses[IN_SPELL_WHEEL]);
}

void SpellRadialMenu::recordMouseCoordinates() {
    if(!isDrawing) {
        isDrawing = true;
        this->startCoord = Point(omousex, omousey);
    }
}

Point::Point(): x(0), y(0) { }
Point::Point(int x, int y) : x(x), y(y) { }
real_t Point::getAngle() {
    real_t angle = std::atan2(y,x);
    if(angle < 0)
       angle += 2*PI;
    return angle;
}
