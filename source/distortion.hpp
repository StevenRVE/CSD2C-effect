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
        ARCTAN,
        TSQ
    };

    Distortion(float preGain, float drive, DriveType driveType = TANH);
    explicit Distortion(DriveType driveType = TANH);
    ~Distortion();
    void process(float input);
    float getSample();
    void setPreGain(float preGain);
    void setDrive(float newDrive);
    void setDriveType(DriveType driveType);
    DriveType getDriveType();

private:
    float preGain{1.0f};
    float drive{10.0f};
    float previousDrive{0.5f};
    float alpha{0.3f};
    float outputSample{0.0f};

    DriveType driveType{TANH};

    // phil variables
    float clipIn{0.0f};
    float absInput{0.0f};
    float signInput{0.0f};
};

#endif //SVE_CHORUS_ARCTANGENTDISTORTION_HPP
