//
// Created by mfuent on 3/10/2026.
//

#include "Voice.h"
#include "HarmonicOscillator.h"
#include <string>


Voice::Voice(HarmonicOscillator harmonicOscillator, std::string noteString, bool active)
    : harmonicOscillator(harmonicOscillator), noteString(noteString), active(active){}

Voice::Voice(Voice &&other) noexcept
    : harmonicOscillator(other.harmonicOscillator),
      noteString(other.noteString),
      active(other.active.load()) {}

Voice::~Voice() = default;