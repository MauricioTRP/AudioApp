//
// Created by mfuent on 2/24/2026.
//

#include "AudioWrapper.h"
#include <oboe/Oboe.h>

int AudioWrapper::startAudio() {
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

}