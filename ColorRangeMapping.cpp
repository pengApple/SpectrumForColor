#include "ColorRangeMapping.h"

#define DEBUG

#ifdef DEBUG
#include<iostream>
#include <fstream>
#endif

ColorRangeMapping::ColorRangeMapping()
{

}

ColorRangeMapping::~ColorRangeMapping()
{
    if (m_pColorSegment != nullptr) {
        delete m_pColorSegment;
        m_pColorSegment = nullptr;
    }
}

void ColorRangeMapping::setBelowAboveOutOfThreshold(double dThreshold)
{
    if (isless(dThreshold, 0) || isgreater(dThreshold, 0.3)) {
        return;
    }
    m_dThreshold = dThreshold;
}

void ColorRangeMapping::setMaxMin(double dMax, double dMin)
{
    m_dMax = dMax;
    m_dMin = dMin;
}

void ColorRangeMapping::getMaxMin(double& dMax, double& dMin)
{
    dMax = m_dMax;
    dMin = m_dMin;
}

void ColorRangeMapping::setOutof(double dOutof)
{
    m_dOutOf = dOutof;
    m_bSetOutof = true;
}

double ColorRangeMapping::setOutof()
{
    return m_dOutOf;
}

void ColorRangeMapping::setStartColor(const ColorRGBA256& rgb)
{
    m_StartColor = rgb;
}

ColorRGBA256 ColorRangeMapping::getStartColor()
{
    return m_StartColor;
}

void ColorRangeMapping::setEndColor(const ColorRGBA256& rgb)
{
    m_EndColor = rgb;
}

ColorRGBA256 ColorRangeMapping::getEndColor()
{
    return m_EndColor;
}

void ColorRangeMapping::setStartMidColor(const ColorRGBA256& rgb)
{
    m_StartMidColor = rgb;
}

ColorRGBA256 ColorRangeMapping::getStartMidColor()
{
    return m_StartMidColor;
}

void ColorRangeMapping::setBelowColor(const ColorRGBA256& rgb)
{
    m_BelowColor = rgb;
}

ColorRGBA256 ColorRangeMapping::getBelowColor()
{
    return m_BelowColor;
}

void ColorRangeMapping::setAboveColor(const ColorRGBA256& rgb)
{
    m_AboveColor = rgb;
}

ColorRGBA256 ColorRangeMapping::getAboveColor()
{
    return m_AboveColor;
}

void ColorRangeMapping::setOutofColor(const ColorRGBA256& rgb)
{
    m_OutofColor = rgb;
}
ColorRGBA256 ColorRangeMapping::getOutofColor()
{
    return m_OutofColor;
}


int ColorRangeMapping::calculatRGBRange(int nCount, DataRGBMappingVector& rgbRange)
{
    if (nCount <= 1) {
        return 1;
    }
    if (m_pColorSegment == nullptr) {
        m_pColorSegment = new ColorSegment();
    }
    if (m_pColorSegment == nullptr) {
        return 2;
    }

    RGBColorSegment metaR;
    metaR.bColor = m_StartColor;
    metaR.eColor = m_EndColor;
    metaR.mColor = m_StartMidColor;
    m_pColorSegment->setMetaRange(metaR);

    RGBColorRangeVector outRangeSeq;
    int nRet = m_pColorSegment->generateRGBRanges(nCount, outRangeSeq);
    if (nRet != 0) {
        return nRet;
    }
    if (outRangeSeq.size() != nCount) {
        return nRet;
    }
    int nValueCount = nCount + 1;
    valueRangeVector scaleValueVector;
    nRet = calculatRangeScales(nValueCount, scaleValueVector);
    if (nRet != 0) {
        return nRet;
    }
    if (scaleValueVector.size() != nValueCount) {
        return nRet;
    }
    valueRangeVector outValues;
    nRet = generateValueRanges(nValueCount, outValues);
    if (nRet != 0) {
        return nRet;
    }
    if (outValues.size() != nValueCount) {
        return nRet;
    }

    rgbRange.reserve(nCount + 3);
    for (int i = 0; i < nCount; i++) {
        DataRGBMappingObj obj;
        obj.dStartFactor = scaleValueVector[i];
        obj.dEndFactor = scaleValueVector[i + 1];
        obj.dStart = outValues[i];
        obj.dEnd = outValues[i + 1];
        obj.colorRange = outRangeSeq[i];
        rgbRange.emplace_back(obj);
    }

#ifdef DEBUG
    std::fstream fHandle;
    fHandle.open("D:\\test\\SpectrumLog.txt", std::ios::app);
    fHandle << "ColorRangeMapping::calculatRGBRange value mapping to colorSequence \n";
    for (int i = 0; i < nCount; i++) {
        fHandle << "RangeIndex: " << i << "\n";
        fHandle << "\t Start factor: " << rgbRange[i].dStartFactor << "\n";
        fHandle << "\t Start Value: " << rgbRange[i].dStart << "\n";
        fHandle << "\t Start Color: " << "RGB(" << rgbRange[i].colorRange.bColor.m_r << ", " << rgbRange[i].colorRange.bColor.m_g << ", " << rgbRange[i].colorRange.bColor.m_b <<")\n";
        fHandle << "\t End factor: " << rgbRange[i].dEndFactor << "\n";
        fHandle << "\t End Value: " << rgbRange[i].dEnd << "\n";
        fHandle << "\t Start Color: " << "RGB(" << rgbRange[i].colorRange.eColor.m_r << ", " << rgbRange[i].colorRange.eColor.m_g << ", " << rgbRange[i].colorRange.eColor.m_b << ")\n";
        fHandle << "\t Mid Color: " << "RGB(" << rgbRange[i].colorRange.mColor.m_r << ", " << rgbRange[i].colorRange.mColor.m_g << ", " << rgbRange[i].colorRange.mColor.m_b << ")\n";
    }
    fHandle << "End value mapping to colorSequence \n";
    fHandle.close();
#endif // DEBUG

    return 0;
}

int ColorRangeMapping::calculatHLSRange(int nCount, DataHLSMappingVector& hlsRange)
{
    if (nCount <= 1) {
        return 1;
    }
    if (m_pColorSegment == nullptr) {
        m_pColorSegment = new ColorSegment();
    }
    if (m_pColorSegment == nullptr) {
        return 2;
    }

    ColorCalc calcColor = ColorCalc();
    HLSColorSegment metaR;
    metaR.bColor = calcColor.cRGBToHLS(m_StartColor);
    metaR.eColor = calcColor.cRGBToHLS(m_EndColor);
    metaR.mColor = calcColor.cRGBToHLS(m_StartMidColor);
    m_pColorSegment->setHLSMetaRange(metaR);

    HLSColorRangeVector outRangeSeq;
    int nRet = m_pColorSegment->generateHLSRanges(nCount, outRangeSeq);
    if (nRet != 0) {
        return nRet;
    }
    if (outRangeSeq.size() != nCount) {
        return nRet;
    }
    int nValueCount = nCount + 1;
    valueRangeVector scaleValueVector;
    nRet = calculatRangeScales(nValueCount, scaleValueVector);
    if (nRet != 0) {
        return nRet;
    }
    if (scaleValueVector.size() != nValueCount) {
        return nRet;
    }
    valueRangeVector outValues;
    nRet = generateValueRanges(nValueCount, outValues);
    if (nRet != 0) {
        return nRet;
    }
    if (outValues.size() != nValueCount) {
        return nRet;
    }

    hlsRange.reserve(nCount + 3);

    int nNum = nCount - 1;
    for (int i = 0; i < nCount; i++) {
        DataHLSMappingObj obj;
        obj.dStartFactor = scaleValueVector[i];
        obj.dEndFactor = scaleValueVector[i + 1];
        obj.dStart = outValues[i];
        obj.dEnd = outValues[i + 1];
        obj.colorRange = outRangeSeq[i];
        hlsRange.emplace_back(obj);
    }

#ifdef DEBUG
    std::fstream fHandle;
    fHandle.open("D:\\test\\SpectrumLog.txt", std::ios::app);
    fHandle << "ColorRangeMapping::calculatRange value mapping to colorSequence \n";
    for (int i = 0; i < nCount; i++) {
        fHandle << "RangeIndex: " << i << "\n";
        fHandle << "\t Start factor: " << hlsRange[i].dStartFactor << "\n";
        fHandle << "\t Start Value: " << hlsRange[i].dStart << "\n";
        fHandle << "\t Start Color: " << "HLS(" << hlsRange[i].colorRange.bColor.m_h << ", " << hlsRange[i].colorRange.bColor.m_l << ", " << hlsRange[i].colorRange.bColor.m_s << ")\n";
        fHandle << "\t End factor: " << hlsRange[i].dEndFactor << "\n";
        fHandle << "\t End Value: " << hlsRange[i].dEnd << "\n";
        fHandle << "\t Start Color: " << "HLS(" << hlsRange[i].colorRange.eColor.m_h << ", " << hlsRange[i].colorRange.eColor.m_l << ", " << hlsRange[i].colorRange.eColor.m_s << ")\n";
        fHandle << "\t Start Color: " << "HLS(" << hlsRange[i].colorRange.mColor.m_h << ", " << hlsRange[i].colorRange.mColor.m_l << ", " << hlsRange[i].colorRange.mColor.m_s << ")\n";
    }
    fHandle << "End value mapping to colorSequence \n";
    fHandle.close();
#endif // DEBUG

    return 0;
}

int ColorRangeMapping::calculatRange(int nCount, DataRGBMappingVector& rgbRange)
{
    if (nCount <= 1) {
        return 1;
    }
    if (m_pColorSegment == nullptr) {
        m_pColorSegment = new ColorSegment();
    }
    if (m_pColorSegment == nullptr) {
        return 2;
    }

    ColorCalc calcColor = ColorCalc();
    HLSColorSegment metaR;
    metaR.bColor = calcColor.cRGBToHLS(m_StartColor);
    metaR.eColor = calcColor.cRGBToHLS(m_EndColor);
    metaR.mColor = calcColor.cRGBToHLS(m_StartMidColor);
    m_pColorSegment->setHLSMetaRange(metaR);

    HLSColorRangeVector outRangeSeq;
    int nRet = m_pColorSegment->generateHLSRanges(nCount, outRangeSeq);
    if (nRet != 0) {
        return nRet;
    }
    if (outRangeSeq.size() != nCount) {
        return nRet;
    }
    int nValueCount = nCount + 1;
    valueRangeVector scaleValueVector;
    nRet = calculatRangeScales(nValueCount, scaleValueVector);
    if (nRet != 0) {
        return nRet;
    }
    if (scaleValueVector.size() != nValueCount) {
        return nRet;
    }
    valueRangeVector outValues;
    nRet = generateValueRanges(nValueCount, outValues);
    if (nRet != 0) {
        return nRet;
    }
    if (outValues.size() != nValueCount) {
        return nRet;
    }

    rgbRange.reserve(nCount + 3);

    int nNum = nCount - 1;
    for (int i = 0; i < nCount; i++) {
        DataRGBMappingObj obj;
        obj.dStartFactor = scaleValueVector[i];
        obj.dEndFactor = scaleValueVector[i + 1];
        obj.dStart = outValues[i];
        obj.dEnd = outValues[i + 1];
        obj.colorRange.bColor = calcColor.cHLSToRGB(outRangeSeq[i].bColor);
        obj.colorRange.eColor = calcColor.cHLSToRGB(outRangeSeq[i].eColor);
        obj.colorRange.mColor = calcColor.cHLSToRGB(outRangeSeq[i].mColor);
        rgbRange.emplace_back(obj);
    }

#ifdef DEBUG
    std::fstream fHandle;
    fHandle.open("D:\\test\\SpectrumLog.txt", std::ios::app);
    fHandle << "ColorRangeMapping::calculatRange value mapping to colorSequence \n";
    for (int i = 0; i < nCount; i++) {
        fHandle << "RangeIndex: " << i << "\n";
        fHandle << "\t Start factor: " << rgbRange[i].dStartFactor << "\n";
        fHandle << "\t Start Value: " << rgbRange[i].dStart << "\n";
        fHandle << "\t Start Color: " << "RGB(" << rgbRange[i].colorRange.bColor.m_r << ", " << rgbRange[i].colorRange.bColor.m_g << ", " << rgbRange[i].colorRange.bColor.m_b << ")\n";
        fHandle << "\t End factor: " << rgbRange[i].dEndFactor << "\n";
        fHandle << "\t End Value: " << rgbRange[i].dEnd << "\n";
        fHandle << "\t Start Color: " << "RGB(" << rgbRange[i].colorRange.eColor.m_r << ", " << rgbRange[i].colorRange.eColor.m_g << ", " << rgbRange[i].colorRange.eColor.m_b << ")\n";
        fHandle << "\t Mid Color: " << "RGB(" << rgbRange[i].colorRange.mColor.m_r << ", " << rgbRange[i].colorRange.mColor.m_g << ", " << rgbRange[i].colorRange.mColor.m_b << ")\n";
    }
    fHandle << "End value mapping to colorSequence \n";
    fHandle.close();
#endif // DEBUG

    return 0;
}


int ColorRangeMapping::calculatValueInRange(double dValue, double& dOutValue)
{
    double dDis = std::abs(m_dMax - m_dMin);
    if (!isless(dDis, 0.) && !isgreater(dDis, 0.)) {
        dOutValue = 0.;
        return 0;
    }
    
    double dT = 1 - (m_dThreshold * 3);
    double dFDis = dDis / dT;
    double dBelowF = m_dThreshold * 2;
    auto calc = [&]() -> double {
        double dV = std::abs(dValue - m_dMin) / dFDis + dBelowF;
        if (isless(dOutValue, 0.)) {
            dV = 0.001;
        }
        if (isgreater(dOutValue, 1.)) {
            dV = 0.980;
        }
        return dV;
    };

    // Not have the below, above, outof range.
    if (!isless(m_dThreshold, 0.) && !isgreater(m_dThreshold, 0.)) {
        if (isnan(dValue)) {
            dOutValue = 0.001;
            return 1;
        }
        else {
            dOutValue = calc();
            return 0;
        }
    }
    else if (isless(dValue, m_dMin)) {
        if (m_bSetOutof) {
            if (islessequal(dValue, m_dOutOf)) {
                dOutValue = m_dThreshold - 0.002;
                if (isless(dOutValue, 0.)) {
                    dOutValue = 0.001;
                }
                return 1;
            }
        }
        else if (isnan(dValue)) {
            dOutValue = m_dThreshold - 0.002;
            if (isless(dOutValue, 0.)) {
                dOutValue = 0.001;
            }
            return 1;
        }
        dOutValue = m_dThreshold + 0.002;
        return 2;
    }
    else if (isgreater(dValue, m_dMax)) {
        dOutValue = 1 - 0.002;
        return 3;
    }

    dOutValue = calc();
    return 0;
}

int ColorRangeMapping::calculatRangeScales(int nCount, valueRangeVector& scaleValueVector)
{
    if (nCount <= 1) {
        return 1;
    }

    double dLength = 1 - (m_dThreshold * 3);
    double dOffset = m_dThreshold * 2;
    double dAvg = dLength / (double)(nCount);
    scaleValueVector.reserve(nCount);
    for (int i = 0; i < nCount; i++) {
        double dValue = (dAvg * (double)(i)) + dOffset;
        scaleValueVector.push_back(dValue);
    }

    return 0;
}

int ColorRangeMapping::generateValueRanges(int nCount, valueRangeVector& outRanges)
{
    if (nCount <= 0) {
        return 1;
    }
    if (!isless(m_dMax, m_dMin) && !isgreater(m_dMax, m_dMin)) {
        return 2;
    }
    outRanges.reserve(nCount + 2);
    double dAvg = std::abs(m_dMax - m_dMin) / (double)nCount;
    int nNum = nCount - 1;
    outRanges.emplace_back(m_dMin);
    for (int i = 1; i < nNum; i++) {
        outRanges.emplace_back(m_dMin + dAvg * double(i));
    }
    outRanges.emplace_back(m_dMax);
    return 0;
}

