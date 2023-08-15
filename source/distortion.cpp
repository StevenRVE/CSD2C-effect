//
// Created by steve on 10-8-2023.
//

#include "distortion.hpp"

Distortion::Distortion(DriveType driveType) :
driveType(driveType)
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
        case COPILOTSUGGESTION1:
            outputSample = preGain * atanf(drive * input) / atanf(drive);
            break;
        case PHIL:
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
    float value = (newDrive * alpha) + (previousDrive * alpha);
    this->drive = value;
}

void Distortion::setDriveType(Distortion::DriveType driveType) {
    this->driveType = driveType;
}

Distortion::DriveType Distortion::getDriveType() {
    return Distortion::driveType;
}

