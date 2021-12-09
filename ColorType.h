#ifndef COLORTYPES_NAME_H
#define COLORTYPES_NAME_H

// The *Arith classes defined below are not intended for public use,
// but are only needed for color interpolation in the spectrum classes.
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

typedef struct packedColor {
    __int8 r = 0;
    __int8 g = 0;
    __int8 b = 0;
    __int8 a = 0;

    packedColor(__int8 a, __int8 b, __int8 c, __int8 d)
    {
        r = a;
        g = b;
        b = c;
        a = d;
    }
} PackedColor;

struct ColorRGBA256 {
    int m_r = 0;
    int m_g = 0;
    int m_b = 0;
    int m_a = 0;

    ColorRGBA256() {}

    ColorRGBA256(int a, int b, int c, int d)
    {
        m_r = a;
        m_g = b;
        m_b = c;
        m_a = d;
    }
};

typedef std::vector<ColorRGBA256> ColorRGBVector;

//  HLSA (hue, lightness, saturation, alpha)
struct ColorHLSA {
    double m_h = 0.;
    double m_l = 0.5;
    double m_s = 1.;
    double m_a = 0.;

    ColorHLSA() {}

    ColorHLSA(double a, double b, double c, double d)
    {
        m_h = a;
        m_l = b;
        m_s = c;
        m_a = d;
    }
};

typedef std::vector<ColorHLSA> ColorHLSAVector;



//  Initialize static constant colors:
const ColorRGBA256 g_Red(255, 0, 0, 0);
const ColorRGBA256 g_Yellow(255, 255, 0, 0);
const ColorRGBA256 g_Green(0,  255, 0, 0);
const ColorRGBA256 g_Cyan(0, 255, 255, 0);
const ColorRGBA256 g_Blue(0, 0, 255, 0);
const ColorRGBA256 g_Magenta(255, 0, 255, 0);
const ColorRGBA256 g_White(255, 255, 255, 0);
const ColorRGBA256 g_Black(0, 0, 0, 0);
const ColorRGBA256 g_Gray(127, 127, 127, 0);

#endif

