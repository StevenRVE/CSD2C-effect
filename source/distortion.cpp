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
            outputSample = /*preGain*/ 0.8f * tanh(/*drive*/ 5.0f * input);
            break;
        case ARCTAN:
            outputSample = preGain * atanf(drive * input);
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

