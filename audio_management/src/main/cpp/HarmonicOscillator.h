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

HarmonicOscillator harmonicOscillator440 = HarmonicOscillator(
        0.5,
        440.0,
        0.0);

#endif //AUDIOAPP_HARMONICOSCILLATOR_H
