//
// Created by mfuent on 2/26/2026.
//

#include "HarmonicOscillator.h"

double HarmonicOscillator::getNextSample() {
    double sample = amplitude * sin(2 * M_PI * frequency * time + phase);
    return sample;
}