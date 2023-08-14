#include <iostream>
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

    // keep the program running and listen for user input, q = quit
    std::cout << "\n\nPress 'q' when you want to quit the program.\n";
    bool running = true;
    while (running)
    {
        switch (std::cin.get())
        {
            case 'q':
                running = false;
                jack.end();
                break;
        }
    }

    return 0;
}
