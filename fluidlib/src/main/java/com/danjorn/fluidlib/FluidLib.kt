package com.danjorn.fluidlib

import android.content.Context

private const val SOUNDFONT_NAME = "sndfnt.sf2"

fun setupSynth(context: Context) {
    System.loadLibrary("native-lib1")
    val soundFontPath = copyAssetToTempFile(context, SOUNDFONT_NAME)
    setupSynthExternal(soundFontPath)
}

private fun copyAssetToTempFile(context: Context, fileName: String): String {
    context.assets.open(fileName).use { `is` ->
        val tempFileName = "tmp_$fileName"
        context.openFileOutput(tempFileName, Context.MODE_PRIVATE).use { fos ->
            var bytes_read: Int
            val buffer = ByteArray(4096)
            while (`is`.read(buffer).also { bytes_read = it } != -1) {
                fos.write(buffer, 0, bytes_read)
            }
        }
        return "${context.filesDir}/$tempFileName"
    }
}

private external fun setupSynthExternal(soundFont: String)
external fun closeSynth()

external fun playNote(channel: Int, note: Int)
external fun midiToWav(soundfontPath: String, inputPath: String, outPath: String)
external fun changeInstrument(channel: Int, instrument: Int)

