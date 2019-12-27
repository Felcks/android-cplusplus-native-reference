/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <android/log.h>
#include "teste_simples.h"
#include <string>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   app/src/main/java/com/example/hellolibs/MainActivity.java
 */

extern "C" JNIEXPORT jint JNICALL
Java_com_example_autenticacao_MainActivity_intFromJNI() {
    return printazero();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_autenticacao_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello Danilo C++";
    return env->NewStringUTF(hello.c_str());
}


//    // Just for simplicity, we do this right away; correct way would do it in
//    // another thread...
//    auto ticks = GetTicks();
//
//    for (auto exp = 0; exp < 32; ++exp) {
//        volatile unsigned val = gpower(exp);
//        (void) val;  // to silence compiler warning
//    }
//    ticks = GetTicks() - ticks;
//
//    LOGI("calculation time: %" PRIu64, ticks);
//
//    return env->NewStringUTF("Hello from JNI LIBS!");
//}
