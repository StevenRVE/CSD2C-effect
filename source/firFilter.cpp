//
// Created by steve on 14-8-2023.
//

#include "firFilter.hpp"

FIRFilter::FIRFilter(FilterType filterType) :
filterType(filterType)
{
    setFilterType(filterType);
}

FIRFilter::~FIRFilter() {
    releaseBuffer();
}

void FIRFilter::allocateBuffer(uint8_t size) {
    buffer = new float[size]();
    std::fill_n(buffer, size, 0.0f);
}

void FIRFilter::releaseBuffer() {
    delete[] buffer;
}

void FIRFilter::initializeBuffer() {
    allocateBuffer(filterTaps);
    bufferIndex = 0;
    currentFilterOutput = 0.0f;
}

void FIRFilter::process(float input) {
    // store latest input value at the beginning of the buffer and increment bufferIndex
    buffer[bufferIndex++] = input;

    // wrap bufferIndex if necessary
    if (bufferIndex == filterTaps) {
        bufferIndex = 0;
    }

    // set current output to zero
    float output = 0.0f;
    uint8_t sumIndex = bufferIndex;

    // loop through all the filter taps
    for (uint8_t i = 0; i < filterTaps; i++) {
        // decrement sumIndex, but wrap around if necessary
        sumIndex = sumIndex != 0 ? sumIndex - 1 : filterTaps - 1;
        // add the next sample multiplied by the filter coefficient to the output
        output += buffer[sumIndex] * filterCoefficients[i];
    }

    currentFilterOutput = output;
}

float FIRFilter::getSample() {
    return currentFilterOutput;
}

FilterType FIRFilter::getFilterType() const {
    return filterType;
}

void FIRFilter::setFilterType(FilterType filterType) {
    this->filterType = filterType;
    switch (filterType)
    {
        case FILTER_ANTIALIASING_LOW_QUALITY:
            filterCoefficients = antiAliasingLowQuality;
            filterTaps = ANTI_ALIASING_LOW_QUALITY_TAPS;
            break;
        case FILTER_ANTIALIASING_MEDIUM_QUALITY:
            filterCoefficients = antiAliasingMediumQuality;
            filterTaps = ANTI_ALIASING_MEDIUM_QUALITY_TAPS;
            break;
        case FILTER_ANTIALIASING_HIGH_QUALITY:
            filterCoefficients = antiAliasingHighQuality;
            filterTaps = ANTI_ALIASING_HIGH_QUALITY_TAPS;
            break;
    }
    initializeBuffer();
}