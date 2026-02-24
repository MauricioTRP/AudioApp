package com.kotlinpl.audio_management

class NativeLib {

    /**
     * A native method that is implemented by the 'audio_management' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'audio_management' library on application startup.
        init {
            System.loadLibrary("audio_management")
        }
    }
}