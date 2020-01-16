#include "authchallenge.h"

std::string AuthHandler::getAccessToken() {
    return m_accessToken;
}

u_int AuthHandler::getExpirationTime() {
    return m_expirationTime;
}

void AuthHandler::requestAccessToken() {
    performAuthChallenge(*this, &m_accessToken, &m_expirationTime);
}