package com.mobfiq.auth;

/**
 * An object that handles an authentication challenge.
 *
 * Whenever you need to perform an authentication challenge with the server, create a instance of this class an call {@code requestAccessToken()}. To retrieve the access token and its expiration time, use the corresponding getters.
 *
 * <pre>{@code
 * AuthHandler handler = new AuthHandler("...","...","...");
 * handler.requestAccessToken();
 *
 * String accessToken = handler.getAccessToken();
 * int expirationTime = handler.getExpirationTime();
 * }</pre>
 *
 * If the authentication fails, the access token and its expiration time will be {@code null}.
 */
public final class AuthHandler {

    /**
     * Creates a new {@code AuthHandler} object.
     * @param baseUrl   The base URL used on the authentication challenge.
     * @param username  The username used to perform the authentication.
     * @param uniqueKey The unique identifier key used to perform the authentication.
     */
    public AuthHandler(String baseUrl, String username, String uniqueKey) {
        initialize(baseUrl, username, uniqueKey);
    }

    /** Requests an access token from the service by performing an authentication challenge. */
    public native void requestAccessToken();

    /** The access token string, or an empty string if the authentication fails. */
    public native String getAccessToken();

    /** The expiration time, in seconds, or {@code 0} if the authentication fails. */
    public native int getExpirationTime();

    private long nativeHandle;  // Stores an instance of the native AuthHandler class.

    private native void initialize(String baseUrl, String username, String uniqueKey);

    static {
        System.loadLibrary("auth");
    }
}