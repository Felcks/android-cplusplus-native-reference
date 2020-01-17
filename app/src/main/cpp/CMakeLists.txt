# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        auth

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        auth.cpp

        ../../../../mfauthhandler/src/Authhandler.cpp
        ../../../../mfauthhandler/src/Authchallenge.cpp
        ../../../../mfauthhandler/libraries/crypto/sha256.cpp)

include_directories(
        ../../../../mfauthhandler/src/

        libs/curl/include
        libs/openssl/include
        libs/rapidjson/include)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

# find_library(log-lib log)

# This project uses prebuilt libraries for curl and openssl. The source code
# is available at https://github.com/leenjewel/openssl_for_ios_and_android

# Adds curl prebuilt library.

add_library(curl-lib
        STATIC IMPORTED)

set_target_properties(curl-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../../../libs/curl/lib/${ANDROID_ABI}/libcurl.a)

# Adds ssl prebuilt library.

add_library(ssl-lib
        STATIC IMPORTED)

set_target_properties(ssl-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../../../libs/openssl/lib/${ANDROID_ABI}/libssl.a)

# Adds crypto prebuilt library.

add_library(crypto-lib
        STATIC IMPORTED)

set_target_properties(crypto-lib
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../../../libs/openssl/lib/${ANDROID_ABI}/libcrypto.a)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        auth

        # Links the target library to the log library
        # included in the NDK.
        # ${log-lib}
        z log

        # Set external library dependencies.
        # The order on which each library is linked below
        # is important. Changing it may cause the project
        # to not build.
        curl-lib ssl-lib crypto-lib)