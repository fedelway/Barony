#include "radialmenu.hpp"
#include "../draw.hpp"
#include "../player.hpp"
#include "../colors.hpp"
#include "interface.hpp"

SpellRadialMenu spellRadialMenu;

void SpellRadialMenu::draw() {

    if (!this->shouldDraw()) {
        return;
    }

    int menuX = omousex;
    int menuY = omousey;

    SDL_Rect src;
    src.x = xres / 2;
    src.y = yres / 2;

    int numoptions = 8;
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

    bool mouseInCenterButton = sqrt(pow((omousex - menuX), 2) + pow((omousey - menuY), 2)) < (radius - thickness);

    for ( i = 0; i < numoptions; ++i )
    {
        // see if mouse cursor is within an option.
        if ( highlight == -1 )
        {
            if ( !mouseInCenterButton )
            {
                real_t x1 = menuX + (radius + thickness + 45) * cos(angleEnd);
                real_t y1 = menuY - (radius + thickness + 45) * sin(angleEnd);
                real_t x2 = menuX + 5 * cos(angleMiddle);
                real_t y2 = menuY - 5 * sin(angleMiddle);
                real_t x3 = menuX + (radius + thickness + 45) * cos(angleStart);
                real_t y3 = menuY - (radius + thickness + 45) * sin(angleStart);
                real_t a = ((y2 - y3)*(omousex - x3) + (x3 - x2)*(omousey - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
                real_t b = ((y3 - y1)*(omousex - x3) + (x1 - x3)*(omousey - y3)) / ((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));
                real_t c = 1 - a - b;
                if ( (0 <= a && a <= 1) && (0 <= b && b <= 1) && (0 <= c && c <= 1) )
                {
                    //barycentric calc for figuring if mouse point is within triangle.
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
        drawImage(sidebar_unlock_bmp, nullptr, &img); // locked menu options

        angleStart += 2 * PI / numoptions;
        angleMiddle = angleStart + PI / numoptions;
        angleEnd = angleMiddle + PI / numoptions;
    }
    // draw center text.
    if ( mouseInCenterButton )
    {
        highlight = -1;
        drawCircle(xres / 2, yres / 2, radius - thickness, uint32ColorBaronyBlue(*mainsurface), 192);
    }
}

bool SpellRadialMenu::shouldDraw() {

    return *inputPressed(impulses[IN_FORWARD]);
    //return true;
}
