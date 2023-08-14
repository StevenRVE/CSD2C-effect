//
// Created by steve on 10-8-2023.
//

#ifndef SVE_CHORUS_ARCTANGENTDISTORTION_HPP
#define SVE_CHORUS_ARCTANGENTDISTORTION_HPP

#include <cmath>

class Distortion{
public:
    enum DriveType{
        TANH,
        ARCTAN
    };

    Distortion(DriveType driveType = TANH);
    ~Distortion();
    void process(float input);
    float getSample();
    void setPreGain(float preGain);
    void setDrive(float newDrive);
    void setSampleRate(double sampleRate);
    void setDriveType(DriveType driveType);
    DriveType getDriveType();

private:
    float preGain{1.0f};
    float drive{0.5f};
    float previousDrive{0.5f};
    float alpha{0.3f};
    float outputSample{0.0f};

    DriveType driveType{TANH};
};

#endif //SVE_CHORUS_ARCTANGENTDISTORTION_HPP
