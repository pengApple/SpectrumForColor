#ifndef COLORSEGMENT_DEFINATION_H
#define COLORSEGMENT_DEFINATION_H

#include"ColorCalc.h"

struct RGBColorSegment
{
    ColorRGBA256 bColor = g_Black;// Begin color.
    ColorRGBA256 mColor = g_Black;// mid color.
    ColorRGBA256 eColor = g_Black;// End color.
};

typedef std::vector<RGBColorSegment> RGBColorRangeVector;

struct HLSColorSegment
{
    ColorHLSA bColor;// Begin color.
    ColorHLSA mColor;// mid color.
    ColorHLSA eColor;// End color.
};

typedef std::vector<HLSColorSegment> HLSColorRangeVector;

class ColorSegment
{
public:
    ColorSegment();
    ~ColorSegment();

    void setMetaRange(const RGBColorSegment& rgb);
    RGBColorSegment getMetaRange();

    void setHLSMetaRange(const HLSColorSegment& hls);
    HLSColorSegment getHLSMetaRange();

    /*------------------------------------------------------------------------
     *
     * Method: generateRGBRanges
     *
     * Purpose:
     * [input] nCount the number of spectrum range.
     * [output] outColorRanges the colors from m_metaRange.bColor to m_metaRange.eColor, size of this list equal (nCount)
     *    The value from m_metaRange.bValue to m_metaRange.eValue
     * For example: You want display blue to red, and split them in the 15 different colors.
     * You should set nCount = 15
     *  outColors=[(beginColor,M+1),(M+1,M+2)...,(M+14,endColor)], size is 15
     * return 0 is success.
     *
    */
    int generateRGBRanges(int nCount, RGBColorRangeVector& outColorRanges);


    /*------------------------------------------------------------------------
     *
     * Method: generateHLSRanges
     *
     * Purpose:
     * [input] nCount the number of spectrum range.
     * [output] outColorRanges the colors from m_metaHLSRange.bColor to m_metaHLSRange.eColor, size of this list equal (nCount)
     *  The value from m_metaHLSRange.bValue to m_metaHLSRange.eValue
     * For example: You want display blue to red, and split them in the 15 different colors.
     * You should set nCount = 15
     *  outColors=[(beginColor,M+1),(M+1,M+2)...,(M+14,endColor)], size is 15
     * return 0 is success.
     *
    */
    int generateHLSRanges(int nCount, HLSColorRangeVector& outColorRanges);

    /*------------------------------------------------------------------------
     *
     * Method: generateValueRGBColor
     *
     * Purpose:
     * [input] inputValue input value that you want to convert RGB color base on metaRange
     * [output] rgb The color matach with your input value, if value less than metaRange.bValue, return below color.
     *  if value greater than metaRange.eValue, return Above color.
     *  if value is Null or in outOfRange, return Outof color.
     * return 0 is success.
     *
    */
    //int generateValueRGBColor(double inputValue, ColorRGBA256& rgb);

    /*------------------------------------------------------------------------
     *
     * Method: generateValueHLSColor
     *
     * Purpose:
     * [input] inputValue input value that you want to convert RGB color base on metaRange
     * [output] hls The color matach with your input value, if value less than metaRange.bValue, return below color.
     *  if value greater than metaRange.eValue, return Above color.
     *  if value is Null or in outOfRange, return Outof color.
     * return 0 is success.
     *
    */
    //int generateValueHLSColor(double inputValue, ColorHLSA& hls);

private:
    RGBColorSegment m_metaRange;
    HLSColorSegment m_metaHLSRange;
};

#endif
