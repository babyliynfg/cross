

#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "basics/CAObject.h"
#include <functional>
NS_CC_BEGIN

class CAHttpClient;
class CAHttpResponse;

class CC_DLL CAHttpRequest : public CAObject
{
public:
    
    typedef std::function<void(CAHttpClient* client, CAHttpResponse* response)> Callback;
    
    /** Use this enum type as param in setReqeustType(param) */
    enum class Type
    {
        Get = 0,
        Post,
        PostFile,
        Put,
        Delete,
        Unkown,
    };
    
    /** Constructor
     Because HttpRequest object will be used between UI thead and network thread,
     requestObj->autorelease() is forbidden to avoid crashes in CAAutoreleasePool
     new/retain/release still works, which means you need to release it manually
     Please refer to HttpRequestTest.cpp to find its usage
     */
    CAHttpRequest()
    : _requestType(Type::Unkown)
    , _pCallback(nullptr)
    {
        
    };
    
    /** Destructor */
    virtual ~CAHttpRequest()
    {
    };
    
    /** Override autorelease method to avoid developers to call it */
    CAObject* autorelease(void)
    {
        CCAssert(false, "HttpResponse is used between network thread and ui thread \
                 therefore, autorelease is forbidden here");
        return NULL;
    }
    
    // setter/getters for properties
    inline void setFileNameToPost(const std::string& fileName)
    {
        _fileNameToPost = fileName;
    }
    inline const char* getFileNameToPost()
    {
        return _fileNameToPost.c_str();
    }
    
    /** Required field for HttpRequest object before being sent.
     kHttpGet & kHttpPost is currently supported
     */
    inline void setRequestType(CAHttpRequest::Type type)
    {
        _requestType = type;
    };
    /** Get back the kHttpGet/Post/... enum value */
    inline CAHttpRequest::Type getRequestType()
    {
        return _requestType;
    };
    
    /** Required field for HttpRequest object before being sent.
     */
    inline void setUrl(const char* url)
    {
        _url = url;
    };
    /** Get back the setted url */
    inline const std::string& getUrl()
    {
        return _url;
    };
    
    /** Option field. You can set your post data here
     */
    inline void setRequestData(const char* buffer, unsigned int len)
    {
        _requestData.resize(len);
        memcpy(&_requestData[0], buffer, len);
    };
    /** Get the request data pointer back */
    inline char* getRequestData()
    {
        return (char*)_requestData.c_str();
    }
    /** Get the size of request data back */
    inline int getRequestDataSize()
    {
        return (int)_requestData.size();
    }
    
    /**
     * Set response callback function of HttpRequest object.
     * When response come back, we would call _pCallback to process response data.
     *
     * @param callback the Callback function.
     */
    inline void setResponseCallback(const CAHttpRequest::Callback& callback)
    {
        _pCallback = callback;
    }
    /**
     * Get ccHttpRequestCallback callback function.
     *
     * @return const ccHttpRequestCallback& ccHttpRequestCallback callback function.
     */
    inline const CAHttpRequest::Callback& getCallback() const
    {
        return _pCallback;
    }
    
    /** Set any custom headers **/
    inline void setHeaders(std::vector<std::string> pHeaders)
    {
        _headers = pHeaders;
    }
    
    /** Get custom headers **/
    inline std::vector<std::string> getHeaders()
    {
        return _headers;
    }
    
    inline void setThreadID(ssize_t threadID)
    {
        _threadID = threadID;
    };
    
    inline ssize_t getThreadID()
    {
        return _threadID;
    };
    
protected:
    // properties
    CAHttpRequest::Type             _requestType;  /// kHttpRequestGet, kHttpRequestPost or other enums
    std::string                     _url;          /// target url that this request is sent to
    std::string                     _requestData;  /// used for POST
    std::string                     _tag;          /// user defined tag, to identify different requests in response
    Callback                        _pCallback;      /// callbacks
    std::vector<std::string>        _headers;      /// custom http headers
	std::string                     _fileNameToPost;
    ssize_t                         _threadID;
};

NS_CC_END

#endif //__HTTP_REQUEST_H__
