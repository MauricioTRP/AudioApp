#include <jni.h>
#include <string>
#include "AudioWrapper.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_kotlinpl_audio_1management_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_kotlinpl_audio_1management_AudioManagement_createNativeEngine(JNIEnv *env, jobject thiz) {
    auto* engine = new AudioWrapper();
    return reinterpret_cast<jlong>(engine);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_kotlinpl_audio_1management_AudioManagement_nativeStart(JNIEnv *env, jobject thiz, jlong handle) {
    auto* engine = reinterpret_cast<AudioWrapper*>(handle);
    return engine->startAudio();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_kotlinpl_audio_1management_AudioManagement_nativeStop(JNIEnv *env, jobject thiz, jlong handle) {
    auto* engine = reinterpret_cast<AudioWrapper*>(handle);
    engine->stopAudio();
}

