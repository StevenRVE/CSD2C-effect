//
// Created by steve on 10-8-2023.
//

#include "distortion.hpp"

Distortion::Distortion(double sampleRate, DriveType driveType) :
sampleRate(sampleRate),
driveType(driveType)
{

}

Distortion::~Distortion()
{

}

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

void Distortion::setSampleRate(double sampleRate)
{
    this->sampleRate = sampleRate;
}

void Distortion::setDriveType(Distortion::DriveType driveType) {
    this->driveType = driveType;
}

Distortion::DriveType Distortion::getDriveType() {
    return Distortion::driveType;
}

