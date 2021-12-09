#include "ColorSegment.h"

#define DEBUG

#ifdef DEBUG
#include<iostream>
#include <fstream>
#endif


ColorSegment::ColorSegment()
{
    m_metaRange.bColor = g_Blue;
    m_metaRange.eColor = g_Red;
    m_metaRange.mColor = g_Green;
    ColorCalc colorCalc;
    m_metaHLSRange.bColor = colorCalc.cRGBToHLS(g_Blue);
    m_metaHLSRange.eColor = colorCalc.cRGBToHLS(g_Red);
    m_metaHLSRange.mColor = colorCalc.cRGBToHLS(g_Green);
}

ColorSegment::~ColorSegment()
{

}

void ColorSegment::setMetaRange(const RGBColorSegment& metaR)
{
    m_metaRange = metaR;
}

RGBColorSegment ColorSegment::getMetaRange()
{
    return m_metaRange;
}


void ColorSegment::setHLSMetaRange(const HLSColorSegment& hls)
{
    m_metaHLSRange = hls;
}

HLSColorSegment ColorSegment::getHLSMetaRange()
{
    return m_metaHLSRange;
}


int ColorSegment::generateRGBRanges(int nCount, RGBColorRangeVector& outColorRanges)
{
    if (nCount <= 2) {
        return 1;
    }
    // From begin color to midColor.
    ColorCalc colorFirstHalf;
    colorFirstHalf.setRGBBeginEndColor(m_metaRange.bColor, m_metaRange.mColor);
    int nHalf = nCount / 2;
    
    // From mid color to end color.
    ColorCalc colorLastHalf;
    colorLastHalf.setRGBBeginEndColor(m_metaRange.mColor, m_metaRange.eColor);
    
    ColorCalc colorCalcMid;

    outColorRanges.resize(nCount);
    auto addColorSegment = [&](int index, const ColorRGBA256& b, const ColorRGBA256& e)mutable->void{
        RGBColorSegment rTemp;
        rTemp.bColor = b;
        rTemp.eColor = e;
        colorCalcMid.setRGBBeginEndColor(b, e);
        rTemp.mColor = colorCalcMid.interpolateRGBColor(0.5);
        outColorRanges[index] = rTemp;
    };

    double dMax = (double)(nHalf + 2.);
    int nBigIndex = nCount - 1;
    // Add first half segments.
    for (size_t i = 0, length = nHalf; i < length; i++) {
        double dFirtHalfT = double(i + 1.) / dMax;
        double dLastHalfT = 1. - dFirtHalfT;
        if (i == 0) {
            addColorSegment(i, m_metaRange.bColor, colorFirstHalf.interpolateRGBColor(dFirtHalfT));
            addColorSegment(nBigIndex - i, colorLastHalf.interpolateRGBColor(dLastHalfT), m_metaRange.eColor);
        }
        else {
            addColorSegment(i, outColorRanges[i - 1].eColor, colorFirstHalf.interpolateRGBColor(dFirtHalfT));
            addColorSegment(nBigIndex - i, colorLastHalf.interpolateRGBColor(dLastHalfT), outColorRanges[nBigIndex - i + 1].bColor);
        }
    }
    int nM = nCount % 2;
    if (nM == 1) {
        // Add mid segment.
        addColorSegment(nHalf, outColorRanges[nHalf - 1].eColor, outColorRanges[nHalf + 1].bColor);
    }
    
#ifdef DEBUG
    std::fstream fHandle;
    fHandle.open("D:\\test\\SpectrumLog.txt", std::ios::app);
    fHandle << "ColorSegment::generateRGBRanges results \n";
    for (size_t i = 0, length = outColorRanges.size(); i < length; i++) {
        fHandle << "RangeIndex: " << i << " \n";
        fHandle << "\t BeginColor: (" << outColorRanges[i].bColor.m_r << ", " << outColorRanges[i].bColor.m_g << ", " << outColorRanges[i].bColor.m_b << ") \n";
        fHandle << "\t MidColor: (" << outColorRanges[i].mColor.m_r << ", " << outColorRanges[i].mColor.m_g << ", " << outColorRanges[i].mColor.m_b << ") \n";
        fHandle << "\t EndColor: (" << outColorRanges[i].eColor.m_r << ", " << outColorRanges[i].eColor.m_g << ", " << outColorRanges[i].eColor.m_b << ") \n";
    }
    fHandle << "End ColorSegment::generateRGBRanges results \n";
    fHandle.close();
#endif // DEBUG

    return 0;
}

int ColorSegment::generateHLSRanges(int nCount, HLSColorRangeVector& outColorRanges)
{
    if (nCount <= 2) {
        return 1;
    }

    // From begin color to midColor.
    ColorCalc colorFirstHalf;
    colorFirstHalf.setHLSABeginEndColor(m_metaHLSRange.bColor, m_metaHLSRange.mColor);
    int nHalf = nCount / 2;

    // From mid color to end color.
    ColorCalc colorLastHalf;
    colorLastHalf.setHLSABeginEndColor(m_metaHLSRange.mColor, m_metaHLSRange.eColor);

    ColorCalc colorCalcMid;

    outColorRanges.resize(nCount);
    auto addColorSegment = [&](int index, const ColorHLSA& b, const ColorHLSA& e)mutable->void {
        HLSColorSegment rTemp;
        rTemp.bColor = b;
        rTemp.eColor = e;
        colorCalcMid.setHLSABeginEndColor(b, e);
        rTemp.mColor = colorCalcMid.interpolateHLSAColor(0.5);
        outColorRanges[index] = rTemp;
    };

    double dMax = (double)(nHalf + 2.);
    int nBigIndex = nCount - 1;
    // Add first half segments.
    for (size_t i = 0, length = nHalf; i < length; i++) {
        double dFirtHalfT = double(i + 1.) / dMax;
        double dLastHalfT = 1. - dFirtHalfT;
        if (i == 0) {
            addColorSegment(i, m_metaHLSRange.bColor, colorFirstHalf.interpolateHLSAColor(dFirtHalfT));
            addColorSegment(nBigIndex - i, colorLastHalf.interpolateHLSAColor(dLastHalfT), m_metaHLSRange.eColor);
        }
        else {
            addColorSegment(i, outColorRanges[i - 1].eColor, colorFirstHalf.interpolateHLSAColor(dFirtHalfT));
            addColorSegment(nBigIndex - i, colorLastHalf.interpolateHLSAColor(dLastHalfT), outColorRanges[nBigIndex - i + 1].bColor);
        }
    }
    int nM = nCount % 2;
    if (nM == 1) {
        // Add mid segment.
        addColorSegment(nHalf, outColorRanges[nHalf - 1].eColor, outColorRanges[nHalf + 1].bColor);
    }

#ifdef DEBUG
    std::fstream fHandle;
    fHandle.open("D:\\test\\SpectrumLog.txt", std::ios::app);
    fHandle << "ColorSegment::generateHLSRanges results \n";
    for (size_t i = 0, length = outColorRanges.size(); i < length; i++) {
        fHandle << "RangeIndex: " << i << " \n";
        fHandle << "\t BeginColor: (" << outColorRanges[i].bColor.m_h << ", " << outColorRanges[i].bColor.m_l << ", " << outColorRanges[i].bColor.m_s << ") \n";
        fHandle << "\t MidColor: (" << outColorRanges[i].mColor.m_h << ", " << outColorRanges[i].mColor.m_l << ", " << outColorRanges[i].mColor.m_s << ") \n";
        fHandle << "\t EndColor: (" << outColorRanges[i].eColor.m_h << ", " << outColorRanges[i].eColor.m_l << ", " << outColorRanges[i].eColor.m_s << ") \n";
    }
    fHandle << "End ColorSegment::generateHLSRanges results \n";
    fHandle.close();
#endif // DEBUG

    return 0;
}
