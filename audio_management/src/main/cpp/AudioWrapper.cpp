//
// Created by mfuent on 2/24/2026.
//

#include "AudioWrapper.h"
#include <oboe/Oboe.h>

int AudioWrapper::startAudio() {
    std::lock_guard<std::mutex> lock(mMutex);

    oboe::AudioStreamBuilder builder;

    oboe::Result result = builder.setSharingMode(oboe::SharingMode::Exclusive)
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

AudioWrapper::AudioWrapper() {
    harmonicOscillators.push_back(harmonicC4);
    harmonicOscillators.push_back(harmonicE4);
    harmonicOscillators.push_back(harmonicG4);
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
    const size_t numOscillators = harmonicOscillators.size();
    float *out = static_cast<float *>(audioData);

    if (numOscillators == 0) {
        memset(out, 0, numFrames * kChannels * sizeof(float));
        return oboe::DataCallbackResult::Continue;
    }

    for (int i = 0; i < numFrames; i++) {
        double sum = 0.0;
        for (int j = 0; j < numOscillators; j++) {
            sum += harmonicOscillators[j].getNextSample();
        }
        sum /= static_cast<double >(numOscillators);

        const float sample = static_cast<float>(sum);

        for (int j = 0; j < kChannels; j++) {
            out[i * kChannels + j] = sample;
        }
    }

    return oboe::DataCallbackResult::Continue;
}