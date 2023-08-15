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
    void setDrive(float inputDrive);
    void setDriveType(DriveType driveType);
    DriveType getDriveType();

private:
    float preGain{1.0f};
    float tanDrive{10.0f};
    float tsqDrive{1.0f};
    float outputSample{0.0f};

    DriveType driveType{TANH};

    // phil variables
    float distInput{0.0f};
    float absInput{0.0f};
    float signInput{0.0f};
};

#endif //SVE_CHORUS_ARCTANGENTDISTORTION_HPP
