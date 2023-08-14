#include <iostream>
#include "jack_module.h"
#include "distortion.hpp"
#include "oscillator.hpp"

int main(int argc, char **argv)
{
    // create a JackModule instance
    JackModule jack;

    // init the jack, use program name as JACK client name
    jack.init(argv[0]);
    float samplerate = jack.getSamplerate();

    // testTone
    Oscillator testTone(samplerate, 440);

    // assign a function to the JackModule::onProces
    jack.onProcess = [&testTone](jack_default_audio_sample_t *inBuf,
                        jack_default_audio_sample_t *outBuf, jack_nframes_t nframes) {
        for(unsigned int i = 0; i < nframes; i++) {

            // write input to output
            outBuf[i] = testTone.getSample() * 0.5;

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
