#include <jni.h>
#include <fluidsynth.h>
#include <unistd.h>

fluid_settings_t *settings = nullptr;
fluid_synth_t *synth = nullptr;
fluid_audio_driver_t *adriver = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_setupSynthExternal(JNIEnv *env, jclass thiz,
                                                        jstring soundfont
) {
    // Setup synthesizer
    settings = new_fluid_settings();
    synth = new_fluid_synth(settings);
    adriver = new_fluid_audio_driver(settings, synth);

    // Load sample soundfont
    const char *soundfontPath = env->GetStringUTFChars(soundfont, nullptr);
    fluid_synth_sfload(synth, soundfontPath, 1);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_closeSynth(JNIEnv *env, jclass thiz) {
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_playNote(JNIEnv *env,
                                              jclass thiz,
                                              jint channel,
                                              jint note) {


    // succesfully loaded soundfont...play something
    fluid_synth_noteon(synth, channel, note, 127); // play middle C
    usleep(1000);
    fluid_synth_noteoff(synth, channel, note); // play middle C


}extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_changeInstrument(JNIEnv *env,
                                                      jclass thiz,
                                                      jint channel,
                                                      jint instrument) {
    fluid_synth_program_change(synth, channel, instrument);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_midiToWav(JNIEnv *env, jclass thiz,
                                               jstring soundfont_path,
                                               jstring input_path,
                                               jstring out_path) {
    fluid_settings_t *settings;
    fluid_synth_t *synth;
    fluid_player_t *player;
    fluid_file_renderer_t *renderer;
    settings = new_fluid_settings();

    // specify the file to store the audio to
    // make sure you compiled fluidsynth with libsndfile to get a real wave file
    // otherwise this file will only contain raw s16 stereo PCM
    const char *lazy = env->GetStringUTFChars(out_path, nullptr);
    fluid_settings_setstr(settings, "audio.file.name", lazy);

    // use number of samples processed as timing source, rather than the system timer
    fluid_settings_setstr(settings, "player.timing-source", "sample");

    // since this is a non-realtime scenario, there is no need to pin the sample data
    fluid_settings_setint(settings, "synth.lock-memory", 0);
    synth = new_fluid_synth(settings);

    // Load sample soundfont
    const char *soundfontPath = env->GetStringUTFChars(soundfont_path, nullptr);
    fluid_synth_sfload(synth, soundfontPath, 1);

    const char *inputPath = env->GetStringUTFChars(input_path, nullptr);

    player = new_fluid_player(synth);
    fluid_player_add(player, inputPath);
    fluid_player_play(player);
    renderer = new_fluid_file_renderer(synth);
    while (fluid_player_get_status(player) == FLUID_PLAYER_PLAYING) {
        if (fluid_file_renderer_process_block(renderer) != FLUID_OK) {
            break;
        }
    }

    // just for sure: stop the playback explicitly and wait until finished
    fluid_player_stop(player);
    fluid_player_join(player);
    delete_fluid_file_renderer(renderer);
    delete_fluid_player(player);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}