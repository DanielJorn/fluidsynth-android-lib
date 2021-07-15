# fluidsynth-android-lib

Kinda lib that provides kinda easy access to FluidSynth API without any need to get your hands dirty.

Believe me, configuring FluidSynth for Android is true pain.

Important note: the following lib contains a lotta lazy implementation and\or possible performance leaks and due to its code it should not be used by anyone in any kind of serious\real projects. I told you.

## Preface 
Read it carefully.https://github.com/FluidSynth/fluidsynth/wiki/BuildingForAndroid#preface

fluidsynth is licensed under LGPL-2.1; [make sure you understand what that means](https://github.com/FluidSynth/fluidsynth/wiki/LicensingFAQ) when using it in your app!

## Setting up

Read the preface above!

[Seriously, read the preface!!](https://github.com/FluidSynth/fluidsynth/wiki/BuildingForAndroid#Preface)


Put this in project-level build.gragle

```
allprojects {
    repositories {
        maven { url 'https://jitpack.io' }
    }
}
```

... and this to app-level build.gradle

```
implementation 'com.github.DanielJorn:fluidsynth-android-lib:0.3'
```

## Usage

Read the preface above!

[Seriously, read the preface!!](https://github.com/FluidSynth/fluidsynth/wiki/BuildingForAndroid#Preface)


First of all, you gotta call ```setupSynth(context)``` before using any other functions.

Also, you probably need to call ```closeSynth()``` after you're done using the lib to prevent battery drain and performance leaks, but I am really unsure whether if affects anything or not.

```midiToWav(inputPath: String, outPath: String)``` blocks thread. You must implement some kind of async non-blocking code to achieve the best user experience.

```noteOn(channel: Int, note: Int)``` - use to send NOTE_ON MIDI event to the given channel.

```noteOff(channel: Int, note: Int)``` - NOTE_OFF event. You can call this after some time after calling noteOn to stop playing the note.

```midiToWav(inputPath: String, outPath: String)``` - converts .mid to .wav. 

```changeInstrument(channel: Int, instrument: Int)``` - PROGRAM_CHANGE MIDI event. Used to change instrument on the given channel.

## Examples 

This repo contains an example of using the lib.

Also, [here is one more repo](https://github.com/DanielJorn/Beat-Em-Up/tree/c-library) using this lib.

### Converting .mid to .wav

[source](https://github.com/DanielJorn/Beat-Em-Up/blob/c-library/app/src/main/java/com/danjorn/beatemup/features/track/files/WavFileManager.kt#L13)

```
suspend fun convertMidiToWav(inputPath: String, outPath: String){

    withContext(Dispatchers.IO) {
        try {
            midiToWav(inputPath, outPath)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }
}
```

### Playing note, canceling note, changing insturment
[source](https://github.com/DanielJorn/Beat-Em-Up/blob/c-library/app/src/main/java/com/danjorn/beatemup/features/track/play/PlayerController.kt)

```
fun playNote(channel, Int, note: Int) {
    noteOn(channel, note)
}

fun cancelNotePlay(channel, Int, note: Int){
    noteOff(channel, note)
}
    
fun changeInstrument(channel, Int, instrument: Int) {
    changeInstrument(channel, instrument)
}

```
