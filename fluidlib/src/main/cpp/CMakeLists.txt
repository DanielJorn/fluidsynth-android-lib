# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

# Declares and names the project.

project("beatemup")
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

# Create a variable fluidsynth_DIR to specify where the fluidsynth library is located.
set(fluidsynth_DIR ${CMAKE_CURRENT_SOURCE_DIR}/fluidsynth)

add_library(libc++_shared SHARED IMPORTED)
set_target_properties(libc++_shared PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libc++_shared.so)

add_library(libcharset SHARED IMPORTED)
set_target_properties(libcharset PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libcharset.so)

add_library(libffi SHARED IMPORTED)
set_target_properties(libffi PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libffi.so)

add_library(libFLAC SHARED IMPORTED)
set_target_properties(libFLAC PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libFLAC.so)

add_library(libfluidsynth SHARED IMPORTED)
set_target_properties(libfluidsynth PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libfluidsynth.so)

add_library(libfluidsynth-assetloader SHARED IMPORTED)
set_target_properties(libfluidsynth-assetloader PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libfluidsynth-assetloader.so)

add_library(libgio-2.0 SHARED IMPORTED)
set_target_properties(libgio-2.0 PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libgio-2.0.so)

add_library(libglib-2.0 SHARED IMPORTED)
set_target_properties(libglib-2.0 PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libglib-2.0.so)

add_library(libgmodule-2.0 SHARED IMPORTED)
set_target_properties(libgmodule-2.0 PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libgmodule-2.0.so)

add_library(libgobject-2.0 SHARED IMPORTED)
set_target_properties(libgobject-2.0 PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libgobject-2.0.so)

add_library(libgthread-2.0 SHARED IMPORTED)
set_target_properties(libgthread-2.0 PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libgthread-2.0.so)

add_library(libiconv SHARED IMPORTED)
set_target_properties(libiconv PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libiconv.so)

add_library(libintl SHARED IMPORTED)
set_target_properties(libintl PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libintl.so)

add_library(liboboe SHARED IMPORTED)
set_target_properties(liboboe PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/liboboe.so)

add_library(libogg SHARED IMPORTED)
set_target_properties(libogg PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libogg.so)

add_library(libsndfile SHARED IMPORTED)
set_target_properties(libsndfile PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libsndfile.so)

add_library(libvorbis SHARED IMPORTED)
set_target_properties(libvorbis PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libvorbis.so)

add_library(libvorbisenc SHARED IMPORTED)
set_target_properties(libvorbisenc PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libvorbisenc.so)

add_library(libvorbisfile SHARED IMPORTED)
set_target_properties(libvorbisfile PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libvorbisfile.so)

add_library(libz SHARED IMPORTED)
set_target_properties(libz PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/libz.so)

add_library(preloadable_libiconv SHARED IMPORTED)
set_target_properties(preloadable_libiconv PROPERTIES IMPORTED_LOCATION ${fluidsynth_DIR}/lib/${ANDROID_ABI}/preloadable_libiconv.so)

add_library(fluid-lib-android SHARED fluid-lib-android.cpp)

target_include_directories(fluid-lib-android PRIVATE ${fluidsynth_DIR}/include)

target_link_libraries(
        fluid-lib-android
        libc++_shared
        libcharset
        libffi
        libFLAC
        libfluidsynth
        libfluidsynth-assetloader
        libgio-2.0
        libglib-2.0
        libgmodule-2.0
        libgobject-2.0
        libgthread-2.0
        libiconv
        libintl
        liboboe
        libogg
        libsndfile
        libvorbis
        libvorbisenc
        libvorbisfile
        libz
        preloadable_libiconv
)