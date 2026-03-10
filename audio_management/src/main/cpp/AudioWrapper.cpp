//
// Created by mfuent on 2/24/2026.
//

#include "AudioWrapper.h"
#include <oboe/Oboe.h>
#include <algorithm>

AudioWrapper::AudioWrapper() {}
AudioWrapper::~AudioWrapper() = default;

Voice AudioWrapper::voices[kNotes] = {
        Voice(HarmonicOscillator(0.5, 261.63, 0.0), "C4", false), // C4
        Voice(HarmonicOscillator(0.5, 277.18, 0.0), "C#4", false), // C#4
        Voice(HarmonicOscillator(0.5, 293.66, 0.0), "D4", false), // D4
        Voice(HarmonicOscillator(0.5, 311.13, 0.0), "D#4", false), // D#4
        Voice(HarmonicOscillator(0.5, 329.63, 0.0), "E4", false), // E4
        Voice(HarmonicOscillator(0.5, 349.23, 0.0), "F4", false), // F4
        Voice(HarmonicOscillator(0.5, 369.99, 0.0), "F#4", false), // F#4
        Voice(HarmonicOscillator(0.5, 392.00, 0.0), "G4", false), // G4
        Voice(HarmonicOscillator(0.5, 415.30, 0.0), "G#4", false), // G#4
        Voice(HarmonicOscillator(0.5, 440.00, 0.0), "A4", false), // A4
        Voice(HarmonicOscillator(0.5, 466.16, 0.0), "A#4", false), // A#4
        Voice(HarmonicOscillator(0.5, 493.88, 0.0), "B4", false)  // B4
};

int AudioWrapper::startAudio() {
    std::lock_guard<std::mutex> lock(mMutex);

    oboe::AudioStreamBuilder builder;

    oboe::Result result = builder.setSharingMode(oboe::SharingMode::Shared)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setChannelCount(kChannels)
            ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Medium)
            ->setFormat(oboe::AudioFormat::Float)
            ->setDataCallback(this)
            ->openStream(mStream);

    if (result != oboe::Result::OK) return static_cast<int>(result);

    result = mStream->requestStart();
    return static_cast<int>(result);
}

void AudioWrapper::stopAudio() {
    if (mStream) {
        mStream->stop();
        mStream->close();
        mStream.reset(); // "puntero vacío"
    }
}

void AudioWrapper::noteOn(std::string noteString) {
// Activar nota con base en string
    for (int i = 0; i < kNotes; i++) {
        if (voices[i].noteString == noteString) {
            voices[i].active.store(true, std::memory_order_release);
            return;
        }
    }
}

void AudioWrapper::noteOff(std::string noteString) {
    // desactivar con base en string
    auto it = std::find_if(std::begin(voices), std::end(voices), [&noteString](const Voice& voice) {
        return voice.noteString == noteString;
    });

    if (it != std::end(voices)) {
        it->active.store(false, std::memory_order_release);
    }
}

/**
 * Acá se procesa el audio por bloques
 * @param oboeStream
 * @param audioData
 * @param numFrames
 * @return
 */
oboe::DataCallbackResult AudioWrapper::onAudioReady(
        oboe::AudioStream *oboeStream,
        void *audioData,
        int32_t numFrames) {
    float *out = static_cast<float *>(audioData);

    double sampleRate = static_cast<double>(oboeStream->getSampleRate());
    double deltaTime = 1.0 / sampleRate;

    for (int i = 0; i < numFrames; i++) {
        double sum = 0.0;
        int activeCount = 0;

        for (int j = 0; j < kNotes; j++) {
            if (voices[j].active.load(std::memory_order_acquire)) {
                sum += voices[j].harmonicOscillator.getNextSample(deltaTime);
                activeCount++;
            }
        }

        if (activeCount > 0) sum / static_cast<double>(activeCount);
        const float sample = static_cast<float>(sum);

        for (int j = 0; j < kChannels; j++) {
            out[i * kChannels + j] = sample;
        }
    }

    return oboe::DataCallbackResult::Continue;
}