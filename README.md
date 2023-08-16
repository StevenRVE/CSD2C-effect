# CSD2C-effect
This repository is for a HKU CSD2C assignment. 

## Installation
- Jack2 has to be installed
- Make sure to adjust the path for Jack2 in CMakeLists.txt file to the correct path
- Use cmake to build the project

## About
This effect is an overdrive/distortion. It has 3 different algorithms to choose from:
- Hyperbolic Tangent Soft Clipping(Tanh)
- Hyperbolic Inverse Tangent Hard Clipping(Arctan)
- Two Stage Quadratic Soft Clipping(TSQ)

The algorithms are based on the following paper and video:
- https://www.dafx12.york.ac.uk/papers/dafx12_submission_45.pdf
- https://www.youtube.com/watch?v=_0ys155xv1Q

The highpass and lowpass filters are from pms67's filterLib library which can be found here:
- https://github.com/pms67/FilterLib/tree/master

The anti-aliasing FIR filter is based on the filter desribed in this video by Phil's Lab:
- https://www.youtube.com/watch?v=uNNNj9AZisM

The anti-aliasing FIR filter coefficients are generated using the http://t-filter.appspot.com website.

TODO:
- Add algorithms from https://www.dafx12.york.ac.uk/papers/dafx12_submission_45.pdf
- Add highpass and lowpass parameters controllable by the user