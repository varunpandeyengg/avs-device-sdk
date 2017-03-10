/*
 * AuthDelegateInterface.h
 *
 * Copyright 2016-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ALEXA_CLIENT_SDK_ACL_INCLUDE_ACL_AUTH_DELEGATE_INTERFACE_H_
#define ALEXA_CLIENT_SDK_ACL_INCLUDE_ACL_AUTH_DELEGATE_INTERFACE_H_

#include <memory>
#include <string>

#include "ACL/AuthObserverInterface.h"

namespace alexaClientSDK {
namespace acl {

/**
 * The AuthDelegateInterface is used to provide clients with valid LWA authroization
 * tokens. @see
 * https://developer.amazon.com/public/solutions/alexa/alexa-voice-service/content/avs-api-overview#authorization
 * Given an @c AuthDelegateInterface pointer, the client is expected to call @c getAuthToken() immediately before
 * making AVS requests. The returned value is passed in the HTTP/2 header of requests sent to AVS.
 * These authroization tokens may expire, so AuthDelegates also track the state of authorization (essentially,
 * whether an immediate call to @c getAuthToken() will return a token that is expected to be viable).  The client
 * may elect to receive callbacks when this state changes by calling @c setAuthObserver().  This allows the client
 * to avoid sending requests tha are doomed to fail because the authorization token has already expired.  This also
 * allows the client to know when authorization has been restored.
 */
class AuthDelegateInterface {
public:
    /**
     * Virtual destructor to assure proper cleanup of derived types.
     */
    virtual ~AuthDelegateInterface() = default;

    /**
     * Specify an object to observe changes to the authorization state of this AuthDelegate.
     * During the call to this setter the observers onAuthStateChange() method will be called
     * back with the current authorization state.
     *
     * @param observer The object to observe this authorization state of this AuthDelegate.
     */
    virtual void setAuthObserver(std::shared_ptr<AuthObserverInterface> observer) = 0;

    /**
     * Get the current LWA authoriation token.
     *
     * @return The current authorization token.  The returned value will be empty if an authorization token
     * has yet to be acquired or if the most recently acquired token has expired.
     */
    virtual std::string getAuthToken() = 0;
};

} // namespace acl
} // namespace alexaClientSDK

#endif // ALEXA_CLIENT_SDK_ACL_INCLUDE_ACL_AUTH_DELEGATE_INTERFACE_H_