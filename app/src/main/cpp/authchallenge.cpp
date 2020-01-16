#include "authchallenge.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#if __has_include(<android/log.h>)
    #include <android/log.h>
    #define ANDROID_ENVIRONMENT
#endif

#include "../../../libs/curl/include/curl.h"
#include "../../../libs/rapidjson/include/document.h"

#include "sha256.h"

using namespace std;

size_t callback(const char *t_in, size_t t_size, size_t t_num, string *t_out) {
    const size_t totalBytes(t_size * t_num);
    t_out->append(t_in, totalBytes);
    return totalBytes;
}

string currentTimeISO8601() {
    time_t currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    stringstream stream;
    stream << put_time(gmtime(&currentTime), "%FT%H:%M");
    return stream.str();
}

void sha256(const BYTE t_data[], const size_t t_len, BYTE *t_buf) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, t_data, t_len);
    sha256_final(&ctx, t_buf);
}

void performAuthChallenge(AuthHandler t_handler, string *__access_token, u_int *__expiration_time) {
    *__access_token = "";
    *__expiration_time = 0;

    CURL *curl = curl_easy_init();
    CURLcode result;
    BYTE buf[SHA256_BLOCK_SIZE];

    if (curl) {
        stringstream composedKeyStream;
        composedKeyStream << t_handler.uniqueKey << currentTimeISO8601();

        const string __tmp__key = composedKeyStream.str();
        const char *keyBuf = __tmp__key.c_str();

        sha256((BYTE *) keyBuf, strlen(keyBuf), buf);

        stringstream hashStream;
        hashStream << hex << setfill('0');

        for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
            hashStream << setw(2) << static_cast<unsigned>(buf[i]);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        stringstream parametersStream;
        parametersStream << "username=" << t_handler.username << "&password=" << hashStream.str()
                         << "&grant_type=password";

        const string __tmp__params = parametersStream.str();
        const char *parameters = __tmp__params.c_str();

        long httpStatusCode(0);
        string httpResponseData;

#if defined(PROXY_IP_ADDRESS) && defined(PROXY_PORT)
        curl_easy_setopt(curl, CURLOPT_PROXY, PROXY_IP_ADDRESS);
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, PROXY_PORT);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
#endif

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

        curl_easy_setopt(curl, CURLOPT_URL, t_handler.baseURL.c_str());
        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, parameters);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpResponseData);

        result = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpStatusCode);

        if (result == CURLE_OK && httpStatusCode == 200) {
            rapidjson::Document document;
            document.Parse(httpResponseData.c_str());

            rapidjson::Value &accessToken = document["access_token"];
            rapidjson::Value &expirationTime = document["expires_in"];

            *__access_token = accessToken.GetString();
            *__expiration_time = expirationTime.GetInt();
        } else {
#if defined(ANDROID_ENVIRONMENT)
            __android_log_print(ANDROID_LOG_INFO, "AUTH","Request failed. Status code: %ld. Error: %s\n", httpStatusCode, curl_easy_strerror(result));
#else
            fprintf(stderr, "Request failed. Status code: %ld. Error: %s\n", httpStatusCode, curl_easy_strerror(result));
#endif
        }

        curl_easy_cleanup(curl);
    }
}