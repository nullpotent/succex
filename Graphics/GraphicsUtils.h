#pragma once

#define COLOR_BLACK 0,0,0
#define COLOR_BLUE 0,0,255
#define COLOR_WHITE 255,255,255
#define COLOR_RED 255,0,0
#define COLOR_GREEN 0,255,0

template<typename T>
struct rgb_struct
{
    T r,g,b;
    template<typename B>
    rgb_struct(B rc,B gc, B bc)
    {
        r = rc;
        g = gc;
        b = bc;
    }
};
