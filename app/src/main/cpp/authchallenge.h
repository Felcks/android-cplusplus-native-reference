#ifndef AUTH_CHALLENGE_H
#define AUTH_CHALLENGE_H

#include <string>

#include "authhandler.h"

typedef unsigned int u_int;

/**
 * Performs an authentication challenge.
 * 
 * If the challenge succeeds, it passes back an access token and its expiration time. Otherwise, these parameters will be empty.
 *
 * @param [in] t_handler The @c AuthHandler object used to perform the challenge.
 * @param [out] __access_token The output access token string.
 * @param [out] __expiration_time The access token's expiration time, in seconds.
 */
void performAuthChallenge(AuthHandler t_handler, std::string *__access_token, u_int *__expiration_time);

#endif  // AUTH_CHALLENGE_H