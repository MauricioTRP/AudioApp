//
// Created by mfuent on 2/24/2026.
//

#ifndef AUDIOAPP_AUDIOWRAPPER_H
#define AUDIOAPP_AUDIOWRAPPER_H

#include <oboe/Oboe.h>
#include "HarmonicOscillator.h"
#include "Voice.h"

class AudioWrapper : public oboe::AudioStreamDataCallback {
public:
    AudioWrapper();
    ~AudioWrapper();

    int startAudio();
    void stopAudio();

    void noteOn(std::string noteString);
    void noteOff(std::string noteString);

    oboe::DataCallbackResult onAudioReady(
            oboe::AudioStream *oboeStream,
            void *audioData,
            int32_t numFrames
            );
private:
    // mutex
    std::mutex mMutex;

    // audio stream
    std::shared_ptr<oboe::AudioStream> mStream;

    // Configuraciones de audio
    static int constexpr kChannels = 2;
    static int constexpr sampleRate = 48000;

//    std::vector<HarmonicOscillator> harmonicOscillators;
    
    // Signature de las voces
    static int constexpr kNotes = 12;
    static Voice voices[kNotes];
};


#endif //AUDIOAPP_AUDIOWRAPPER_H
