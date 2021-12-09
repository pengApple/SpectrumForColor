#ifndef COLORRANGEMAPPING_DEFINATION_H
#define COLORRANGEMAPPING_DEFINATION_H

#include"ColorSegment.h"

struct DataRGBMappingObj {
    double dStartFactor = 0.;
    double dEndFactor = 1.;
    double dStart = 0.;
    double dEnd = 1.;
    RGBColorSegment colorRange;
};

typedef std::vector<DataRGBMappingObj> DataRGBMappingVector;

struct DataHLSMappingObj {
    double dStartFactor = 0.;
    double dEndFactor = 1.;
    double dStart = 0.;
    double dEnd = 1.;
    HLSColorSegment colorRange;
};

typedef std::vector<DataHLSMappingObj> DataHLSMappingVector;

typedef std::vector<double> valueRangeVector;


class ColorRangeMapping
{
public:
    ColorRangeMapping();
    ~ColorRangeMapping();


    /*------------------------------------------------------------------------
     *
     * Method: setBelowAboveOutOfThreshold
     *
     * Purpose:
     * [input] dThreshold This is a scale value [0,0.5), all valid values should has color.
     * For example: All the color calculated in the range (0,1)
     *    The color scale should be splite to [0, outof),[outof, below)[below, end)[Above, 1)
     * The default value dThreshold = 0.05,  This means: dBelow = 0.10, Above = 0.95, dOutOf=0.05
     *  If you want to remove below/above and outOf, plese set 0.0
     * If your set value greater than 0.5 or less than 0, this function does not anything.
     *
    */
    void setBelowAboveOutOfThreshold(double dThreshold);

    /*------------------------------------------------------------------------
     *
     * Method: setMaxMin
     *
     * Purpose:
     * [input] dMax Max value of valid value.
     * [input] dMin Min value of valid value.
     *
    */
    void setMaxMin(double dMax, double dMin);
    void getMaxMin(double& dMax, double& dMin);

    /*------------------------------------------------------------------------
     *
     * Method: setMaxMin
     *
     * Purpose:
     * [input] dOutof You can specify a color for data less than this value.
     *
    */
    void setOutof(double dOutof);
    double setOutof();

    void setStartColor(const ColorRGBA256& rgb);
    ColorRGBA256 getStartColor();
    void setEndColor(const ColorRGBA256& rgb);
    ColorRGBA256 getEndColor();
    void setStartMidColor(const ColorRGBA256& rgb);
    ColorRGBA256 getStartMidColor();

    void setBelowColor(const ColorRGBA256& rgb);
    ColorRGBA256 getBelowColor();

    void setAboveColor(const ColorRGBA256& rgb);
    ColorRGBA256 getAboveColor();

    void setOutofColor(const ColorRGBA256& rgb);
    ColorRGBA256 getOutofColor();

    /*------------------------------------------------------------------------
     *
     * Method: calculatRGBRange
     *
     * Purpose:
     * [input] nCount The number of color ranges.
     * [output] rgbRange Color ranges..
     * For example: you want to get 2 ranges. You set nCount = 1
     *    The range list is shown: [0, outof),[outof, dMin)[dMin, newData),[newData, dMax)[dMax, 1)
     *  1. {
     *     double dStartFactor = 0.;
     *     double dEndFactor = dThreshold = 0.05;
     *     colorRange.bColor = OutofColor;
     *     colorRange.eColor = belowColor;
     *    };
     * *  2. {
     *     double dStartFactor = 0.05;
     *     double dEndFactor = 0.1;
     *     colorRange.bColor = belowColor;
     *     colorRange.eColor = bStartColor;
     *     colorRange.bValue = 0.;
     *     colorRange.eValue = dMin;
     *    };
     *  3. {
     *     double dStartFactor = 0.1;
     *     double dEndFactor = 0.45;
     *     colorRange.bColor = bStartColor;
     *     colorRange.eColor = newColor1;
     *     colorRange.bValue = dMin;
     *     colorRange.eValue = newData;
     *    };
     * 4. {
     *     double dStartFactor = 0.45;
     *     double dEndFactor = 0.95;
     *     colorRange.bColor = newColor1;
     *     colorRange.eColor = bEndColor;
     *     colorRange.bValue = newData;
     *     colorRange.eValue = dMax;
     *    };
     * 5. {
     *     double dStartFactor = 0.95;
     *     double dEndFactor = 1.;
     *     colorRange.bColor = bEndColor;
     *     colorRange.eColor = aboveColor;
     *     colorRange.bValue = dMax;
     *     colorRange.eValue = NAN;
     *    };
     * return 0 is success.
    */
    int calculatRGBRange(int nCount, DataRGBMappingVector& rgbRange);


    /*------------------------------------------------------------------------
     *
     * Method: calculatHLSRange
     *
     * Purpose:
     * [input] nCount The number of color ranges.
     * [output] hlsRange Color ranges..
     * For example: you want to get 2 ranges. You set nCount = 1
     *    The range list is shown: [0, outof),[outof, dMin)[dMin, newData),[newData, dMax)[dMax, 1)
     *  1. {
     *     double dStartFactor = 0.;
     *     double dEndFactor = dThreshold = 0.05;
     *     colorRange.bColor = OutofColor;
     *     colorRange.eColor = belowColor;
     *    };
     * *  2. {
     *     double dStartFactor = 0.05;
     *     double dEndFactor = 0.1;
     *     colorRange.bColor = belowColor;
     *     colorRange.eColor = bStartColor;
     *     colorRange.bValue = 0.;
     *     colorRange.eValue = dMin;
     *    };
     *  3. {
     *     double dStartFactor = 0.1;
     *     double dEndFactor = 0.45;
     *     colorRange.bColor = bStartColor;
     *     colorRange.eColor = newColor1;
     *     colorRange.bValue = dMin;
     *     colorRange.eValue = newData;
     *    };
     * 4. {
     *     double dStartFactor = 0.45;
     *     double dEndFactor = 0.95;
     *     colorRange.bColor = newColor1;
     *     colorRange.eColor = bEndColor;
     *     colorRange.bValue = newData;
     *     colorRange.eValue = dMax;
     *    };
     * 5. {
     *     double dStartFactor = 0.95;
     *     double dEndFactor = 1.;
     *     colorRange.bColor = bEndColor;
     *     colorRange.eColor = aboveColor;
     *     colorRange.bValue = dMax;
     *     colorRange.eValue = NAN;
     *    };
     * return 0 is success.
    */
    int calculatHLSRange(int nCount, DataHLSMappingVector& hlsRange);


    /*------------------------------------------------------------------------
     *
     * Method: calculatRGBRange
     *
     * Purpose:
     * [input] nCount The number of color ranges.
     * [output] rgbRange Color ranges..
     * This method call calculatHLSRange to create ranges, and coverts all color to RGB.
     * return 0 is success.
    */
    int calculatRange(int nCount, DataRGBMappingVector& rgbRange);

    /*------------------------------------------------------------------------
     *
     * Method: generateValueRanges
     *
     * Purpose:
     * [input] nCount the number of spectrum range.
     * [input] beginValue the start value.
     * [input] endValue the end value.
     * [output] outRanges the value between beginValue and endValue, [beginValue, ...endValue].
     * You should set nCount = 15
     *  outColors=[beginValue, ...endValue], size is 15
     * return 0 is success.
     *
    */
    int generateValueRanges(int nCount, valueRangeVector& outRanges);



    /*------------------------------------------------------------------------
     *
     * Method: calculatHLSRange
     *
     * Purpose:
     * [input] dValue The value you want to draw color. This input value base on Max/Min
     * [output] dOutValue The scale value in [0, 1) ranges..
     * return 0 is success.
    */
    int calculatValueInRange(double dValue, double& dOutValue);

    int calculatRangeScales(int nCount, valueRangeVector& scaleValueVector);

private:
    ColorSegment* m_pColorSegment = nullptr;
    double m_dMax = 0.90;
    double m_dMin = 0.1;
    bool m_bSetOutof = false;
    double m_dOutOf = FP_NAN;
    double m_dThreshold = 0.05;
    ColorRGBA256 m_BelowColor = g_Magenta;
    ColorRGBA256 m_AboveColor = g_White;
    ColorRGBA256 m_OutofColor = g_Gray;
    ColorRGBA256 m_StartColor = g_Blue;
    ColorRGBA256 m_StartMidColor = g_Green;
    ColorRGBA256 m_EndColor = g_Red;
};


#endif

