package com.kotlinpl.audio_management

class AudioManagement : AutoCloseable{
    companion object {
        init {
            System.loadLibrary("audio_management")
        }
    }

    override fun close() {
        TODO("Not yet implemented")
    }

    fun play() = nativeStart(nativeHandle)
    fun stop() = nativeStop(nativeHandle)

    private var nativeHandle: Long = createNativeEngine()

    private external fun createNativeEngine() : Long
    private external fun nativeStart(handle: Long) : Long
    private external fun nativeStop(handle: Long)
}