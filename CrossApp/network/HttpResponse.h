
#ifndef __HTTP_RESPONSE__
#define __HTTP_RESPONSE__

#include "network/HttpRequest.h"

/**
 * @addtogroup network
 * @{
 */

NS_CC_BEGIN

/**
 * @brief defines the object which users will receive at onHttpCompleted(sender, CAHttpResponse) callback.
 * Please refer to samples/TestCpp/Classes/ExtensionTest/NetworkTest/CAHttpClientTest.cpp as a sample.
 * @since v2.0.2.
 * @lua NA
 */
class CC_DLL CAHttpResponse : public CAObject
{
public:
    /**
     * Constructor, it's used by CAHttpClient internal, users don't need to create CAHttpResponse manually.
     * @param request the corresponding CAHttpRequest which leads to this response.
     */
    CAHttpResponse(CAHttpRequest* request)
    : _pHttpRequest(request)
    , _succeed(false)
    , _responseDataString("")
    {
        if (_pHttpRequest)
        {
            _pHttpRequest->retain();
        }
    }
    
    /**
     * Destructor, it will be called in CAHttpClient internal.
     * Users don't need to destruct CAHttpResponse object manually.
     */
    virtual ~CAHttpResponse()
    {
        if (_pHttpRequest)
        {
            _pHttpRequest->release();
        }
    }
    
    /**
     * Override autorelease method to prevent developers from calling it.
     * If this method is called , it would trigger CCASSERT.
     * @return cocos2d::Ref* always return nullptr.
     */
    CAObject* autorelease()
    {
        CCASSERT(false, "CAHttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return nullptr;
    }
    
    // getters, will be called by users
    
    /**
     * Get the corresponding CAHttpRequest object which leads to this response.
     * There's no paired setter for it, because it's already setted in class constructor
     * @return CAHttpRequest* the corresponding CAHttpRequest object which leads to this response.
     */
    inline CAHttpRequest* getHttpRequest() const
    {
        return _pHttpRequest;
    }
    
    /**
     * To see if the http request is returned successfully.
     * Although users can judge if (http response code = 200), we want an easier way.
     * If this getter returns false, you can call getResponseCode and getErrorBuffer to find more details.
     * @return bool the flag that represent whether the http request return successfully or not.
     */
    inline bool isSucceed() const
    {
        return _succeed;
    }
    
    /**
     * Get the http response data.
     * @return std::vector<char>* the pointer that point to the _responseData.
     */
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }
    
    /**
     * Get the response headers.
     * @return std::vector<char>* the pointer that point to the _responseHeader.
     */
    inline std::vector<char>* getResponseHeader()
    {
        return &_responseHeader;
    }
    
    /**
     * Get the http response code to judge whether response is successful or not.
     * I know that you want to see the _responseCode is 200.
     * If _responseCode is not 200, you should check the meaning for _responseCode by the net.
     * @return long the value of _responseCode
     */
    inline long getResponseCode() const
    {
        return _responseCode;
    }
    
    /**
     * Get the error buffer which will tell you more about the reason why http request failed.
     * @return const char* the pointer that point to _errorBuffer.
     */
    inline const char* getErrorBuffer() const
    {
        return _errorBuffer.c_str();
    }
    
    // setters, will be called by CAHttpClient
    // users should avoid invoking these methods
    
    
    /**
     * Set whether the http request is returned successfully or not,
     * This setter is mainly used in CAHttpClient, users mustn't set it directly
     * @param value the flag represent whether the http request is successful or not.
     */
    inline void setSucceed(bool value)
    {
        _succeed = value;
    }
    
    /**
     * Set the http response data buffer, it is used by CAHttpClient.
     * @param data the pointer point to the response data buffer.
     */
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }
    
    /**
     * Set the http response headers buffer, it is used by CAHttpClient.
     * @param data the pointer point to the response headers buffer.
     */
    inline void setResponseHeader(std::vector<char>* data)
    {
        _responseHeader = *data;
    }
    
    
    /**
     * Set the http response code.
     * @param value the http response code that represent whether the request is successful or not.
     */
    inline void setResponseCode(long value)
    {
        _responseCode = value;
    }
    
    
    /**
     * Set the error buffer which will tell you more the reason why http request failed.
     * @param value a string pointer that point to the reason.
     */
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    }
    
    /**
     * Set the response data by the string pointer and the defined size.
     * @param value a string pointer that point to response data buffer.
     * @param n the defined size that the response data buffer would be copied.
     */
    inline void setResponseDataString(const char* value, size_t n)
    {
        _responseDataString.clear();
        _responseDataString.assign(value, n);
    }
    
    /**
     * Get the string pointer that point to the response data.
     * @return const char* the string pointer that point to the response data.
     */
    inline const char* getResponseDataString() const
    {
        return _responseDataString.c_str();
    }
    
protected:
    bool initWithRequest(CAHttpRequest* request);
    
    // properties
    CAHttpRequest*        _pHttpRequest;  /// the corresponding CAHttpRequest pointer who leads to this response
    bool                _succeed;       /// to indicate if the http request is successful simply
    std::vector<char>   _responseData;  /// the returned raw data. You can also dump it as a string
    std::vector<char>   _responseHeader;  /// the returned raw header data. You can also dump it as a string
    long                _responseCode;    /// the status code returned from libcurl, e.g. 200, 404
    std::string         _errorBuffer;   /// if _responseCode != 200, please read _errorBuffer to find the reason
    std::string         _responseDataString; // the returned raw data. You can also dump it as a string
    
};

NS_CC_END

// end group
/// @}

#endif //__HTTP_RESPONSE_H__

