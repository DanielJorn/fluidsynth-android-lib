#include <jni.h>
#include <fluidsynth.h>
#include <unistd.h>

fluid_settings_t *settings = nullptr;
fluid_synth_t *synth = nullptr;
fluid_audio_driver_t *adriver = nullptr;
const char *soundfontPath = nullptr;

void firstTimeSetupVariables();

void firstTimeSetupSoundFont(JNIEnv *env, jstring soundfont);

void setOutPath(JNIEnv *env, jstring out_path, fluid_settings_t *settings);

void configureSettings(fluid_settings_t *settings);

void renderFile(fluid_player_t *player, fluid_file_renderer_t *renderer);

void cleanUpFluidVariables(fluid_settings_t *settings, fluid_synth_t *synth,
                           fluid_player_t *player, fluid_file_renderer_t *renderer);

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_setupSynthExternal(JNIEnv *env, jclass, jstring soundfont) {
    firstTimeSetupVariables();
    firstTimeSetupSoundFont(env, soundfont);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_closeSynth(JNIEnv *, jclass) {
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_noteOn(JNIEnv *, jclass, jint channel, jint note) {
    fluid_synth_noteon(synth, channel, note, 127);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_noteOff(JNIEnv *, jclass, jint channel, jint note) {
    fluid_synth_noteoff(synth, channel, note);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_changeInstrument(JNIEnv *, jclass,
                                                      jint channel,
                                                      jint instrument) {
    fluid_synth_program_change(synth, channel, instrument);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_danjorn_fluidlib_FluidLibKt_midiToWav(JNIEnv *env, jclass,
                                               jstring input_path,
                                               jstring out_path) {
    fluid_settings_t *settings;
    fluid_synth_t *synth;
    fluid_player_t *player;
    fluid_file_renderer_t *renderer;
    settings = new_fluid_settings();

    setOutPath(env, out_path, settings);
    configureSettings(settings);

    synth = new_fluid_synth(settings);
    fluid_synth_sfload(synth, soundfontPath, 1);

    const char *inputPath = env->GetStringUTFChars(input_path, nullptr);

    player = new_fluid_player(synth);
    fluid_player_add(player, inputPath);
    fluid_player_play(player);
    renderer = new_fluid_file_renderer(synth);

    renderFile(player, renderer);

    cleanUpFluidVariables(settings, synth, player, renderer);
}

void cleanUpFluidVariables(fluid_settings_t *settings,
                           fluid_synth_t *synth,
                           fluid_player_t *player,
                           fluid_file_renderer_t *renderer) {
    fluid_player_stop(player);
    fluid_player_join(player);
    delete_fluid_file_renderer(renderer);
    delete_fluid_player(player);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

void renderFile(fluid_player_t *player, fluid_file_renderer_t *renderer) {
    while (fluid_player_get_status(player) == FLUID_PLAYER_PLAYING) {
        if (fluid_file_renderer_process_block(renderer) != FLUID_OK) {
            break;
        }
    }
}

void configureSettings(fluid_settings_t *settings) {// number of samples as timing source
    fluid_settings_setstr(settings, "player.timing-source", "sample");

    // do not pin the samples
    fluid_settings_setint(settings, "synth.lock-memory", 0);
}

void setOutPath(JNIEnv *env, jstring out_path, fluid_settings_t *fluid_settings) {
    const char *outPath = env->GetStringUTFChars(out_path, nullptr);
    fluid_settings_setstr(fluid_settings, "audio.file.name", outPath);
}

void firstTimeSetupVariables() {
    settings = new_fluid_settings();
    synth = new_fluid_synth(settings);
    adriver = new_fluid_audio_driver(settings, synth);
}

void firstTimeSetupSoundFont(JNIEnv *env, jstring soundfont) {
    soundfontPath = env->GetStringUTFChars(soundfont, nullptr);
    fluid_synth_sfload(synth, soundfontPath, 1);
}