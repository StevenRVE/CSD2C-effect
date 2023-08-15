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
            absInput = fabsf(input);
            signInput = (input > 0.0f) ? 1.0f : -1.0f;

            if (absInput < 0.5f) {
                outputSample = 2.0f * clipIn;
            } else if (absInput < 0.75f) {
                outputSample = signInput * (3.0f - (2.0f * clipIn));
            } else {
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

