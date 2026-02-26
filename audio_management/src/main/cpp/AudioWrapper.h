//
// Created by mfuent on 2/24/2026.
//

#ifndef AUDIOAPP_AUDIOWRAPPER_H
#define AUDIOAPP_AUDIOWRAPPER_H

#include <oboe/Oboe.h>
#include "HarmonicOscillator.h"

class AudioWrapper : public oboe::AudioStreamDataCallback {
public:
    int startAudio();
    void stopAudio();

    void addOscillatorToVector(HarmonicOscillator harmonicOscillator);
    void removeOscillatorFromVector(HarmonicOscillator harmonicOscillator);

    oboe::DataCallbackResult onAudioReady(
            oboe::AudioStream *oboeStream,
            void *audioData,
            int32_t numFrames
            );
private:
    // mutex

    // audio stream
    std::shared_ptr<oboe::AudioStream> mStream;

    // Configuraciones de audio
    static int constexpr kChannels = 2;
    static int constexpr sampleRate = 48000;

    std::vector<HarmonicOscillator> harmonicOscillators;
};


#endif //AUDIOAPP_AUDIOWRAPPER_H
