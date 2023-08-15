//
// Created by steve on 10-8-2023.
//

#include "distortion.hpp"

Distortion::Distortion(float preGain, float drive, Distortion::DriveType driveType)
{

}

Distortion::Distortion(DriveType driveType)
{

}

Distortion::~Distortion() = default;

void Distortion::process(float input)
{
    switch (getDriveType()) {
        case TANH:
            outputSample = preGain * tanh(drive * input);
            break;
        case ARCTAN:
            outputSample = preGain * atanf(drive * input);
            break;
        case TSQ: // Two Stage Quadratic Soft Clipping (TSQ) https://www.dafx12.york.ac.uk/papers/dafx12_submission_45.pdf
            distInput = preGain * input;
            absInput = fabsf(input);
            signInput = (distInput > 0.0f) ? 1.0f : -1.0f; // hard clipping

            // linear
            if (absInput < drive) {
                outputSample = 2.0f * distInput;
            }
            // quadratic
            else if (absInput > drive && absInput < (2.0f * drive)) {
                outputSample = signInput * (3.0f - (3.0f - (2.0f * absInput)) * (3.0f - (2.0f * absInput))) / 3.0f;
            }
            // hard clipping
            else {
                outputSample = signInput;
            }

            if (outputSample > 1.0f)
                outputSample = 1.0f;
            else if (outputSample < -1.0f)
                outputSample = -1.0f;
            break;
        default:
            break;
    }
}

float Distortion::getSample()
{
    return outputSample;
}

void Distortion::setPreGain(float preGain)
{
    this->preGain = preGain;
}

void Distortion::setDrive(float newDrive)
{
//    float value = (newDrive * alpha) + (previousDrive * alpha);
    switch (getDriveType()) {
        case TANH:
            this->drive = newDrive * 0.3333f;
            break;
        case ARCTAN:
            this->drive = newDrive * 0.3333f;
            break;
        case TSQ:
            newDrive = 101.0f - newDrive;
            this->drive = newDrive * 0.001f;
            break;
        default:
            break;
    }

}

void Distortion::setDriveType(Distortion::DriveType driveType) {
    this->driveType = driveType;
}

Distortion::DriveType Distortion::getDriveType() {
    return Distortion::driveType;
}

