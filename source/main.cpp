#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include "jack_module.h"
#include "oscillator.hpp"
#include "distortion.hpp"
#include "firFilter.hpp"
#include "FilterLib/LowpassFilter.h"
#include "FilterLib/HighpassFilter.h"

int main(int argc, char **argv)
{
    // create a JackModule instance
    JackModule jack;

    // init the jack, use program name as JACK client name
    jack.init(argv[0]);
    float samplerate = jack.getSamplerate();

    // init objects
    Oscillator testTone(samplerate, 440);
    Distortion overdrive(Distortion::TANH);
    Distortion distortion(Distortion::TANH);
    FIRFilter antiAliasingFilter;
    antiAliasingFilter.initializeBuffer();
    LowpassFilter lowpassFilter(2, 10000, samplerate);
    HighpassFilter highpassFilter(2, 100, samplerate);

    // Parse command line arguments
    // -D <drive type> : Specify the drive type <tanh|arctan>
    for(int i = 0 ; i < argc ; i++) {
        if(strcmp(argv[i], "-D") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "tanh") == 0) {
                    distortion.setDriveType(Distortion::TANH);
                } else if (strcmp(argv[i + 1], "arctan") == 0) {
                    distortion.setDriveType(Distortion::ARCTAN);
                } else {
                    std::cerr << "Error: Invalid drive type specified.\n";
                    return 1; // Exit with an error code
                }
            } else {
                std::cerr << "Error: Missing drive type after -D flag.\n";
                return 1; // Exit with an error code
            }
        }
    }

    // assign a function to the JackModule::onProces
    jack.onProcess = [&testTone, &distortion, &antiAliasingFilter]
        (jack_default_audio_sample_t *inputBuffer, jack_default_audio_sample_t *outputBuffer, jack_nframes_t nframes)
    {
        for(unsigned int i = 0; i < nframes; i++) {
            // anti-aliasing filter
            antiAliasingFilter.process(inputBuffer[i]);

            antiAliasingFilter.process(highpassFilter.update(inputBuffer[i]));
            overdrive.process(antiAliasingFilter.getSample());
            // distortion
            distortion.process(overdrive.getSample());

            // write input to output
            outputBuffer[i] = 0.2 * distortion.getSample();

            // update oscillator
            testTone.tick();
        }
        return 0;
    };

    jack.autoConnect();

    std::cout << "Available commands:\n";
    std::cout << "q: Quit the program.\n";
    std::cout << "d|drive <value>: Set the drive intensity (0.0 - 20.0).\n";
    std::cout << "pg|pre-gain <value>: Set the pre-gain amplitude (0.1 - 2.0).\n";
    std::cout << "dt|driveType <type>: Choose distortion type (tanh or arctan).\n";
    std::cout << "f|frequency <value>: Set the test tone frequency (1.0 - 20000.0).\n";
    std::cout << "aa|AntiAliasing FilterType <type>: Choose filter type \n"
                 "    1: FILTER_ANTIALIASING_LOW_QUALITY\n"
                 "    2: FILTER_ANTIALIASING_MEDIUM_QUALITY\n"
                 "    3: FILTER_ANTIALIASING_HIGH_QUALITY)\n";
    std::cout << "h|help: Show this command list.\n\n";

    bool running = true;
    std::string command;
    float inputValue;

    // TODO: implement a better way to handle input using std::unordered_map
    while (running)
    {
        std::getline(std::cin, command);

        std::istringstream iss(command);
        iss >> command >> inputValue;

        if (command == "quit" || command == "q")
        {
            running = false;
            jack.end();
        }
        else if (command == "drive" || command == "d")
        {
            if (inputValue >= 0.1f && inputValue <= 30.0f) {
                distortion.setDrive(inputValue);
                std::cout << "Drive set to " << inputValue << std::endl;
            } else {
                std::cout << "Invalid input value for drive" << std::endl;
            }
        }
        else if (command == "pre-gain" || command == "pg") {
            if (inputValue >= 0.1f && inputValue <= 2.0f) {
                distortion.setPreGain(inputValue);
                std::cout << "Pre-gain set to " << inputValue << std::endl;
            } else {
                std::cout << "Invalid input value for pre-gain" << std::endl;
            }
        }
        else if (command == "driveType" || command == "dt")
        {
            if (inputValue == 0) {
                distortion.setDriveType(Distortion::TANH);
                std::cout << "Drive type set to tanh" << std::endl;
            } else if (inputValue == 1) {
                distortion.setDriveType(Distortion::ARCTAN);
                std::cout << "Drive type set to arctan" << std::endl;
            } else if (inputValue == 2) {
                distortion.setDriveType(Distortion::COPILOTSUGGESTION1);
                std::cout << "Drive type set to COPILOTSUGGESTION1" << std::endl;
            } else if (inputValue == 3) {
                distortion.setDriveType(Distortion::PHIL);
                std::cout << "Drive type set to PHIL" << std::endl;
            }
            else {
                std::cout << "Invalid input value for drive type" << std::endl;
            }
        }
        else if (command == "frequency" || command == "f")
        {
            if (inputValue >= 0.1f && inputValue <= 20000.0f) {
                testTone.setFrequency(inputValue);
                std::cout << "Frequency set to " << inputValue << std::endl;
            } else {
                std::cout << "Invalid input value for frequency" << std::endl;
            }
        }
        else if (command == "antiAliasingFilter" || command == "aa")
        {
            if (inputValue == 1) {
                antiAliasingFilter.setFilterType(FILTER_ANTIALIASING_LOW_QUALITY);
                std::cout << "AntiAliasing filter set to low quality" << std::endl;
            } else if (inputValue == 2) {
                antiAliasingFilter.setFilterType(FILTER_ANTIALIASING_MEDIUM_QUALITY);
                std::cout << "AntiAliasing filter set to medium quality" << std::endl;
            } else if (inputValue == 3) {
                antiAliasingFilter.setFilterType(FILTER_ANTIALIASING_HIGH_QUALITY);
                std::cout << "AntiAliasing filter set to high quality" << std::endl;
            } else {
                std::cout << "Invalid input value for anti-aliasing filter type" << std::endl;
            }
        }
        else if (command == "help" || command == "h")
        {
            std::cout << "Available commands:\n";
            std::cout << "q: Quit the program.\n";
            std::cout << "drive <value>: Set the drive intensity (0.0 - 20.0).\n";
            std::cout << "pre-gain <value>: Set the pre-gain amplitude (0.1 - 2.0).\n";
            std::cout << "driveType <type>: Choose distortion type (tanh or arctan).\n";
            std::cout << "frequency <value>: Set the test tone frequency.\n";
            std::cout << "help: Show this command list.\n\n";
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }
    return 0;
}
