package com.danjorn.fluidlib

import android.content.Context
import java.io.File

private const val SOUNDFONT_NAME = "sndfnt.sf2"

fun setupSynth(context: Context) {
    System.loadLibrary("fluid-lib-android")
    val soundFontPath = copyAssetToTempFile(context, SOUNDFONT_NAME)
    setupSynthExternal(soundFontPath)
}

private fun copyAssetToTempFile(context: Context, fileName: String): String {
    context.assets.open(fileName).use { inStream ->
        val tempFileName = "tmp_$fileName"
        val fullPath = "${context.filesDir}/$tempFileName"
        val possibleFile = File(fullPath)

        return if (possibleFile.exists()){
            fullPath
        } else {
            context.openFileOutput(tempFileName, Context.MODE_PRIVATE).use { outStream ->
                var bytesRead: Int
                val buffer = ByteArray(4096)
                while (inStream.read(buffer).also { bytesRead = it } != -1) {
                    outStream.write(buffer, 0, bytesRead)
                }
            }
            fullPath
        }
    }
}

private external fun setupSynthExternal(soundFont: String)
external fun closeSynth()

external fun noteOn(channel: Int, note: Int)
external fun noteOff(channel: Int, note: Int)
external fun midiToWav(inputPath: String, outPath: String)
external fun changeInstrument(channel: Int, instrument: Int)

