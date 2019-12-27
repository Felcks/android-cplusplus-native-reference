#ifndef AUTHHANDLER_H
#define AUTHHANDLER_H

#include <string>

typedef unsigned int u_int;

/**
 * An object that handles an authentication challenge.
 *
 * Whenever you need to perform an authentication challenge with the server, create a instance of this class an call @c requestAccessToken(). To retrieve the access token and its expiration time, use the associated getters.
 *
 * @code
 * AuthHandler handler(URL, KEY, USERNAME);
 * handler.requestAccessToken();
 *
 * std::string accessToken = handler->getAccessToken();
 * u_int expirationTime = handler->getExpirationTime();
 * @endcode
 *
 * @remark If the authentication fails the access token will be empty and is expiration time zero.
 *
 */
class AuthHandler final {
public:
    std::string baseURL;    ///< The base URL used on the authentication challenge.
    std::string uniqueKey;  ///< The unique identifier key used to perform the authentication.
    std::string username;   ///< The username used to perform the authentication.

    /**
     * Gets the access token returned from the authentication challenge.
     * @return The access token string.
     * @remark You should call this method only after requesting the access token through @c requestAccessToken().
     */
    std::string getAccessToken();

    /**
     * Gets the expiration time of the access token returned from the authentication challenge.
     * @return The expiration time, in seconds.
     * @remark You should call this method only after requesting the access token through @c requestAccessToken().
     */
    u_int getExpirationTime();

    /// Requests an access token from the service by performing an authentication challenge.
    void requestAccessToken();

    /**
     * Creates a new @c AuthHandler object.
     * @param t_baseURL The base URL used on the authentication challenge.
     * @param t_uniqueKey The unique identifier key used to perform the authentication.
     * @param t_username The username used to perform the authentication.
     */
    AuthHandler(std::string t_baseURL, std::string t_uniqueKey, std::string t_username)
            : baseURL(t_baseURL),
              uniqueKey(t_uniqueKey),
              username(t_username) {
    }

private:
    std::string m_accessToken;
    u_int m_expirationTime;
};

#endif  // AUTHHANDLER_H