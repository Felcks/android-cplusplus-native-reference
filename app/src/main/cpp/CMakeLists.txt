# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution)

add_library(teste_simples STATIC IMPORTED)
set_target_properties(teste_simples PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gmath/lib/${ANDROID_ABI}/teste_simples.a)

add_library(auth-libs SHARED auth-libs.cpp)

# biblioteca do Patrick para Autenticacao MobFiq
add_library(libauth STATIC IMPORTED)
set_target_properties(libauth PROPERTIES IMPORTED_LOCATION
        ${distribution_DIR}/gmath/lib/${ANDROID_ABI}/libauth.a)

# build application's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_include_directories(auth-libs PRIVATE ${distribution_DIR}/gmath/include)

target_link_libraries( # Specifies the target library.
        auth-libs
        # Links the target library to the log library
        # included in the NDK.
        android
        teste_simples
        libauth)