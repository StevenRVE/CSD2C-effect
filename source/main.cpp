#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include "jack_module.h"
#include "oscillator.hpp"
#include "distortion.hpp"

int main(int argc, char **argv)
{
    // create a JackModule instance
    JackModule jack;

    // init the jack, use program name as JACK client name
    jack.init(argv[0]);
    float samplerate = jack.getSamplerate();

    // init objects
    Oscillator testTone(samplerate, 440);
    Distortion distortion(Distortion::TANH);

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
    jack.onProcess = [&testTone, &distortion](jack_default_audio_sample_t *inBuf,
                        jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {
        for(unsigned int i = 0; i < nframes; i++) {
            // process distortion
//            distortion.process(inBuf[i]);
            distortion.process(testTone.getSample());

            // write input to output
            outBuf[i] = 0.5 * distortion.getSample();

            // update oscillator
            testTone.tick();
        }
        return 0;
    };

    jack.autoConnect();

    std::cout << "Available commands:\n";
    std::cout << "q: Quit the program.\n";
    std::cout << "drive <value>: Set the drive intensity (0.0 - 10.0).\n";
    std::cout << "pre-gain <value>: Set the pre-gain amplitude (0.0 - 1.0).\n";
    std::cout << "driveType <type>: Choose distortion type (tanh or arctan).\n";
    std::cout << "frequency <value>: Set the test tone frequency.\n";
    std::cout << "help: Show this command list.\n\n";

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
            distortion.setDrive(inputValue);
            std::cout << "Drive set to " << inputValue << std::endl;
        }
        else if (command == "pre-gain" || command == "p")
        {
            distortion.setPreGain(inputValue);
            std::cout << "Pre-gain set to " << inputValue << std::endl;
        }
        else if (command == "frequency" || command == "f")
        {
            testTone.setFrequency(inputValue);
            std::cout << "Frequency set to " << inputValue << std::endl;
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}
