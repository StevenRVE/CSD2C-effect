//
// Created by steve on 14-8-2023.
//
// firFilter is based on the example from: FIR Filter Design and Software Implementation - Phil's Lab #17 video on YouTube
// https://www.youtube.com/watch?v=uNNNj9AZisM

#ifndef CSD2C_EFFECT_FIRFILTER_HPP
#define CSD2C_EFFECT_FIRFILTER_HPP

#include <cmath>
#include <cstdint>
#include <iostream>

#include "filterCoefficients.hpp"

enum FilterType
{
    FILTER_ANTIALIASING_LOW_QUALITY,
    FILTER_ANTIALIASING_MEDIUM_QUALITY,
    FILTER_ANTIALIASING_HIGH_QUALITY
};

class FIRFilter
{
public:
    FIRFilter(FilterType filterType = FILTER_ANTIALIASING_HIGH_QUALITY);
    ~FIRFilter();

    // buffer methods
    void allocateBuffer(uint8_t size);
    void releaseBuffer();
    void initializeBuffer();

    // filter methods
    void process(float input);
    float getSample();

    // FilterType methods
    FilterType getFilterType() const;
    void setFilterType(FilterType filterType);

private:
    FilterType filterType = FILTER_ANTIALIASING_HIGH_QUALITY;
    const float* filterCoefficients = antiAliasingHighQuality;
    uint8_t filterTaps = ANTI_ALIASING_HIGH_QUALITY_TAPS;

    float* buffer = nullptr;
    uint8_t bufferIndex = 0;
    float currentFilterOutput = 0;
};

#endif //CSD2C_EFFECT_FIRFILTER_HPP
