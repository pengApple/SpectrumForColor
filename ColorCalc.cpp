#include "ColorCalc.h"

ColorCalc::ColorCalc()
{

}

ColorCalc::~ColorCalc()
{

}

double ColorCalc::ColorHLSToRGBValue(double n1, double n2, double h)
{
    double rgb = 0.;

    if (h > 360.0) {
        h -= 360.0;
    }

    if (h < 0.0) {
        h += 360.0;
    }

    if (h < 60.0) {
        rgb = n1 + (n2 - n1) * h / 60.0;
    }
    else if (h < 180.0) {
        rgb = n2;
    }
    else if (h < 240.0) {
        rgb = n1 + (n2 - n1) * (240.0 - h) / 60.0;
    }
    else {
        rgb = n1;
    }

    return rgb;
}

void ColorCalc::HLSToRGB(double h, double l, double s, double& r, double& g, double& b)
{

    double m2 = 0.;
    if (l <= 0.5) {
        m2 = l * (1.0 + s);
    }
    else {
        m2 = l + s - l * s;
    }
    double m1 =  2.0 * l - m2;
    if (s == 0.) {
        r = g = b = l;
    }
    else {
        r = ColorHLSToRGBValue(m1, m2, h + 120.0);
        g = ColorHLSToRGBValue(m1, m2, h);
        b = ColorHLSToRGBValue(m1, m2, h - 120.0);
    }
}

void ColorCalc::RGBToHLS(double r, double g, double b, double& h, double& l, double& s)
{
    double dMax = r; 
    int nMax = 0; // 0 is r, 1 is g, 2 is blue
    if (dMax < g) {
        dMax = g;
        nMax = 1;
    }

    if (dMax < b) {
        dMax = b;
        nMax = 2;
    }

    double dMin = r;
    int nMin = 0; // 0 is r, 1 is g, 2 is blue
    if (dMin > g) {
        dMin = g;
        nMin = 1;
    }

    if (dMin > b) {
        dMin = b;
        nMin = 2;
    }

    double dAdd = dMax + dMin;
    double dSub = dMax - dMin;
    l = dAdd / 2.;

    if (nMin == nMax) {
        s = 0.0f;
        h = 0.0f;
    }
    else {
        if (l <= 0.5) {
            s = dSub / dAdd;
        }
        else {
            s = dSub / (2. - dAdd);
        }
        if (nMax == 0) {
            h = (g - b) / dSub;
        }
        else if (nMax == 1) {
            h = 2. + (b - r) / dSub;
        }
        else if (nMax == 2) {
            h = 4. + (r - g) / dSub;
        }
        
        h *= 60.0f;

        if (h < 0.0) {
            h += 360.0;
        }
    }
}

ColorHLSA ColorCalc::cRGBToHLS(const ColorRGBA256& rgb)
{
    double r = (double)rgb.m_r / 255.0;
    double g = (double)rgb.m_g / 255.0;
    double b = (double)rgb.m_b / 255.0;
    ColorHLSA hls;
    hls.m_a = (double)rgb.m_a / 255.0;
    RGBToHLS(r, g, b, hls.m_h, hls.m_l, hls.m_s);
    return hls;
}

ColorRGBA256 ColorCalc::cHLSToRGB(const ColorHLSA& hls)
{
    double dr = 0.;
    double dg = 0.;
    double db = 0.;
    HLSToRGB(hls.m_h, hls.m_l, hls.m_s, dr, dg, db);

    auto getValue = [&](double c)->int {
        int cV = static_cast<int>(c * 255);
        cV = cV > 0 ? cV : 0;
        cV = cV < 255 ? cV : 255;
        return cV;
    };

    ColorRGBA256 rgb;
    rgb.m_r = getValue(dr);
    rgb.m_g = getValue(dg);
    rgb.m_b = getValue(db);
    rgb.m_a = getValue(hls.m_a);
    return rgb;
}

ColorRGBA256 ColorCalc::addRGB(const ColorRGBA256& rgb, const ColorRGBA256& rgb1)
{
    ColorRGBA256 outRgb(0, 0, 0, 0);
    outRgb.m_r = rgb.m_r + rgb1.m_r;
    outRgb.m_g = rgb.m_g + rgb1.m_g;
    outRgb.m_b = rgb.m_b + rgb1.m_b;
    outRgb.m_a = rgb.m_a + rgb1.m_a;
    return outRgb;
}

ColorRGBA256 ColorCalc::subRGB(const ColorRGBA256& rgb, const ColorRGBA256& rgb1)
{
    ColorRGBA256 outRgb(0, 0, 0, 0);
    outRgb.m_r = rgb.m_r - rgb1.m_r;
    outRgb.m_g = rgb.m_g - rgb1.m_g;
    outRgb.m_b = rgb.m_b - rgb1.m_b;
    outRgb.m_a = rgb.m_a - rgb1.m_a;
    return outRgb;
}

ColorRGBA256 ColorCalc::multipRGB(const ColorRGBA256& rgb, double v)
{
    ColorRGBA256 outRgb(0, 0, 0, 0);
    outRgb.m_r = (int)(rgb.m_r * v);
    outRgb.m_g = (int)(rgb.m_g * v);
    outRgb.m_b = (int)(rgb.m_b * v);
    outRgb.m_a = (int)(rgb.m_a * v);
    return outRgb;
}

ColorHLSA ColorCalc::addHLS(const ColorHLSA& hls, const ColorHLSA& hls1)
{
    ColorHLSA outHLS(0, 0, 0, 0);
    outHLS.m_h = hls.m_h + hls1.m_h;
    outHLS.m_l = hls.m_l + hls1.m_l;
    outHLS.m_s = hls.m_s + hls1.m_s;
    outHLS.m_a = hls.m_a + hls1.m_a;
    return outHLS;
}

ColorHLSA ColorCalc::subHLS(const ColorHLSA& hls, const ColorHLSA& hls1)
{
    ColorHLSA outHLS(0, 0, 0, 0);
    outHLS.m_h = hls.m_h - hls1.m_h;
    outHLS.m_l = hls.m_l - hls1.m_l;
    outHLS.m_s = hls.m_s - hls1.m_s;
    outHLS.m_a = hls.m_a - hls1.m_a;
    return outHLS;
}

ColorHLSA ColorCalc::multipHLS(const ColorHLSA& hls, double v)
{
    ColorHLSA outHLS(0, 0, 0, 0);
    outHLS.m_h = hls.m_h * v;
    outHLS.m_l = hls.m_l * v;
    outHLS.m_s = hls.m_s * v;
    outHLS.m_a = hls.m_a * v;
    return outHLS;
}

void ColorCalc::setRGBBeginEndColor(const ColorRGBA256& b, const ColorRGBA256& e)
{
    m_bRGBColor = true;
    m_beginRGBColor = b;
    m_endRGBColor = e;
}

void ColorCalc::setHLSABeginEndColor(const ColorHLSA& b, const ColorHLSA& e)
{
    m_bRGBColor = false;
    m_beginHLSAColor = b;
    m_endHLSAColor = e;
}

ColorRGBA256 ColorCalc::interpolateRGBColor(double fraction)
{
    if (!m_bRGBColor) {
        m_beginRGBColor = cHLSToRGB(m_beginHLSAColor);
        m_endRGBColor = cHLSToRGB(m_endHLSAColor);
        m_bRGBColor = true;
    }
    ColorRGBA256 outColor = subRGB(m_endRGBColor, m_beginRGBColor);
    outColor = multipRGB(outColor, fraction);
    outColor = addRGB(m_beginRGBColor, outColor);

    auto getColorValue = [&](int color)->int {
        color %= 256;
        color = color >= 0 ? color : 256 + color;
        return color;
    };

    outColor.m_r = getColorValue(outColor.m_r);
    outColor.m_g = getColorValue(outColor.m_g);
    outColor.m_b = getColorValue(outColor.m_b);
    outColor.m_a = outColor.m_a >= 0 ? outColor.m_a : 256 + outColor.m_a;
    return outColor;
}


ColorHLSA ColorCalc::interpolateHLSAColor(double fraction)
{
    if (m_bRGBColor) {
        m_beginHLSAColor = cRGBToHLS(m_beginRGBColor);
        m_endHLSAColor = cRGBToHLS(m_endRGBColor);
        m_bRGBColor = false;
    }

    ColorHLSA outColor = subHLS(m_endHLSAColor, m_beginHLSAColor);
    outColor = multipHLS(outColor, fraction);
    outColor = addHLS(m_beginHLSAColor, outColor);

    auto getColorValue = [&](double v)->double {
        double r = isless(v, 1.0) ? v : 1.;
        r = isgreater(r, 0.) ? r : 0.;
        return r;
    };

    outColor.m_h = isgreaterequal(outColor.m_h, 0.) ? fmod(outColor.m_h, 360.) : 360.0f - fmod((-1. * outColor.m_h), 360.0f);
    outColor.m_l = getColorValue(outColor.m_l);
    outColor.m_s = getColorValue(outColor.m_s);
    outColor.m_a = getColorValue(outColor.m_a);
    return outColor;
}

int ColorCalc::generateRGBBegEnd(int nCount, ColorRGBVector& outColors)
{
    if (nCount <= 0) {
        return 1;
    }
    if (!m_bRGBColor) {
        m_beginRGBColor = cHLSToRGB(m_beginHLSAColor);
        m_endRGBColor = cHLSToRGB(m_endHLSAColor);
        m_bRGBColor = true;
    }

    outColors.reserve(nCount + 2);
    outColors.push_back(m_beginRGBColor);
    int nNumber = nCount - 1;
    for (int i = 1; i < nNumber; i++) {
        double dFactor = double(i) / double(nCount);
        outColors.push_back(interpolateRGBColor(dFactor));
    }
    outColors.push_back(m_endRGBColor);
    return 0;
}

int ColorCalc::generateHLSABegEnd(int nCount, ColorHLSAVector& outColors)
{
    if (nCount <= 0) {
        return 1;
    }
    if (m_bRGBColor){
        m_beginHLSAColor = cRGBToHLS(m_beginRGBColor);
        m_endHLSAColor = cRGBToHLS(m_endRGBColor);
        m_bRGBColor = false;
    }

    outColors.reserve(nCount + 2);
    outColors.push_back(m_beginHLSAColor);
    int nNumber = nCount - 1;
    for (int i = 1; i < nNumber; i++) {
        double dFactor = double(i) / double(nCount);
        outColors.push_back(interpolateHLSAColor(dFactor));
    }
    outColors.push_back(m_endHLSAColor);
    return 0;
}
