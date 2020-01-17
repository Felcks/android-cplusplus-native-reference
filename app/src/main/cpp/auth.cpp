#include <string>

#include "../../../../mfauthhandler/src/Authhandler.h"
#include "handle.h"

extern "C" JNIEXPORT void JNICALL
Java_com_mobfiq_auth_AuthHandler_initialize(JNIEnv *env, jobject obj, jstring t_base_url, jstring t_username, jstring t_unique_key) {
    std::string baseUrl     = std::string(env->GetStringUTFChars(t_base_url, nullptr));
    std::string uniqueKey   = std::string(env->GetStringUTFChars(t_unique_key, nullptr));
    std::string username    = std::string(env->GetStringUTFChars(t_username, nullptr));

    AuthHandler *handler = new AuthHandler(baseUrl, uniqueKey, username);
    setHandle(env, obj, handler);
}

extern "C" JNIEXPORT void JNICALL
Java_com_mobfiq_auth_AuthHandler_requestAccessToken(JNIEnv *env, jobject obj) {
    auto *handler = getHandle<AuthHandler>(env, obj);
    handler->requestAccessToken();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mobfiq_auth_AuthHandler_getAccessToken(JNIEnv *env, jobject obj) {
    auto *handler = getHandle<AuthHandler>(env, obj);
    return env->NewStringUTF((handler->getAccessToken()).c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_mobfiq_auth_AuthHandler_getExpirationTime(JNIEnv *env, jobject obj) {
    auto *handler = getHandle<AuthHandler>(env, obj);
    return handler->getExpirationTime();
}