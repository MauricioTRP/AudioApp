//
// Created by mfuent on 3/10/2026.
//

#ifndef AUDIOAPP_VOICE_H
#define AUDIOAPP_VOICE_H


#include "HarmonicOscillator.h"
#include <string>
#include <atomic>

class Voice {
public:
    HarmonicOscillator harmonicOscillator; // miembro "más grande"
    std::string noteString;
    std::atomic<bool> active; // miembro "más pequeño"

    Voice(
            HarmonicOscillator harmonicOscillator,
            std::string noteString,
            bool active
            );

    Voice(Voice&& other) noexcept;
    ~Voice();
};


#endif //AUDIOAPP_VOICE_H
