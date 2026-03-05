//
// Created by mfuent on 2/26/2026.
//

#include "HarmonicOscillator.h"

double HarmonicOscillator::getNextSample(double deltaTime) {
    double sample = amplitude * sin(2 * M_PI * frequency * time + phase);
    time += deltaTime;

    if (time >= 1.0/frequency) time -= 1.0/frequency;

    return sample;
}