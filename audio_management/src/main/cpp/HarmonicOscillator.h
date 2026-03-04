//
// Created by mfuent on 2/26/2026.
//

#ifndef AUDIOAPP_HARMONICOSCILLATOR_H
#define AUDIOAPP_HARMONICOSCILLATOR_H

#include <cmath>

/**
 *
 * Amplitude
 * Frequency
 * Phase (en qué parte del ciclo está la onda)
 * Time
 */
class HarmonicOscillator {
    double amplitude;
    double frequency;
    double phase;
    double time;

public:
    HarmonicOscillator(double amplitude, double freq, double phase = 0.0)
    : amplitude(amplitude), frequency(freq), phase(phase), time(0.0) {}

    double getNextSample();
};

HarmonicOscillator harmonicC4 = HarmonicOscillator(
        0.5,
        261.63,
        0.0
        );

HarmonicOscillator harmonicE4 = HarmonicOscillator(
        0.5,
        329.63,
        0.0
);

HarmonicOscillator harmonicG4 = HarmonicOscillator(
        0.5,
        392,
        0.0
);



#endif //AUDIOAPP_HARMONICOSCILLATOR_H
