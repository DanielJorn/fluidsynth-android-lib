# fluidsynth-android-lib

Kinda lib that provides kinda easy access to FluidSynth API without any need to get your hands dirty.

Believe me, configuring FluidSynth for Android is true pain.

Important note: the following lib contains a lotta lazy implementation and\or possible performance leaks and due to its code it should not be used by anyone in any kind of serious\real projects. I told you.

## Setting up

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

First of all, you gotta call ```setupSynth(context)``` before using any other functions.

Also, you probably need to call ```closeSynth()``` after you're done using the lib to prevent battery drain and performance leaks, but I am really unsure whether if affects anything or not.

```noteOn(channel: Int, note: Int)``` - use to send NOTE_ON MIDI event to the given channel.

```noteOff(channel: Int, note: Int)``` - NOTE_OFF event. You can call this after some time after calling noteOn to stop playing the note.

```midiToWav(inputPath: String, outPath: String)``` - converts .mid to .wav. 

```changeInstrument(channel: Int, instrument: Int)``` - PROGRAM_CHANGE MIDI event. Used to change instrument on the given channel.
