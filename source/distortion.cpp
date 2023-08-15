//
// Created by steve on 10-8-2023.
//

#include "distortion.hpp"

Distortion::Distortion(float preGain, float drive, Distortion::DriveType driveType)
{
    setDrive(drive);
}

Distortion::Distortion(DriveType driveType)
{

}

Distortion::~Distortion() = default;

void Distortion::process(float input)
{
    switch (getDriveType()) {
        case TANH:
            outputSample = preGain * tanh(tanDrive * input);
            break;
        case ARCTAN:
            outputSample = preGain * atanf(tanDrive * input);
            break;
        case TSQ: // Two Stage Quadratic Soft Clipping (TSQ) https://www.dafx12.york.ac.uk/papers/dafx12_submission_45.pdf
            distInput = preGain * input;
            absInput = fabsf(input);
            signInput = (distInput > 0.0f) ? 1.0f : -1.0f; // hard clipping

            // linear
            if (absInput < tsqDrive) {
                outputSample = 2.0f * distInput;
            }
            // quadratic
            else if (absInput > tsqDrive && absInput < (2.0f * tsqDrive)) {
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

void Distortion::setDrive(float inputDrive)
{
    this->tanDrive = inputDrive * 0.3333f;
    this->tsqDrive = 0.001f * (100.1f - inputDrive);
}

void Distortion::setDriveType(Distortion::DriveType driveType) {
    this->driveType = driveType;
}

Distortion::DriveType Distortion::getDriveType() {
    return Distortion::driveType;
}

