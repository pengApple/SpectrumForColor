#ifndef COLORCALCULATE_DEFINATION_H
#define COLORCALCULATE_DEFINATION_H

#include "ColorType.h"

class ColorCalc
{
public:
    ColorCalc();
    ~ColorCalc();

    double ColorHLSToRGBValue(double n1, double n2, double h);
    void HLSToRGB(double h, double l, double s, double& r, double& g, double& b);
    void RGBToHLS(double r, double g, double b, double& h, double& l, double& s);

    ColorHLSA cRGBToHLS(const ColorRGBA256& rgb);
    ColorRGBA256 cHLSToRGB(const ColorHLSA& hls);

    ColorRGBA256 addRGB(const ColorRGBA256& rgb, const ColorRGBA256& rgb1);
    ColorRGBA256 subRGB(const ColorRGBA256& rgb, const ColorRGBA256& rgb1);
    ColorRGBA256 multipRGB(const ColorRGBA256& rgb, double v);

    ColorHLSA addHLS(const ColorHLSA& hls, const ColorHLSA& hls1);
    ColorHLSA subHLS(const ColorHLSA& hls, const ColorHLSA& hls1);
    ColorHLSA multipHLS(const ColorHLSA& hls, double v);

    void setRGBBeginEndColor(const ColorRGBA256& b, const ColorRGBA256& e);
    
    void setHLSABeginEndColor(const ColorHLSA& b, const ColorHLSA& e);

    ColorRGBA256 interpolateRGBColor(double fraction);
    ColorHLSA interpolateHLSAColor(double fraction);

    /*------------------------------------------------------------------------
     *
     * Method: generateRGBBegEnd
     *
     * Purpose:
     * [input] nCount the number of spectrum range.
     * [output] outColors the colors from begColor to endColor, size of this list equal (nCount)
     * For example: You want display blue to red, and split them in the 15 different colors. 
     * You should set nCount = 15
     *  outColors=[beginColor,M+1,  M+2....,M+13,endColor], size is 15
     * return 0 is success.
     *
    */
    int generateRGBBegEnd(int nCount, ColorRGBVector& outColors);

    /*------------------------------------------------------------------------
     *
     * Method: generateHLSABegEnd
     *
     * Purpose:
     * [input] nCount the number of spectrum range.
     * [output] outColors the colors from begColor to endColor, size of this list equal (nCount)
     * * For example: You want display blue to red, and split them in the 15 different colors. 
     *   You should set nCount = 15
     *  outColors=[beginColor, M+1,  M+2....,M+13,endColor], size is 15
     * return 0 is success.
     *
    */
    int generateHLSABegEnd(int nCount, ColorHLSAVector& outColors);
private:
    ColorRGBA256 m_beginRGBColor = g_Blue;
    ColorRGBA256 m_endRGBColor = g_Red;
    ColorHLSA m_beginHLSAColor;
    ColorHLSA m_endHLSAColor;
    bool m_bRGBColor = true;
};

#endif
