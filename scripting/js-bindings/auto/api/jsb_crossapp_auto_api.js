/**
 * @module crossapp
 */
var ca = ca || {};

/**
 * @class CAObject
 */
ca.CAObject = {

/**
 * @method getUID
 * @return {unsigned int}
 */
getUID : function (
)
{
    return 0;
},

/**
 * @method setUserObject
 * @param {ca.CAObject} arg0
 */
setUserObject : function (
caobject 
)
{
},

/**
 * @method getUserObject
 * @return {ca.CAObject}
 */
getUserObject : function (
)
{
    return ca.CAObject;
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method isEqual
 * @param {ca.CAObject} arg0
 * @return {bool}
 */
isEqual : function (
caobject 
)
{
    return false;
},

/**
 * @method isSingleReference
 * @return {bool}
 */
isSingleReference : function (
)
{
    return false;
},

/**
 * @method autorelease
 * @return {ca.CAObject}
 */
autorelease : function (
)
{
    return ca.CAObject;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setTextTag
 * @param {String} arg0
 */
setTextTag : function (
str 
)
{
},

/**
 * @method setTag
 * @param {int} arg0
 */
setTag : function (
int 
)
{
},

/**
 * @method release
 */
release : function (
)
{
},

/**
 * @method retain
 * @return {ca.CAObject}
 */
retain : function (
)
{
    return ca.CAObject;
},

/**
 * @method getTag
 * @return {int}
 */
getTag : function (
)
{
    return 0;
},

/**
 * @method retainCount
 * @return {unsigned int}
 */
retainCount : function (
)
{
    return 0;
},

/**
 * @method getStrID
 * @return {String}
 */
getStrID : function (
)
{
    return ;
},

/**
 * @method getTextTag
 * @return {String}
 */
getTextTag : function (
)
{
    return ;
},

/**
 * @method CAObject
 * @constructor
 */
CAObject : function (
)
{
},

};

/**
 * @class CAScheduler
 */
ca.CAScheduler = {

/**
 * @method setTimeScale
 * @param {float} arg0
 */
setTimeScale : function (
float 
)
{
},

/**
 * @method isScheduled
 * @param {String} arg0
 * @param {void} arg1
 * @return {bool}
 */
isScheduled : function (
str, 
void 
)
{
    return false;
},

/**
 * @method unschedule
 * @param {String} arg0
 * @param {void} arg1
 */
unschedule : function (
str, 
void 
)
{
},

/**
 * @method scheduleOnce
 * @param {function} arg0
 * @param {String} arg1
 * @param {void} arg2
 * @param {float} arg3
 * @param {bool} arg4
 */
scheduleOnce : function (
func, 
str, 
void, 
float, 
bool 
)
{
},

/**
 * @method unscheduleAllForTarget
 * @param {void} arg0
 */
unscheduleAllForTarget : function (
void 
)
{
},

/**
 * @method resumeAll
 */
resumeAll : function (
)
{
},

/**
 * @method unscheduleUpdate
 * @param {void} arg0
 */
unscheduleUpdate : function (
void 
)
{
},

/**
 * @method resumeAllTargetsWithMinPriority
 * @param {int} arg0
 */
resumeAllTargetsWithMinPriority : function (
int 
)
{
},

/**
 * @method pauseAll
 */
pauseAll : function (
)
{
},

/**
 * @method scheduleScriptFunc
 * @param {unsigned int} arg0
 * @param {float} arg1
 * @param {bool} arg2
 * @return {unsigned int}
 */
scheduleScriptFunc : function (
int, 
float, 
bool 
)
{
    return 0;
},

/**
 * @method schedule
* @param {function|function} func
* @param {String|String} str
* @param {void|void} void
* @param {float|float} float
* @param {unsigned int|bool} int
* @param {float} float
* @param {bool} bool
*/
schedule : function(
func,
str,
void,
float,
int,
float,
bool 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method resumeTarget
 * @param {void} arg0
 */
resumeTarget : function (
void 
)
{
},

/**
 * @method unscheduleScriptEntry
 * @param {unsigned int} arg0
 */
unscheduleScriptEntry : function (
int 
)
{
},

/**
 * @method unscheduleAll
 */
unscheduleAll : function (
)
{
},

/**
 * @method pauseTarget
 * @param {void} arg0
 */
pauseTarget : function (
void 
)
{
},

/**
 * @method performFunctionInUIThread
 * @param {function} arg0
 */
performFunctionInUIThread : function (
func 
)
{
},

/**
 * @method getTimeScale
 * @return {float}
 */
getTimeScale : function (
)
{
    return 0;
},

/**
 * @method unscheduleAllWithMinPriority
 * @param {int} arg0
 */
unscheduleAllWithMinPriority : function (
int 
)
{
},

/**
 * @method isTargetPaused
 * @param {void} arg0
 * @return {bool}
 */
isTargetPaused : function (
void 
)
{
    return false;
},

/**
 * @method scheduleUpdate
 * @param {ca.CAObject} arg0
 * @param {int} arg1
 * @param {bool} arg2
 */
scheduleUpdate : function (
caobject, 
int, 
bool 
)
{
},

/**
 * @method getScheduler
 * @return {ca.CAScheduler}
 */
getScheduler : function (
)
{
    return ca.CAScheduler;
},

};

/**
 * @class CAData
 */
ca.CAData = {

/**
 * @method getLength
 * @return {int}
 */
getLength : function (
)
{
    return 0;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method isNull
 * @return {bool}
 */
isNull : function (
)
{
    return false;
},

/**
 * @method toString
 * @return {String}
 */
toString : function (
)
{
    return ;
},

/**
 * @method fastSet
 * @param {unsigned char} arg0
 * @param {int} arg1
 */
fastSet : function (
char, 
int 
)
{
},

/**
 * @method copyString
 * @param {String} arg0
 */
copyString : function (
str 
)
{
},

/**
 * @method copy
 * @param {unsigned char} arg0
 * @param {int} arg1
 */
copy : function (
char, 
int 
)
{
},

/**
 * @method getBytes
 * @return {unsigned char}
 */
getBytes : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ca.CAData}
 */
create : function (
)
{
    return ca.CAData;
},

/**
 * @method CAData
 * @constructor
 */
CAData : function (
)
{
},

};

/**
 * @class CAFont
 */
ca.CAFont = {

/**
 * @method CAFont
 * @constructor
 */
CAFont : function (
)
{
},

};

/**
 * @class CAImage
 */
ca.CAImage = {

/**
 * @method getShaderProgram
 * @return {ca.GLProgram}
 */
getShaderProgram : function (
)
{
    return ca.GLProgram;
},

/**
 * @method premultipliedImageData
 */
premultipliedImageData : function (
)
{
},

/**
 * @method getMaxT
 * @return {float}
 */
getMaxT : function (
)
{
    return 0;
},

/**
 * @method stringForFormat
 * @return {char}
 */
stringForFormat : function (
)
{
    return 0;
},

/**
 * @method setMaxS
 * @param {float} arg0
 */
setMaxS : function (
float 
)
{
},

/**
 * @method setShaderProgram
 * @param {ca.GLProgram} arg0
 */
setShaderProgram : function (
glprogram 
)
{
},

/**
 * @method getMaxS
 * @return {float}
 */
getMaxS : function (
)
{
    return 0;
},

/**
 * @method getAspectRatio
 * @return {float}
 */
getAspectRatio : function (
)
{
    return 0;
},

/**
 * @method hasPremultipliedAlpha
 * @return {bool}
 */
hasPremultipliedAlpha : function (
)
{
    return false;
},

/**
 * @method getPixelsWide
 * @return {unsigned int}
 */
getPixelsWide : function (
)
{
    return 0;
},

/**
 * @method getPixelsHigh
 * @return {unsigned int}
 */
getPixelsHigh : function (
)
{
    return 0;
},

/**
 * @method freeName
 */
freeName : function (
)
{
},

/**
 * @method isTiff
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {bool}
 */
isTiff : function (
char, 
long 
)
{
    return false;
},

/**
 * @method bitsPerPixelForFormat
* @param {ca.CAImage::PixelFormat} pixelformat
* @return {unsigned int|unsigned int}
*/
bitsPerPixelForFormat : function(
pixelformat 
)
{
    return 0;
},

/**
 * @method getName
 * @return {unsigned int}
 */
getName : function (
)
{
    return 0;
},

/**
 * @method getGifImageIndex
 * @return {unsigned int}
 */
getGifImageIndex : function (
)
{
    return 0;
},

/**
 * @method setMaxT
 * @param {float} arg0
 */
setMaxT : function (
float 
)
{
},

/**
 * @method initWithImageFile
 * @param {String} arg0
 * @param {bool} arg1
 * @return {bool}
 */
initWithImageFile : function (
str, 
bool 
)
{
    return false;
},

/**
 * @method getBitPerPixel
 * @return {int}
 */
getBitPerPixel : function (
)
{
    return 0;
},

/**
 * @method getGifImageCounts
 * @return {unsigned int}
 */
getGifImageCounts : function (
)
{
    return 0;
},

/**
 * @method getContentSize
 * @return {size_object}
 */
getContentSize : function (
)
{
    return ca.DSize;
},

/**
 * @method getData
 * @return {ca.CAData}
 */
getData : function (
)
{
    return ca.CAData;
},

/**
 * @method setAliasTexParameters
 */
setAliasTexParameters : function (
)
{
},

/**
 * @method isPng
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {bool}
 */
isPng : function (
char, 
long 
)
{
    return false;
},

/**
 * @method setAntiAliasTexParameters
 */
setAntiAliasTexParameters : function (
)
{
},

/**
 * @method generateMipmap
 */
generateMipmap : function (
)
{
},

/**
 * @method saveToFile
 * @param {String} arg0
 * @param {bool} arg1
 * @return {bool}
 */
saveToFile : function (
str, 
bool 
)
{
    return false;
},

/**
 * @method description
 * @return {char}
 */
description : function (
)
{
    return 0;
},

/**
 * @method isMonochrome
 * @return {bool}
 */
isMonochrome : function (
)
{
    return false;
},

/**
 * @method initWithImageData
 * @param {ca.CAData} arg0
 * @param {bool} arg1
 * @return {bool}
 */
initWithImageData : function (
cadata, 
bool 
)
{
    return false;
},

/**
 * @method getPixelFormat
 * @return {ca.CAImage::PixelFormat}
 */
getPixelFormat : function (
)
{
    return 0;
},

/**
 * @method hasAlpha
 * @return {bool}
 */
hasAlpha : function (
)
{
    return false;
},

/**
 * @method isEtc
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {bool}
 */
isEtc : function (
char, 
long 
)
{
    return false;
},

/**
 * @method isWebp
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {bool}
 */
isWebp : function (
char, 
long 
)
{
    return false;
},

/**
 * @method updateGifImageWithIndex
 * @param {unsigned int} arg0
 */
updateGifImageWithIndex : function (
int 
)
{
},

/**
 * @method copy
 * @return {ca.CAImage}
 */
copy : function (
)
{
    return ca.CAImage;
},

/**
 * @method getImageFileType
 * @return {char}
 */
getImageFileType : function (
)
{
    return 0;
},

/**
 * @method initWithRawData
 * @param {ca.CAData} arg0
 * @param {ca.CAImage::PixelFormat} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @return {bool}
 */
initWithRawData : function (
cadata, 
pixelformat, 
int, 
int 
)
{
    return false;
},

/**
 * @method repremultipliedImageData
 */
repremultipliedImageData : function (
)
{
},

/**
 * @method detectFormat
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {ca.CAImage::Format}
 */
detectFormat : function (
char, 
long 
)
{
    return 0;
},

/**
 * @method hasMipmaps
 * @return {bool}
 */
hasMipmaps : function (
)
{
    return false;
},

/**
 * @method isCompressed
 * @return {bool}
 */
isCompressed : function (
)
{
    return false;
},

/**
 * @method isJpg
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {bool}
 */
isJpg : function (
char, 
long 
)
{
    return false;
},

/**
 * @method isGif
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @return {bool}
 */
isGif : function (
char, 
long 
)
{
    return false;
},

/**
 * @method purgeCAImage
 */
purgeCAImage : function (
)
{
},

/**
 * @method scaleToNewImageWithImage
* @param {ca.CAImage|ca.CAImage} caimage
* @param {float|size_object} float
* @param {float} float
* @return {ca.CAImage|ca.CAImage}
*/
scaleToNewImageWithImage : function(
caimage,
float,
float 
)
{
    return ca.CAImage;
},

/**
 * @method getStringWidth
 * @param {char} arg0
 * @param {float} arg1
 * @param {String} arg2
 * @return {int}
 */
getStringWidth : function (
char, 
float, 
str 
)
{
    return 0;
},

/**
 * @method CC_SHADOW_LEFT_IMAGE
 * @return {ca.CAImage}
 */
CC_SHADOW_LEFT_IMAGE : function (
)
{
    return ca.CAImage;
},

/**
 * @method getFontHeight
 * @param {char} arg0
 * @param {float} arg1
 * @return {int}
 */
getFontHeight : function (
char, 
float 
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CAImage}
 */
create : function (
str 
)
{
    return ca.CAImage;
},

/**
 * @method createWithRawData
 * @param {ca.CAData} arg0
 * @param {ca.CAImage::PixelFormat} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @param {String} arg4
 * @return {ca.CAImage}
 */
createWithRawData : function (
cadata, 
pixelformat, 
int, 
int, 
str 
)
{
    return ca.CAImage;
},

/**
 * @method createWithImageDataNoCache
 * @param {ca.CAData} arg0
 * @return {ca.CAImage}
 */
createWithImageDataNoCache : function (
cadata 
)
{
    return ca.CAImage;
},

/**
 * @method reloadAllImages
 */
reloadAllImages : function (
)
{
},

/**
 * @method createWithImageData
 * @param {ca.CAData} arg0
 * @param {String} arg1
 * @return {ca.CAImage}
 */
createWithImageData : function (
cadata, 
str 
)
{
    return ca.CAImage;
},

/**
 * @method getStringHeight
 * @param {char} arg0
 * @param {float} arg1
 * @param {String} arg2
 * @param {float} arg3
 * @param {int} arg4
 * @param {bool} arg5
 * @return {int}
 */
getStringHeight : function (
char, 
float, 
str, 
float, 
int, 
bool 
)
{
    return 0;
},

/**
 * @method generateMipmapsWithImage
 * @param {ca.CAImage} arg0
 * @return {ca.CAImage}
 */
generateMipmapsWithImage : function (
caimage 
)
{
    return ca.CAImage;
},

/**
 * @method CC_SHADOW_TOP_IMAGE
 * @return {ca.CAImage}
 */
CC_SHADOW_TOP_IMAGE : function (
)
{
    return ca.CAImage;
},

/**
 * @method CC_SHADOW_BOTTOM_IMAGE
 * @return {ca.CAImage}
 */
CC_SHADOW_BOTTOM_IMAGE : function (
)
{
    return ca.CAImage;
},

/**
 * @method CC_WHITE_IMAGE
 * @return {ca.CAImage}
 */
CC_WHITE_IMAGE : function (
)
{
    return ca.CAImage;
},

/**
 * @method createWithRawDataNoCache
 * @param {ca.CAData} arg0
 * @param {ca.CAImage::PixelFormat} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @return {ca.CAImage}
 */
createWithRawDataNoCache : function (
cadata, 
pixelformat, 
int, 
int 
)
{
    return ca.CAImage;
},

/**
 * @method CC_SHADOW_RIGHT_IMAGE
 * @return {ca.CAImage}
 */
CC_SHADOW_RIGHT_IMAGE : function (
)
{
    return ca.CAImage;
},

/**
 * @method createWithString
 * @param {String} arg0
 * @param {font_object} arg1
 * @param {size_object} arg2
 * @param {ca.CATextAlignment} arg3
 * @return {ca.CAImage}
 */
createWithString : function (
str, 
cafont, 
dsize, 
catextalignment 
)
{
    return ca.CAImage;
},

/**
 * @method CAImage
 * @constructor
 */
CAImage : function (
)
{
},

};

/**
 * @class CATouch
 */
ca.CATouch = {

/**
 * @method getLocation
 * @return {point_object}
 */
getLocation : function (
)
{
    return ca.DPoint;
},

/**
 * @method getDelta
 * @return {point_object}
 */
getDelta : function (
)
{
    return ca.DPoint;
},

/**
 * @method getStartLocation
 * @return {point_object}
 */
getStartLocation : function (
)
{
    return ca.DPoint;
},

/**
 * @method getID
 * @return {int}
 */
getID : function (
)
{
    return 0;
},

/**
 * @method isDelta
 * @return {bool}
 */
isDelta : function (
)
{
    return false;
},

/**
 * @method setTouchInfo
 * @param {int} arg0
 * @param {float} arg1
 * @param {float} arg2
 */
setTouchInfo : function (
int, 
float, 
float 
)
{
},

/**
 * @method getDeltaFromAToZ
 * @return {point_object}
 */
getDeltaFromAToZ : function (
)
{
    return ca.DPoint;
},

/**
 * @method getPreviousLocation
 * @return {point_object}
 */
getPreviousLocation : function (
)
{
    return ca.DPoint;
},

/**
 * @method CATouch
 * @constructor
 */
CATouch : function (
)
{
},

};

/**
 * @class CAEvent
 */
ca.CAEvent = {

/**
 * @method getEventType
 * @return {ca.EventType}
 */
getEventType : function (
)
{
    return 0;
},

/**
 * @method setEventType
 * @param {ca.EventType} arg0
 */
setEventType : function (
eventtype 
)
{
},

/**
 * @method CAEvent
 * @constructor
 */
CAEvent : function (
)
{
},

};

/**
 * @class CAResponder
 */
ca.CAResponder = {

/**
 * @method setReachBoundaryHandOverToSuperview
 * @param {bool} arg0
 */
setReachBoundaryHandOverToSuperview : function (
bool 
)
{
},

/**
 * @method setMouseScrollWheelEnabled
 * @param {bool} arg0
 */
setMouseScrollWheelEnabled : function (
bool 
)
{
},

/**
 * @method setMouseMovedEnabled
 * @param {bool} arg0
 */
setMouseMovedEnabled : function (
bool 
)
{
},

/**
 * @method setMouseMovedOutSideCallback
 * @param {function} arg0
 */
setMouseMovedOutSideCallback : function (
func 
)
{
},

/**
 * @method isScrollEnabled
 * @return {bool}
 */
isScrollEnabled : function (
)
{
    return false;
},

/**
 * @method isHaveNextResponder
 * @return {bool}
 */
isHaveNextResponder : function (
)
{
    return false;
},

/**
 * @method getMouseScrollWheelCallback
 * @return {function}
 */
getMouseScrollWheelCallback : function (
)
{
    return std::function<void (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method getMouseMovedOutSideCallback
 * @return {function}
 */
getMouseMovedOutSideCallback : function (
)
{
    return std::function<void (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method getTouchEndedCallback
 * @return {function}
 */
getTouchEndedCallback : function (
)
{
    return std::function<void (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method setHorizontalScrollEnabled
 * @param {bool} arg0
 */
setHorizontalScrollEnabled : function (
bool 
)
{
},

/**
 * @method isVerticalScrollEnabled
 * @return {bool}
 */
isVerticalScrollEnabled : function (
)
{
    return false;
},

/**
 * @method setPriorityScroll
 * @param {bool} arg0
 */
setPriorityScroll : function (
bool 
)
{
},

/**
 * @method isFirstResponder
 * @return {bool}
 */
isFirstResponder : function (
)
{
    return false;
},

/**
 * @method setTouchMovedCallback
 * @param {function} arg0
 */
setTouchMovedCallback : function (
func 
)
{
},

/**
 * @method isTouchEnabled
 * @return {bool}
 */
isTouchEnabled : function (
)
{
    return false;
},

/**
 * @method getTouchBeganCallback
 * @return {function}
 */
getTouchBeganCallback : function (
)
{
    return std::function<bool (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method setTouchEnabled
 * @param {bool} arg0
 */
setTouchEnabled : function (
bool 
)
{
},

/**
 * @method setScrollEnabled
 * @param {bool} arg0
 */
setScrollEnabled : function (
bool 
)
{
},

/**
 * @method getTouches
 * @return {Array}
 */
getTouches : function (
)
{
    return new Array();
},

/**
 * @method getMouseMovedCallback
 * @return {function}
 */
getMouseMovedCallback : function (
)
{
    return std::function<void (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method setTouchBeganCallback
 * @param {function} arg0
 */
setTouchBeganCallback : function (
func 
)
{
},

/**
 * @method isPriorityScroll
 * @return {bool}
 */
isPriorityScroll : function (
)
{
    return false;
},

/**
 * @method isHorizontalScrollEnabled
 * @return {bool}
 */
isHorizontalScrollEnabled : function (
)
{
    return false;
},

/**
 * @method setVerticalScrollEnabled
 * @param {bool} arg0
 */
setVerticalScrollEnabled : function (
bool 
)
{
},

/**
 * @method setHaveNextResponder
 * @param {bool} arg0
 */
setHaveNextResponder : function (
bool 
)
{
},

/**
 * @method nextResponder
 * @return {ca.CAResponder}
 */
nextResponder : function (
)
{
    return ca.CAResponder;
},

/**
 * @method isReachBoundaryRight
 * @return {bool}
 */
isReachBoundaryRight : function (
)
{
    return false;
},

/**
 * @method isReachBoundaryDown
 * @return {bool}
 */
isReachBoundaryDown : function (
)
{
    return false;
},

/**
 * @method setMultipleTouchEnabled
 * @param {bool} arg0
 */
setMultipleTouchEnabled : function (
bool 
)
{
},

/**
 * @method isTouchEventScrollHandOverToSuperview
 * @return {bool}
 */
isTouchEventScrollHandOverToSuperview : function (
)
{
    return false;
},

/**
 * @method isReachBoundaryHandOverToSuperview
 * @return {bool}
 */
isReachBoundaryHandOverToSuperview : function (
)
{
    return false;
},

/**
 * @method setTouchEndedCallback
 * @param {function} arg0
 */
setTouchEndedCallback : function (
func 
)
{
},

/**
 * @method isReachBoundaryUp
 * @return {bool}
 */
isReachBoundaryUp : function (
)
{
    return false;
},

/**
 * @method setMouseMovedCallback
 * @param {function} arg0
 */
setMouseMovedCallback : function (
func 
)
{
},

/**
 * @method isReachBoundaryLeft
 * @return {bool}
 */
isReachBoundaryLeft : function (
)
{
    return false;
},

/**
 * @method getScrollRunning
 * @return {bool}
 */
getScrollRunning : function (
)
{
    return false;
},

/**
 * @method setMouseScrollWheelCallback
 * @param {function} arg0
 */
setMouseScrollWheelCallback : function (
func 
)
{
},

/**
 * @method isMouseScrollWheelEnabled
 * @return {bool}
 */
isMouseScrollWheelEnabled : function (
)
{
    return false;
},

/**
 * @method resignFirstResponder
 * @return {bool}
 */
resignFirstResponder : function (
)
{
    return false;
},

/**
 * @method getTouchMovedCallback
 * @return {function}
 */
getTouchMovedCallback : function (
)
{
    return std::function<void (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method setTouchEventScrollHandOverToSuperview
 * @param {bool} arg0
 */
setTouchEventScrollHandOverToSuperview : function (
bool 
)
{
},

/**
 * @method isMouseMovedEnabled
 * @return {bool}
 */
isMouseMovedEnabled : function (
)
{
    return false;
},

/**
 * @method becomeFirstResponder
 * @return {bool}
 */
becomeFirstResponder : function (
)
{
    return false;
},

/**
 * @method isMultipleTouchEnabled
 * @return {bool}
 */
isMultipleTouchEnabled : function (
)
{
    return false;
},

/**
 * @method getTouchCancelledCallback
 * @return {function}
 */
getTouchCancelledCallback : function (
)
{
    return std::function<void (CrossApp::CATouch , CrossApp::CAEvent )>;
},

/**
 * @method getZLevel
 * @return {unsigned long}
 */
getZLevel : function (
)
{
    return 0;
},

/**
 * @method setTouchCancelledCallback
 * @param {function} arg0
 */
setTouchCancelledCallback : function (
func 
)
{
},

/**
 * @method CAResponder
 * @constructor
 */
CAResponder : function (
)
{
},

};

/**
 * @class CAView
 */
ca.CAView = {

/**
 * @method removeFromSuperview
 */
removeFromSuperview : function (
)
{
},

/**
 * @method enabledTopShadow
 * @param {bool} arg0
 */
enabledTopShadow : function (
bool 
)
{
},

/**
 * @method setLayout
 * @param {layout_object} arg0
 */
setLayout : function (
dlayout 
)
{
},

/**
 * @method setOpacityModifyRGB
 * @param {bool} arg0
 */
setOpacityModifyRGB : function (
bool 
)
{
},

/**
 * @method getSuperview
 * @return {ca.CAView}
 */
getSuperview : function (
)
{
    return ca.CAView;
},

/**
 * @method getSubviewByTag
 * @param {int} arg0
 * @return {ca.CAView}
 */
getSubviewByTag : function (
int 
)
{
    return ca.CAView;
},

/**
 * @method setOnExitCallback
 * @param {function} arg0
 */
setOnExitCallback : function (
func 
)
{
},

/**
 * @method sortAllSubviews
 */
sortAllSubviews : function (
)
{
},

/**
 * @method copy
 * @return {ca.CAView}
 */
copy : function (
)
{
    return ca.CAView;
},

/**
 * @method isOpacityModifyRGB
 * @return {bool}
 */
isOpacityModifyRGB : function (
)
{
    return false;
},

/**
 * @method getCGNode
 * @return {ca.CGNode}
 */
getCGNode : function (
)
{
    return ca.CGNode;
},

/**
 * @method updateDisplayedAlpha
 * @param {float} arg0
 */
updateDisplayedAlpha : function (
float 
)
{
},

/**
 * @method setCGNode
 * @param {ca.CGNode} arg0
 */
setCGNode : function (
cgnode 
)
{
},

/**
 * @method isFlipX
 * @return {bool}
 */
isFlipX : function (
)
{
    return false;
},

/**
 * @method isFlipY
 * @return {bool}
 */
isFlipY : function (
)
{
    return false;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setRotation
 * @param {int} arg0
 */
setRotation : function (
int 
)
{
},

/**
 * @method getWorldToViewAffineTransform
 * @return {ca.AffineTransform}
 */
getWorldToViewAffineTransform : function (
)
{
    return ca.AffineTransform;
},

/**
 * @method setZOrder
 * @param {int} arg0
 */
setZOrder : function (
int 
)
{
},

/**
 * @method setScaleY
 * @param {float} arg0
 */
setScaleY : function (
float 
)
{
},

/**
 * @method setScaleX
 * @param {float} arg0
 */
setScaleX : function (
float 
)
{
},

/**
 * @method removeSubviewByTag
 * @param {int} arg0
 */
removeSubviewByTag : function (
int 
)
{
},

/**
 * @method visitEve
 */
visitEve : function (
)
{
},

/**
 * @method setCenter
 * @param {rect_object} arg0
 */
setCenter : function (
drect 
)
{
},

/**
 * @method getSuperviewToViewAffineTransform
 * @return {ca.AffineTransform}
 */
getSuperviewToViewAffineTransform : function (
)
{
    return ca.AffineTransform;
},

/**
 * @method setonEnterTransitionDidFinishCallback
 * @param {function} arg0
 */
setonEnterTransitionDidFinishCallback : function (
func 
)
{
},

/**
 * @method getTag
 * @return {int}
 */
getTag : function (
)
{
    return 0;
},

/**
 * @method getonEnterTransitionDidFinishCallback
 * @return {function}
 */
getonEnterTransitionDidFinishCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method getViewToWorldTransform
 * @return {ca.Mat4}
 */
getViewToWorldTransform : function (
)
{
    return ca.Mat4;
},

/**
 * @method onExit
 */
onExit : function (
)
{
},

/**
 * @method setSuperview
 * @param {ca.CAView} arg0
 */
setSuperview : function (
caview 
)
{
},

/**
 * @method setRotationX
 * @param {int} arg0
 */
setRotationX : function (
int 
)
{
},

/**
 * @method getAlpha
 * @return {float}
 */
getAlpha : function (
)
{
    return 0;
},

/**
 * @method setSkewX
 * @param {float} arg0
 */
setSkewX : function (
float 
)
{
},

/**
 * @method setSkewY
 * @param {float} arg0
 */
setSkewY : function (
float 
)
{
},

/**
 * @method setOnEnterCallback
 * @param {function} arg0
 */
setOnEnterCallback : function (
func 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method getLayout
 * @return {layout_object}
 */
getLayout : function (
)
{
    return ca.DLayout;
},

/**
 * @method setonExitTransitionDidStartCallback
 * @param {function} arg0
 */
setonExitTransitionDidStartCallback : function (
func 
)
{
},

/**
 * @method removeAllSubviews
 */
removeAllSubviews : function (
)
{
},

/**
 * @method reViewlayout
 * @param {size_object} arg0
 * @param {bool} arg1
 */
reViewlayout : function (
dsize, 
bool 
)
{
},

/**
 * @method getSubviewByTextTag
 * @param {String} arg0
 * @return {ca.CAView}
 */
getSubviewByTextTag : function (
str 
)
{
    return ca.CAView;
},

/**
 * @method removeSubviewByTextTag
 * @param {String} arg0
 */
removeSubviewByTextTag : function (
str 
)
{
},

/**
 * @method getonExitTransitionDidStartCallback
 * @return {function}
 */
getonExitTransitionDidStartCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method enabledLeftShadow
 * @param {bool} arg0
 */
enabledLeftShadow : function (
bool 
)
{
},

/**
 * @method getFrame
 * @return {rect_object}
 */
getFrame : function (
)
{
    return ca.DRect;
},

/**
 * @method getImageRect
 * @return {rect_object}
 */
getImageRect : function (
)
{
    return ca.DRect;
},

/**
 * @method initWithLayout
 * @param {layout_object} arg0
 * @return {bool}
 */
initWithLayout : function (
dlayout 
)
{
    return false;
},

/**
 * @method getOnEnterCallback
 * @return {function}
 */
getOnEnterCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method enabledBottomShadow
 * @param {bool} arg0
 */
enabledBottomShadow : function (
bool 
)
{
},

/**
 * @method getViewToWorldAffineTransform
 * @return {ca.AffineTransform}
 */
getViewToWorldAffineTransform : function (
)
{
    return ca.AffineTransform;
},

/**
 * @method getPointZ
 * @return {float}
 */
getPointZ : function (
)
{
    return 0;
},

/**
 * @method getLayoutType
 * @return {int}
 */
getLayoutType : function (
)
{
    return 0;
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method getFrameOrigin
 * @return {point_object}
 */
getFrameOrigin : function (
)
{
    return ca.DPoint;
},

/**
 * @method setCameraMask
 * @param {unsigned short} arg0
 * @param {bool} arg1
 */
setCameraMask : function (
short, 
bool 
)
{
},

/**
 * @method isImageRectRotated
 * @return {bool}
 */
isImageRectRotated : function (
)
{
    return false;
},

/**
 * @method setGLProgramState
 * @param {ca.GLProgramState} arg0
 */
setGLProgramState : function (
glprogramstate 
)
{
},

/**
 * @method setColor
 * @param {color4b_object} arg0
 */
setColor : function (
cacolor4b 
)
{
},

/**
 * @method getDisplayedColor
 * @return {color4b_object}
 */
getDisplayedColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method removeSubview
 * @param {ca.CAView} arg0
 */
removeSubview : function (
caview 
)
{
},

/**
 * @method getAnchorPoint
 * @return {point_object}
 */
getAnchorPoint : function (
)
{
    return ca.DPoint;
},

/**
 * @method updateTransform
 */
updateTransform : function (
)
{
},

/**
 * @method getAnchorPointInPoints
 * @return {point_object}
 */
getAnchorPointInPoints : function (
)
{
    return ca.DPoint;
},

/**
 * @method getWorldToViewTransform
 * @return {ca.Mat4}
 */
getWorldToViewTransform : function (
)
{
    return ca.Mat4;
},

/**
 * @method onEnter
 */
onEnter : function (
)
{
},

/**
 * @method getCenterOrigin
 * @return {point_object}
 */
getCenterOrigin : function (
)
{
    return ca.DPoint;
},

/**
 * @method initWithCenter
 * @param {rect_object} arg0
 * @return {bool}
 */
initWithCenter : function (
drect 
)
{
    return false;
},

/**
 * @method getRotation
 * @return {int}
 */
getRotation : function (
)
{
    return 0;
},

/**
 * @method getViewToSuperviewTransform
* @param {ca.CAView} caview
* @return {ca.Mat4|ca.Mat4}
*/
getViewToSuperviewTransform : function(
caview 
)
{
    return ca.Mat4;
},

/**
 * @method getZOrder
 * @return {int}
 */
getZOrder : function (
)
{
    return 0;
},

/**
 * @method getSubviewsCount
 * @return {unsigned int}
 */
getSubviewsCount : function (
)
{
    return 0;
},

/**
 * @method visit
* @param {ca.Renderer} renderer
* @param {ca.Mat4} mat4
* @param {unsigned int} int
*/
visit : function(
renderer,
mat4,
int 
)
{
},

/**
 * @method transform
 * @param {ca.Mat4} arg0
 * @return {ca.Mat4}
 */
transform : function (
mat4 
)
{
    return ca.Mat4;
},

/**
 * @method getGLProgramState
 * @return {ca.GLProgramState}
 */
getGLProgramState : function (
)
{
    return ca.GLProgramState;
},

/**
 * @method getSkewX
 * @return {float}
 */
getSkewX : function (
)
{
    return 0;
},

/**
 * @method getSkewY
 * @return {float}
 */
getSkewY : function (
)
{
    return 0;
},

/**
 * @method setBounds
 * @param {rect_object} arg0
 */
setBounds : function (
drect 
)
{
},

/**
 * @method setRotationY
 * @param {int} arg0
 */
setRotationY : function (
int 
)
{
},

/**
 * @method insertSubview
 * @param {ca.CAView} arg0
 * @param {int} arg1
 */
insertSubview : function (
caview, 
int 
)
{
},

/**
 * @method setAdditionalTransform
* @param {ca.AffineTransform|ca.Mat4} affinetransform
*/
setAdditionalTransform : function(
mat4 
)
{
},

/**
 * @method setFlipY
 * @param {bool} arg0
 */
setFlipY : function (
bool 
)
{
},

/**
 * @method setFlipX
 * @param {bool} arg0
 */
setFlipX : function (
bool 
)
{
},

/**
 * @method getCenter
 * @return {rect_object}
 */
getCenter : function (
)
{
    return ca.DRect;
},

/**
 * @method getRotationX
 * @return {int}
 */
getRotationX : function (
)
{
    return 0;
},

/**
 * @method setViewToSuperviewTransform
 * @param {ca.Mat4} arg0
 */
setViewToSuperviewTransform : function (
mat4 
)
{
},

/**
 * @method getOrderOfArrival
 * @return {unsigned int}
 */
getOrderOfArrival : function (
)
{
    return 0;
},

/**
 * @method getRotationY
 * @return {int}
 */
getRotationY : function (
)
{
    return 0;
},

/**
 * @method isRunning
 * @return {bool}
 */
isRunning : function (
)
{
    return false;
},

/**
 * @method setBlendFunc
 * @param {ca.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method getQuad
 * @return {ca._ccV3F_C4B_T2F_Quad}
 */
getQuad : function (
)
{
    return ca._ccV3F_C4B_T2F_Quad;
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method reorderSubview
 * @param {ca.CAView} arg0
 * @param {int} arg1
 */
reorderSubview : function (
caview, 
int 
)
{
},

/**
 * @method _setZOrder
 * @param {int} arg0
 */
_setZOrder : function (
int 
)
{
},

/**
 * @method setScale
* @param {float|float} float
* @param {float} float
*/
setScale : function(
float,
float 
)
{
},

/**
 * @method isDisplayRange
 * @return {bool}
 */
isDisplayRange : function (
)
{
    return false;
},

/**
 * @method getOnExitCallback
 * @return {function}
 */
getOnExitCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method getDisplayedAlpha
 * @return {float}
 */
getDisplayedAlpha : function (
)
{
    return 0;
},

/**
 * @method getViewToSuperviewAffineTransform
* @param {ca.CAView} caview
* @return {ca.AffineTransform|ca.AffineTransform}
*/
getViewToSuperviewAffineTransform : function(
caview 
)
{
    return ca.AffineTransform;
},

/**
 * @method setOrderOfArrival
 * @param {unsigned int} arg0
 */
setOrderOfArrival : function (
int 
)
{
},

/**
 * @method setFrameOrigin
 * @param {point_object} arg0
 */
setFrameOrigin : function (
dpoint 
)
{
},

/**
 * @method getScaleY
 * @return {float}
 */
getScaleY : function (
)
{
    return 0;
},

/**
 * @method getScaleX
 * @return {float}
 */
getScaleX : function (
)
{
    return 0;
},

/**
 * @method isVisitableByVisitingCamera
 * @return {bool}
 */
isVisitableByVisitingCamera : function (
)
{
    return false;
},

/**
 * @method addSubview
 * @param {ca.CAView} arg0
 */
addSubview : function (
caview 
)
{
},

/**
 * @method initWithFrame
 * @param {rect_object} arg0
 * @return {bool}
 */
initWithFrame : function (
drect 
)
{
    return false;
},

/**
 * @method setDisplayRange
 * @param {bool} arg0
 */
setDisplayRange : function (
bool 
)
{
},

/**
 * @method setAlpha
 * @param {float} arg0
 */
setAlpha : function (
float 
)
{
},

/**
 * @method processParentFlags
 * @param {ca.Mat4} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
processParentFlags : function (
mat4, 
int 
)
{
    return 0;
},

/**
 * @method getSubviews
 * @return {Array}
 */
getSubviews : function (
)
{
    return new Array();
},

/**
 * @method getColor
 * @return {color4b_object}
 */
getColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method draw
* @param {ca.Renderer} renderer
* @param {ca.Mat4} mat4
* @param {unsigned int} int
*/
draw : function(
renderer,
mat4,
int 
)
{
},

/**
 * @method getBlendFunc
 * @return {ca.BlendFunc}
 */
getBlendFunc : function (
)
{
    return ca.BlendFunc;
},

/**
 * @method description
 * @return {char}
 */
description : function (
)
{
    return 0;
},

/**
 * @method isVisible
 * @return {bool}
 */
isVisible : function (
)
{
    return false;
},

/**
 * @method getSuperviewToViewTransform
 * @return {ca.Mat4}
 */
getSuperviewToViewTransform : function (
)
{
    return ca.Mat4;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getBounds
 * @return {rect_object}
 */
getBounds : function (
)
{
    return ca.DRect;
},

/**
 * @method getScale
 * @return {float}
 */
getScale : function (
)
{
    return 0;
},

/**
 * @method enabledRightShadow
 * @param {bool} arg0
 */
enabledRightShadow : function (
bool 
)
{
},

/**
 * @method initWithColor
 * @param {color4b_object} arg0
 * @return {bool}
 */
initWithColor : function (
cacolor4b 
)
{
    return false;
},

/**
 * @method setFrame
 * @param {rect_object} arg0
 */
setFrame : function (
drect 
)
{
},

/**
 * @method setTag
 * @param {int} arg0
 */
setTag : function (
int 
)
{
},

/**
 * @method create
 * @return {ca.CAView}
 */
create : function (
)
{
    return ca.CAView;
},

/**
 * @method createWithFrame
* @param {rect_object|rect_object} drect
* @param {color4b_object} cacolor4b
* @return {ca.CAView|ca.CAView}
*/
createWithFrame : function(
drect,
cacolor4b 
)
{
    return ca.CAView;
},

/**
 * @method createWithColor
 * @param {color4b_object} arg0
 * @return {ca.CAView}
 */
createWithColor : function (
cacolor4b 
)
{
    return ca.CAView;
},

/**
 * @method createWithLayout
* @param {layout_object|layout_object} dlayout
* @param {color4b_object} cacolor4b
* @return {ca.CAView|ca.CAView}
*/
createWithLayout : function(
dlayout,
cacolor4b 
)
{
    return ca.CAView;
},

/**
 * @method createWithCenter
* @param {rect_object|rect_object} drect
* @param {color4b_object} cacolor4b
* @return {ca.CAView|ca.CAView}
*/
createWithCenter : function(
drect,
cacolor4b 
)
{
    return ca.CAView;
},

/**
 * @method CAView
 * @constructor
 */
CAView : function (
)
{
},

};

/**
 * @class CAImageView
 */
ca.CAImageView = {

/**
 * @method isAnimating
 * @return {bool}
 */
isAnimating : function (
)
{
    return false;
},

/**
 * @method getAnimationRepeatCount
 * @return {unsigned int}
 */
getAnimationRepeatCount : function (
)
{
    return 0;
},

/**
 * @method copy
 * @return {ca.CAView}
 */
copy : function (
)
{
    return ca.CAView;
},

/**
 * @method stopAnimating
 */
stopAnimating : function (
)
{
},

/**
 * @method setImage
 * @param {ca.CAImage} arg0
 */
setImage : function (
caimage 
)
{
},

/**
 * @method getAnimationImages
 * @return {Array}
 */
getAnimationImages : function (
)
{
    return new Array();
},

/**
 * @method initWithImage
 * @param {ca.CAImage} arg0
 * @return {bool}
 */
initWithImage : function (
caimage 
)
{
    return false;
},

/**
 * @method setAnimationImages
 * @param {Array} arg0
 */
setAnimationImages : function (
array 
)
{
},

/**
 * @method setImageAsyncWithFile
 * @param {String} arg0
 */
setImageAsyncWithFile : function (
str 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setAnimationDuration
 * @param {float} arg0
 */
setAnimationDuration : function (
float 
)
{
},

/**
 * @method getScaleType
 * @return {ca.CAImageView::ScaleType}
 */
getScaleType : function (
)
{
    return 0;
},

/**
 * @method getAnimationDuration
 * @return {float}
 */
getAnimationDuration : function (
)
{
    return 0;
},

/**
 * @method setImageRect
 * @param {rect_object} arg0
 */
setImageRect : function (
drect 
)
{
},

/**
 * @method setScaleType
 * @param {ca.CAImageView::ScaleType} arg0
 */
setScaleType : function (
scaletype 
)
{
},

/**
 * @method getImage
 * @return {ca.CAImage}
 */
getImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method startAnimating
 */
startAnimating : function (
)
{
},

/**
 * @method setAnimationRepeatCount
 * @param {unsigned int} arg0
 */
setAnimationRepeatCount : function (
int 
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAImageView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAImageView;
},

/**
 * @method create
 * @return {ca.CAImageView}
 */
create : function (
)
{
    return ca.CAImageView;
},

/**
 * @method createWithImage
 * @param {ca.CAImage} arg0
 * @return {ca.CAImageView}
 */
createWithImage : function (
caimage 
)
{
    return ca.CAImageView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAImageView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAImageView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAImageView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAImageView;
},

/**
 * @method CAImageView
 * @constructor
 */
CAImageView : function (
)
{
},

};

/**
 * @class CAScale9ImageView
 */
ca.CAScale9ImageView = {

/**
 * @method setInsetBottom
 * @param {float} arg0
 */
setInsetBottom : function (
float 
)
{
},

/**
 * @method getOriginalSize
 * @return {size_object}
 */
getOriginalSize : function (
)
{
    return ca.DSize;
},

/**
 * @method draw
 * @param {ca.Renderer} arg0
 * @param {ca.Mat4} arg1
 * @param {unsigned int} arg2
 */
draw : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method setColor
 * @param {color4b_object} arg0
 */
setColor : function (
cacolor4b 
)
{
},

/**
 * @method setImage
 * @param {ca.CAImage} arg0
 */
setImage : function (
caimage 
)
{
},

/**
 * @method initWithImage
 * @param {ca.CAImage} arg0
 * @return {bool}
 */
initWithImage : function (
caimage 
)
{
    return false;
},

/**
 * @method getInsetTop
 * @return {float}
 */
getInsetTop : function (
)
{
    return 0;
},

/**
 * @method setInsetLeft
 * @param {float} arg0
 */
setInsetLeft : function (
float 
)
{
},

/**
 * @method setCapInsets
 * @param {rect_object} arg0
 */
setCapInsets : function (
drect 
)
{
},

/**
 * @method getCapInsets
 * @return {rect_object}
 */
getCapInsets : function (
)
{
    return ca.DRect;
},

/**
 * @method setInsetTop
 * @param {float} arg0
 */
setInsetTop : function (
float 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setAlpha
 * @param {float} arg0
 */
setAlpha : function (
float 
)
{
},

/**
 * @method getColor
 * @return {color4b_object}
 */
getColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getInsetLeft
 * @return {float}
 */
getInsetLeft : function (
)
{
    return 0;
},

/**
 * @method getInsetBottom
 * @return {float}
 */
getInsetBottom : function (
)
{
    return 0;
},

/**
 * @method setInsetRight
 * @param {float} arg0
 */
setInsetRight : function (
float 
)
{
},

/**
 * @method copy
 * @return {ca.CAView}
 */
copy : function (
)
{
    return ca.CAView;
},

/**
 * @method getInsetRight
 * @return {float}
 */
getInsetRight : function (
)
{
    return 0;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAScale9ImageView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAScale9ImageView;
},

/**
 * @method create
 * @return {ca.CAScale9ImageView}
 */
create : function (
)
{
    return ca.CAScale9ImageView;
},

/**
 * @method createWithImage
 * @param {ca.CAImage} arg0
 * @return {ca.CAScale9ImageView}
 */
createWithImage : function (
caimage 
)
{
    return ca.CAScale9ImageView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAScale9ImageView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAScale9ImageView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAScale9ImageView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAScale9ImageView;
},

/**
 * @method CAScale9ImageView
 * @constructor
 */
CAScale9ImageView : function (
)
{
},

};

/**
 * @class CAViewAnimation
 */
ca.CAViewAnimation = {

/**
 * @method setAnimationsEnabled
 * @param {bool} arg0
 */
setAnimationsEnabled : function (
bool 
)
{
},

/**
 * @method beginAnimations
 * @param {String} arg0
 */
beginAnimations : function (
str 
)
{
},

/**
 * @method areBeginAnimationsWithID
 * @param {String} arg0
 * @return {bool}
 */
areBeginAnimationsWithID : function (
str 
)
{
    return false;
},

/**
 * @method setAnimationDidStopSelector
 * @param {function} arg0
 */
setAnimationDidStopSelector : function (
func 
)
{
},

/**
 * @method setAnimationDelay
 * @param {float} arg0
 */
setAnimationDelay : function (
float 
)
{
},

/**
 * @method setAnimationWillStartSelector
 * @param {function} arg0
 */
setAnimationWillStartSelector : function (
func 
)
{
},

/**
 * @method areAnimationsEnabled
 * @return {bool}
 */
areAnimationsEnabled : function (
)
{
    return false;
},

/**
 * @method removeAnimationsWithView
 * @param {ca.CAView} arg0
 */
removeAnimationsWithView : function (
caview 
)
{
},

/**
 * @method setAnimationDuration
 * @param {float} arg0
 */
setAnimationDuration : function (
float 
)
{
},

/**
 * @method removeAnimations
 * @param {String} arg0
 */
removeAnimations : function (
str 
)
{
},

/**
 * @method commitAnimations
 */
commitAnimations : function (
)
{
},

/**
 * @method setAnimationRepeatAutoreverses
 * @param {bool} arg0
 */
setAnimationRepeatAutoreverses : function (
bool 
)
{
},

/**
 * @method setAnimationCurve
 * @param {ca.CAViewAnimation::Curve} arg0
 */
setAnimationCurve : function (
curve 
)
{
},

/**
 * @method areBeginAnimations
 * @return {bool}
 */
areBeginAnimations : function (
)
{
    return false;
},

/**
 * @method setAnimationRepeatCount
 * @param {float} arg0
 */
setAnimationRepeatCount : function (
float 
)
{
},

};

/**
 * @class CAControl
 */
ca.CAControl = {

/**
 * @method setControlStateSelected
 */
setControlStateSelected : function (
)
{
},

/**
 * @method setControlStateHighlighted
 */
setControlStateHighlighted : function (
)
{
},

/**
 * @method getControlState
 * @return {ca.CAControl::State}
 */
getControlState : function (
)
{
    return 0;
},

/**
 * @method setControlState
 * @param {ca.CAControl::State} arg0
 */
setControlState : function (
state 
)
{
},

/**
 * @method isRecSpe
 * @return {bool}
 */
isRecSpe : function (
)
{
    return false;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setControlStateNormal
 */
setControlStateNormal : function (
)
{
},

/**
 * @method setRecSpe
 * @param {bool} arg0
 */
setRecSpe : function (
bool 
)
{
},

/**
 * @method setControlStateDisabled
 */
setControlStateDisabled : function (
)
{
},

/**
 * @method CAControl
 * @constructor
 */
CAControl : function (
)
{
},

};

/**
 * @class CALabel
 */
ca.CALabel = {

/**
 * @method setTextAlignment
 * @param {ca.CATextAlignment} arg0
 */
setTextAlignment : function (
catextalignment 
)
{
},

/**
 * @method getText
 * @return {String}
 */
getText : function (
)
{
    return ;
},

/**
 * @method setUnderLine
 * @param {bool} arg0
 */
setUnderLine : function (
bool 
)
{
},

/**
 * @method setFontName
 * @param {String} arg0
 */
setFontName : function (
str 
)
{
},

/**
 * @method setLineSpacing
 * @param {float} arg0
 */
setLineSpacing : function (
float 
)
{
},

/**
 * @method setBold
 * @param {bool} arg0
 */
setBold : function (
bool 
)
{
},

/**
 * @method setEnableCopy
 * @param {bool} arg0
 */
setEnableCopy : function (
bool 
)
{
},

/**
 * @method sizeToFit
 */
sizeToFit : function (
)
{
},

/**
 * @method getLabelSize
 * @return {size_object}
 */
getLabelSize : function (
)
{
    return ca.DSize;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method visitEve
 */
visitEve : function (
)
{
},

/**
 * @method setWordWrap
 * @param {bool} arg0
 */
setWordWrap : function (
bool 
)
{
},

/**
 * @method getEnableCopy
 * @return {bool}
 */
getEnableCopy : function (
)
{
    return false;
},

/**
 * @method setNumberOfLine
 * @param {unsigned int} arg0
 */
setNumberOfLine : function (
int 
)
{
},

/**
 * @method setVerticalTextAlignmet
 * @param {ca.CAVerticalTextAlignment} arg0
 */
setVerticalTextAlignmet : function (
caverticaltextalignment 
)
{
},

/**
 * @method getFont
 * @return {font_object}
 */
getFont : function (
)
{
    return ca.CAFont;
},

/**
 * @method getColor
 * @return {color4b_object}
 */
getColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getNumberOfLine
 * @return {unsigned int}
 */
getNumberOfLine : function (
)
{
    return 0;
},

/**
 * @method setItalics
 * @param {bool} arg0
 */
setItalics : function (
bool 
)
{
},

/**
 * @method setFontSize
 * @param {float} arg0
 */
setFontSize : function (
float 
)
{
},

/**
 * @method setColor
 * @param {color4b_object} arg0
 */
setColor : function (
cacolor4b 
)
{
},

/**
 * @method setDeleteLine
 * @param {bool} arg0
 */
setDeleteLine : function (
bool 
)
{
},

/**
 * @method unsizeToFit
 */
unsizeToFit : function (
)
{
},

/**
 * @method setText
 * @param {String} arg0
 */
setText : function (
str 
)
{
},

/**
 * @method setFont
 * @param {font_object} arg0
 */
setFont : function (
cafont 
)
{
},

/**
 * @method create
 * @return {ca.CALabel}
 */
create : function (
)
{
    return ca.CALabel;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CALabel}
 */
createWithFrame : function (
drect 
)
{
    return ca.CALabel;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CALabel}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CALabel;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CALabel}
 */
createWithCenter : function (
drect 
)
{
    return ca.CALabel;
},

/**
 * @method CALabel
 * @constructor
 */
CALabel : function (
)
{
},

};

/**
 * @class CAApplication
 */
ca.CAApplication = {

/**
 * @method setDefaultValues
 */
setDefaultValues : function (
)
{
},

/**
 * @method setCrossAppCCLogNotification
 * @param {bool} arg0
 */
setCrossAppCCLogNotification : function (
bool 
)
{
},

/**
 * @method getStatusBarOrientation
 * @return {ca.CAInterfaceOrientation}
 */
getStatusBarOrientation : function (
)
{
    return 0;
},

/**
 * @method getImageCache
 * @return {ca.CAImageCache}
 */
getImageCache : function (
)
{
    return ca.CAImageCache;
},

/**
 * @method getDeltaTime
* @return {float|float}
*/
getDeltaTime : function(
)
{
    return 0;
},

/**
 * @method setGLDefaultValues
 */
setGLDefaultValues : function (
)
{
},

/**
 * @method setActionManager
 * @param {ca.ActionManager} arg0
 */
setActionManager : function (
actionmanager 
)
{
},

/**
 * @method setAlphaBlending
 * @param {bool} arg0
 */
setAlphaBlending : function (
bool 
)
{
},

/**
 * @method loadMatrix
 * @param {ca.MATRIX_STACK_TYPE} arg0
 * @param {ca.Mat4} arg1
 */
loadMatrix : function (
matrix_stack_type, 
mat4 
)
{
},

/**
 * @method updateDraw
 */
updateDraw : function (
)
{
},

/**
 * @method getKeypadDispatcher
 * @return {ca.CAKeypadDispatcher}
 */
getKeypadDispatcher : function (
)
{
    return ca.CAKeypadDispatcher;
},

/**
 * @method getRenderer
 * @return {ca.Renderer}
 */
getRenderer : function (
)
{
    return ca.Renderer;
},

/**
 * @method getWinSize
 * @return {size_object}
 */
getWinSize : function (
)
{
    return ca.DSize;
},

/**
 * @method end
 */
end : function (
)
{
},

/**
 * @method multiplyMatrix
 * @param {ca.MATRIX_STACK_TYPE} arg0
 * @param {ca.Mat4} arg1
 */
multiplyMatrix : function (
matrix_stack_type, 
mat4 
)
{
},

/**
 * @method runWindow
 * @param {ca.CAWindow} arg0
 */
runWindow : function (
cawindow 
)
{
},

/**
 * @method getNotificationView
 * @return {ca.CAView}
 */
getNotificationView : function (
)
{
    return ca.CAView;
},

/**
 * @method getVisibleOrigin
 * @return {point_object}
 */
getVisibleOrigin : function (
)
{
    return ca.DPoint;
},

/**
 * @method mainLoop
 */
mainLoop : function (
)
{
},

/**
 * @method isDrawing
 * @return {bool}
 */
isDrawing : function (
)
{
    return false;
},

/**
 * @method setDepthTest
 * @param {bool} arg0
 */
setDepthTest : function (
bool 
)
{
},

/**
 * @method getSecondsPerFrame
 * @return {float}
 */
getSecondsPerFrame : function (
)
{
    return 0;
},

/**
 * @method resetMatrixStack
 */
resetMatrixStack : function (
)
{
},

/**
 * @method getStatusBarStyle
 * @return {ca.CAStatusBarStyle}
 */
getStatusBarStyle : function (
)
{
    return 0;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setScheduler
 * @param {ca.CAScheduler} arg0
 */
setScheduler : function (
cascheduler 
)
{
},

/**
 * @method reshapeProjection
 * @param {size_object} arg0
 */
reshapeProjection : function (
dsize 
)
{
},

/**
 * @method getMatrix
 * @param {ca.MATRIX_STACK_TYPE} arg0
 * @return {ca.Mat4}
 */
getMatrix : function (
matrix_stack_type 
)
{
    return ca.Mat4;
},

/**
 * @method setKeypadDispatcher
 * @param {ca.CAKeypadDispatcher} arg0
 */
setKeypadDispatcher : function (
cakeypaddispatcher 
)
{
},

/**
 * @method getOpenGLView
 * @return {ca.CCEGLView}
 */
getOpenGLView : function (
)
{
    return ca.CCEGLView;
},

/**
 * @method setViewport
 */
setViewport : function (
)
{
},

/**
 * @method stopAnimation
 */
stopAnimation : function (
)
{
},

/**
 * @method getNumberOfDraws
 * @return {unsigned long}
 */
getNumberOfDraws : function (
)
{
    return 0;
},

/**
 * @method getProjection
 * @return {ca.CAApplication::Projection}
 */
getProjection : function (
)
{
    return 0;
},

/**
 * @method resume
 */
resume : function (
)
{
},

/**
 * @method isStatusBarHidden
 * @return {bool}
 */
isStatusBarHidden : function (
)
{
    return false;
},

/**
 * @method isNextDeltaTimeZero
 * @return {bool}
 */
isNextDeltaTimeZero : function (
)
{
    return false;
},

/**
 * @method setImageCache
 * @param {ca.CAImageCache} arg0
 */
setImageCache : function (
caimagecache 
)
{
},

/**
 * @method isCrossAppCCLogNotification
 * @return {bool}
 */
isCrossAppCCLogNotification : function (
)
{
    return false;
},

/**
 * @method setStatusBarStyle
 * @param {ca.CAStatusBarStyle} arg0
 */
setStatusBarStyle : function (
castatusbarstyle 
)
{
},

/**
 * @method setClearColor
 * @param {color4f_object} arg0
 */
setClearColor : function (
cacolor4f 
)
{
},

/**
 * @method setOpenGLView
 * @param {ca.CCEGLView} arg0
 */
setOpenGLView : function (
cceglview 
)
{
},

/**
 * @method startAnimation
 */
startAnimation : function (
)
{
},

/**
 * @method purgeCachedData
 */
purgeCachedData : function (
)
{
},

/**
 * @method getTotalFrames
 * @return {unsigned int}
 */
getTotalFrames : function (
)
{
    return 0;
},

/**
 * @method pause
 */
pause : function (
)
{
},

/**
 * @method setThemeManager
 * @param {ca.CAThemeManager} arg0
 */
setThemeManager : function (
cathememanager 
)
{
},

/**
 * @method restart
 */
restart : function (
)
{
},

/**
 * @method loadIdentityMatrix
 * @param {ca.MATRIX_STACK_TYPE} arg0
 */
loadIdentityMatrix : function (
matrix_stack_type 
)
{
},

/**
 * @method isDisplayStats
 * @return {bool}
 */
isDisplayStats : function (
)
{
    return false;
},

/**
 * @method setProjection
 * @param {ca.CAApplication::Projection} arg0
 */
setProjection : function (
projection 
)
{
},

/**
 * @method setStatusBarHidden
 * @param {bool} arg0
 */
setStatusBarHidden : function (
bool 
)
{
},

/**
 * @method getTouchDispatcher
 * @return {ca.CATouchDispatcher}
 */
getTouchDispatcher : function (
)
{
    return ca.CATouchDispatcher;
},

/**
 * @method getZEye
 * @return {float}
 */
getZEye : function (
)
{
    return 0;
},

/**
 * @method setNextDeltaTimeZero
 * @param {bool} arg0
 */
setNextDeltaTimeZero : function (
bool 
)
{
},

/**
 * @method getThemeManager
 * @return {ca.CAThemeManager}
 */
getThemeManager : function (
)
{
    return ca.CAThemeManager;
},

/**
 * @method popMatrix
 * @param {ca.MATRIX_STACK_TYPE} arg0
 */
popMatrix : function (
matrix_stack_type 
)
{
},

/**
 * @method getVisibleSize
 * @return {size_object}
 */
getVisibleSize : function (
)
{
    return ca.DSize;
},

/**
 * @method setTouchDispatcher
 * @param {ca.CATouchDispatcher} arg0
 */
setTouchDispatcher : function (
catouchdispatcher 
)
{
},

/**
 * @method setNotificationView
 * @param {ca.CAView} arg0
 */
setNotificationView : function (
caview 
)
{
},

/**
 * @method getScheduler
 * @return {ca.CAScheduler}
 */
getScheduler : function (
)
{
    return ca.CAScheduler;
},

/**
 * @method getRootWindow
 * @return {ca.CAWindow}
 */
getRootWindow : function (
)
{
    return ca.CAWindow;
},

/**
 * @method getClassTypeInfo
 * @return {long}
 */
getClassTypeInfo : function (
)
{
    return 0;
},

/**
 * @method getAnimationInterval
 * @return {double}
 */
getAnimationInterval : function (
)
{
    return 0;
},

/**
 * @method isPaused
 * @return {bool}
 */
isPaused : function (
)
{
    return false;
},

/**
 * @method getCurrentNumberOfDraws
 * @return {unsigned long}
 */
getCurrentNumberOfDraws : function (
)
{
    return 0;
},

/**
 * @method setDisplayStats
 * @param {bool} arg0
 */
setDisplayStats : function (
bool 
)
{
},

/**
 * @method drawScene
 */
drawScene : function (
)
{
},

/**
 * @method getActionManager
 * @return {ca.ActionManager}
 */
getActionManager : function (
)
{
    return ca.ActionManager;
},

/**
 * @method pushMatrix
 * @param {ca.MATRIX_STACK_TYPE} arg0
 */
pushMatrix : function (
matrix_stack_type 
)
{
},

/**
 * @method getApplication
 * @return {ca.CAApplication}
 */
getApplication : function (
)
{
    return ca.CAApplication;
},

};

/**
 * @class CAButton
 */
ca.CAButton = {

/**
 * @method setImageSize
 * @param {size_object} arg0
 */
setImageSize : function (
dsize 
)
{
},

/**
 * @method interruptTouchState
 */
interruptTouchState : function (
)
{
},

/**
 * @method getBackgroundViewForState
 * @param {ca.CAControl::State} arg0
 * @return {ca.CAView}
 */
getBackgroundViewForState : function (
state 
)
{
    return ca.CAView;
},

/**
 * @method addTarget
 * @param {function} arg0
 * @param {ca.CAButton::Event} arg1
 */
addTarget : function (
func, 
event 
)
{
},

/**
 * @method setTitleLabelSize
 * @param {size_object} arg0
 */
setTitleLabelSize : function (
dsize 
)
{
},

/**
 * @method setBackgroundViewForState
 * @param {ca.CAControl::State} arg0
 * @param {ca.CAView} arg1
 */
setBackgroundViewForState : function (
state, 
caview 
)
{
},

/**
 * @method setTitleBold
 * @param {bool} arg0
 */
setTitleBold : function (
bool 
)
{
},

/**
 * @method setImageOffset
 * @param {size_object} arg0
 */
setImageOffset : function (
dsize 
)
{
},

/**
 * @method setTitleFontSize
 * @param {float} arg0
 */
setTitleFontSize : function (
float 
)
{
},

/**
 * @method setTitleFontName
 * @param {String} arg0
 */
setTitleFontName : function (
str 
)
{
},

/**
 * @method setImageForState
 * @param {ca.CAControl::State} arg0
 * @param {ca.CAImage} arg1
 */
setImageForState : function (
state, 
caimage 
)
{
},

/**
 * @method setTitleColorForState
 * @param {ca.CAControl::State} arg0
 * @param {color4b_object} arg1
 */
setTitleColorForState : function (
state, 
cacolor4b 
)
{
},

/**
 * @method setImageColorForState
 * @param {ca.CAControl::State} arg0
 * @param {color4b_object} arg1
 */
setImageColorForState : function (
state, 
cacolor4b 
)
{
},

/**
 * @method setTitleForState
 * @param {ca.CAControl::State} arg0
 * @param {String} arg1
 */
setTitleForState : function (
state, 
str 
)
{
},

/**
 * @method getImageForState
 * @param {ca.CAControl::State} arg0
 * @return {ca.CAImage}
 */
getImageForState : function (
state 
)
{
    return ca.CAImage;
},

/**
 * @method setTitleTextAlignment
 * @param {ca.CATextAlignment} arg0
 */
setTitleTextAlignment : function (
catextalignment 
)
{
},

/**
 * @method getTitleForState
 * @param {ca.CAControl::State} arg0
 * @return {String}
 */
getTitleForState : function (
state 
)
{
    return ;
},

/**
 * @method setTitleOffset
 * @param {size_object} arg0
 */
setTitleOffset : function (
dsize 
)
{
},

/**
 * @method create
 * @param {ca.CAButton::Type} arg0
 * @return {ca.CAButton}
 */
create : function (
type 
)
{
    return ca.CAButton;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {ca.CAButton::Type} arg1
 * @return {ca.CAButton}
 */
createWithFrame : function (
drect, 
type 
)
{
    return ca.CAButton;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {ca.CAButton::Type} arg1
 * @return {ca.CAButton}
 */
createWithLayout : function (
dlayout, 
type 
)
{
    return ca.CAButton;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {ca.CAButton::Type} arg1
 * @return {ca.CAButton}
 */
createWithCenter : function (
drect, 
type 
)
{
    return ca.CAButton;
},

/**
 * @method CAButton
 * @constructor
 * @param {ca.CAButton::Type} arg0
 */
CAButton : function (
type 
)
{
},

};

/**
 * @class CASegmentedControl
 */
ca.CASegmentedControl = {

/**
 * @method setTitleFontSize
 * @param {float} arg0
 */
setTitleFontSize : function (
float 
)
{
},

/**
 * @method setImageColor
 * @param {color4b_object} arg0
 */
setImageColor : function (
cacolor4b 
)
{
},

/**
 * @method setSegmentItemBackgroundImage
 * @param {ca.CAImage} arg0
 */
setSegmentItemBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setImageSizeAtIndex
 * @param {size_object} arg0
 * @param {int} arg1
 */
setImageSizeAtIndex : function (
dsize, 
int 
)
{
},

/**
 * @method setSelectedAtIndex
 * @param {int} arg0
 */
setSelectedAtIndex : function (
int 
)
{
},

/**
 * @method setImageForSegmentAtIndex
 * @param {ca.CAImage} arg0
 * @param {int} arg1
 * @param {ca.CAControl::State} arg2
 */
setImageForSegmentAtIndex : function (
caimage, 
int, 
state 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getSelectedAtIndex
 * @return {int}
 */
getSelectedAtIndex : function (
)
{
    return 0;
},

/**
 * @method setTitleSelectedColor
 * @param {color4b_object} arg0
 */
setTitleSelectedColor : function (
cacolor4b 
)
{
},

/**
 * @method getNumberOfSegments
 * @return {unsigned int}
 */
getNumberOfSegments : function (
)
{
    return 0;
},

/**
 * @method setTitleForSegmentAtIndex
 * @param {String} arg0
 * @param {int} arg1
 */
setTitleForSegmentAtIndex : function (
str, 
int 
)
{
},

/**
 * @method setTitleColor
 * @param {color4b_object} arg0
 */
setTitleColor : function (
cacolor4b 
)
{
},

/**
 * @method isEnabledForSegmentAtIndex
 * @param {int} arg0
 * @return {bool}
 */
isEnabledForSegmentAtIndex : function (
int 
)
{
    return false;
},

/**
 * @method setBackgroundImage
 * @param {ca.CAImage} arg0
 */
setBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setTarget
 * @param {function} arg0
 */
setTarget : function (
func 
)
{
},

/**
 * @method setTitleFontName
 * @param {String} arg0
 */
setTitleFontName : function (
str 
)
{
},

/**
 * @method getTitleSelectedColor
 * @return {color4b_object}
 */
getTitleSelectedColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setImageSelectedColor
 * @param {color4b_object} arg0
 */
setImageSelectedColor : function (
cacolor4b 
)
{
},

/**
 * @method getContentOffsetForSegmentAtIndex
 * @param {int} arg0
 * @return {size_object}
 */
getContentOffsetForSegmentAtIndex : function (
int 
)
{
    return ca.DSize;
},

/**
 * @method getImageSelectedColor
 * @return {color4b_object}
 */
getImageSelectedColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getImageForSegmentAtIndex
 * @param {int} arg0
 * @return {ca.CAImage}
 */
getImageForSegmentAtIndex : function (
int 
)
{
    return ca.CAImage;
},

/**
 * @method setContentOffsetForSegmentAtIndex
 * @param {size_object} arg0
 * @param {int} arg1
 */
setContentOffsetForSegmentAtIndex : function (
dsize, 
int 
)
{
},

/**
 * @method getTitleColor
 * @return {color4b_object}
 */
getTitleColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method setTintColor
 * @param {color4b_object} arg0
 */
setTintColor : function (
cacolor4b 
)
{
},

/**
 * @method getTitleForSegmentAtIndex
 * @param {int} arg0
 * @return {String}
 */
getTitleForSegmentAtIndex : function (
int 
)
{
    return ;
},

/**
 * @method getImageColor
 * @return {color4b_object}
 */
getImageColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method setEnabledForSegmentAtIndex
 * @param {bool} arg0
 * @param {int} arg1
 */
setEnabledForSegmentAtIndex : function (
bool, 
int 
)
{
},

/**
 * @method create
 * @param {unsigned int} arg0
 * @return {ca.CASegmentedControl}
 */
create : function (
int 
)
{
    return ca.CASegmentedControl;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {unsigned int} arg1
 * @return {ca.CASegmentedControl}
 */
createWithFrame : function (
drect, 
int 
)
{
    return ca.CASegmentedControl;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {unsigned int} arg1
 * @return {ca.CASegmentedControl}
 */
createWithLayout : function (
dlayout, 
int 
)
{
    return ca.CASegmentedControl;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {unsigned int} arg1
 * @return {ca.CASegmentedControl}
 */
createWithCenter : function (
drect, 
int 
)
{
    return ca.CASegmentedControl;
},

/**
 * @method CASegmentedControl
 * @constructor
 * @param {unsigned int} arg0
 */
CASegmentedControl : function (
int 
)
{
},

};

/**
 * @class CABarItem
 */
ca.CABarItem = {

/**
 * @method setImage
 * @param {ca.CAImage} arg0
 */
setImage : function (
caimage 
)
{
},

/**
 * @method setTitle
 * @param {String} arg0
 */
setTitle : function (
str 
)
{
},

/**
 * @method getImage
 * @return {ca.CAImage}
 */
getImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method getTitle
 * @return {String}
 */
getTitle : function (
)
{
    return ;
},

/**
 * @method CABarItem
 * @constructor
 */
CABarItem : function (
)
{
},

};

/**
 * @class CABarButtonItem
 */
ca.CABarButtonItem = {

/**
 * @method getImageOffsetX
 * @return {int}
 */
getImageOffsetX : function (
)
{
    return 0;
},

/**
 * @method getCustomView
 * @return {ca.CAView}
 */
getCustomView : function (
)
{
    return ca.CAView;
},

/**
 * @method setLabelWidth
 * @param {unsigned int} arg0
 */
setLabelWidth : function (
int 
)
{
},

/**
 * @method setImageOffsetX
 * @param {int} arg0
 */
setImageOffsetX : function (
int 
)
{
},

/**
 * @method initWithCustomView
 * @param {ca.CAView} arg0
 * @return {bool}
 */
initWithCustomView : function (
caview 
)
{
    return false;
},

/**
 * @method setItemWidth
 * @param {unsigned int} arg0
 */
setItemWidth : function (
int 
)
{
},

/**
 * @method initWithImage
 * @param {ca.CAImage} arg0
 * @param {ca.CAImage} arg1
 * @return {bool}
 */
initWithImage : function (
caimage, 
caimage 
)
{
    return false;
},

/**
 * @method getHighlightedImage
 * @return {ca.CAImage}
 */
getHighlightedImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setLabelOffsetX
 * @param {int} arg0
 */
setLabelOffsetX : function (
int 
)
{
},

/**
 * @method setImageWidth
 * @param {unsigned int} arg0
 */
setImageWidth : function (
int 
)
{
},

/**
 * @method setHighlightedImage
 * @param {ca.CAImage} arg0
 */
setHighlightedImage : function (
caimage 
)
{
},

/**
 * @method init
 * @param {String} arg0
 * @param {ca.CAImage} arg1
 * @param {ca.CAImage} arg2
 * @return {bool}
 */
init : function (
str, 
caimage, 
caimage 
)
{
    return false;
},

/**
 * @method initWithTitle
 * @param {String} arg0
 * @param {ca.CAImage} arg1
 * @param {ca.CAImage} arg2
 * @return {bool}
 */
initWithTitle : function (
str, 
caimage, 
caimage 
)
{
    return false;
},

/**
 * @method setCallbackFunction
 * @param {function} arg0
 */
setCallbackFunction : function (
func 
)
{
},

/**
 * @method getItemWidth
 * @return {unsigned int}
 */
getItemWidth : function (
)
{
    return 0;
},

/**
 * @method getImageWidth
 * @return {unsigned int}
 */
getImageWidth : function (
)
{
    return 0;
},

/**
 * @method getLabelOffsetX
 * @return {int}
 */
getLabelOffsetX : function (
)
{
    return 0;
},

/**
 * @method getCallbackFunction
 * @return {function}
 */
getCallbackFunction : function (
)
{
    return std::function<void ()>;
},

/**
 * @method getLabelWidth
 * @return {unsigned int}
 */
getLabelWidth : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @param {ca.CAImage} arg1
 * @param {ca.CAImage} arg2
 * @return {ca.CABarButtonItem}
 */
create : function (
str, 
caimage, 
caimage 
)
{
    return ca.CABarButtonItem;
},

/**
 * @method CABarButtonItem
 * @constructor
 */
CABarButtonItem : function (
)
{
},

};

/**
 * @class CANavigationBarItem
 */
ca.CANavigationBarItem = {

/**
 * @method addLeftButtonItem
 * @param {ca.CABarButtonItem} arg0
 */
addLeftButtonItem : function (
cabarbuttonitem 
)
{
},

/**
 * @method getRightButtonItems
 * @return {Array}
 */
getRightButtonItems : function (
)
{
    return new Array();
},

/**
 * @method setNagigationBarHidden
 * @param {bool} arg0
 */
setNagigationBarHidden : function (
bool 
)
{
},

/**
 * @method getTitleViewImage
 * @return {ca.CAImage}
 */
getTitleViewImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setShowGoBackButton
 * @param {bool} arg0
 */
setShowGoBackButton : function (
bool 
)
{
},

/**
 * @method addRightButtonItem
 * @param {ca.CABarButtonItem} arg0
 */
addRightButtonItem : function (
cabarbuttonitem 
)
{
},

/**
 * @method getTitleView
 * @return {ca.CAView}
 */
getTitleView : function (
)
{
    return ca.CAView;
},

/**
 * @method setTitleView
 * @param {ca.CAView} arg0
 */
setTitleView : function (
caview 
)
{
},

/**
 * @method init
 * @param {String} arg0
 * @return {bool}
 */
init : function (
str 
)
{
    return false;
},

/**
 * @method getLeftButtonItems
 * @return {Array}
 */
getLeftButtonItems : function (
)
{
    return new Array();
},

/**
 * @method setTitleViewImage
 * @param {ca.CAImage} arg0
 */
setTitleViewImage : function (
caimage 
)
{
},

/**
 * @method isNagigationBarHidden
 * @return {bool}
 */
isNagigationBarHidden : function (
)
{
    return false;
},

/**
 * @method isShowGoBackButton
 * @return {bool}
 */
isShowGoBackButton : function (
)
{
    return false;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CANavigationBarItem}
 */
create : function (
str 
)
{
    return ca.CANavigationBarItem;
},

/**
 * @method CANavigationBarItem
 * @constructor
 */
CANavigationBarItem : function (
)
{
},

};

/**
 * @class CATabBarItem
 */
ca.CATabBarItem = {

/**
 * @method getBadgeValue
 * @return {String}
 */
getBadgeValue : function (
)
{
    return ;
},

/**
 * @method setSelectedImage
 * @param {ca.CAImage} arg0
 */
setSelectedImage : function (
caimage 
)
{
},

/**
 * @method getSelectedImage
 * @return {ca.CAImage}
 */
getSelectedImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method init
 * @param {String} arg0
 * @param {ca.CAImage} arg1
 * @param {ca.CAImage} arg2
 * @return {bool}
 */
init : function (
str, 
caimage, 
caimage 
)
{
    return false;
},

/**
 * @method setBadgeValue
 * @param {String} arg0
 */
setBadgeValue : function (
str 
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @param {ca.CAImage} arg1
 * @param {ca.CAImage} arg2
 * @return {ca.CATabBarItem}
 */
create : function (
str, 
caimage, 
caimage 
)
{
    return ca.CATabBarItem;
},

/**
 * @method CATabBarItem
 * @constructor
 */
CATabBarItem : function (
)
{
},

};

/**
 * @class CANavigationBar
 */
ca.CANavigationBar = {

/**
 * @method getGoBackBarButtonItem
 * @return {ca.CABarButtonItem}
 */
getGoBackBarButtonItem : function (
)
{
    return ca.CABarButtonItem;
},

/**
 * @method getDelegate
 * @return {ca.CANavigationBarDelegate}
 */
getDelegate : function (
)
{
    return ca.CANavigationBarDelegate;
},

/**
 * @method getItem
 * @return {ca.CANavigationBarItem}
 */
getItem : function (
)
{
    return ca.CANavigationBarItem;
},

/**
 * @method setButtonColor
 * @param {color4b_object} arg0
 */
setButtonColor : function (
cacolor4b 
)
{
},

/**
 * @method getTitleColor
 * @return {color4b_object}
 */
getTitleColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setGoBackBarButtonItem
 * @param {ca.CABarButtonItem} arg0
 */
setGoBackBarButtonItem : function (
cabarbuttonitem 
)
{
},

/**
 * @method setItem
 * @param {ca.CANavigationBarItem} arg0
 */
setItem : function (
canavigationbaritem 
)
{
},

/**
 * @method getBackgroundView
 * @return {ca.CAView}
 */
getBackgroundView : function (
)
{
    return ca.CAView;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method setBackgroundView
 * @param {ca.CAView} arg0
 */
setBackgroundView : function (
caview 
)
{
},

/**
 * @method setDelegate
 * @param {ca.CANavigationBarDelegate} arg0
 */
setDelegate : function (
canavigationbardelegate 
)
{
},

/**
 * @method getButtonColor
 * @return {color4b_object}
 */
getButtonColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method setTitleColor
 * @param {color4b_object} arg0
 */
setTitleColor : function (
cacolor4b 
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {bool} arg1
 * @return {ca.CANavigationBar}
 */
createWithFrame : function (
drect, 
bool 
)
{
    return ca.CANavigationBar;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {bool} arg1
 * @return {ca.CANavigationBar}
 */
createWithLayout : function (
dlayout, 
bool 
)
{
    return ca.CANavigationBar;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {bool} arg1
 * @return {ca.CANavigationBar}
 */
createWithCenter : function (
drect, 
bool 
)
{
    return ca.CANavigationBar;
},

/**
 * @method CANavigationBar
 * @constructor
 */
CANavigationBar : function (
)
{
},

};

/**
 * @class CATabBar
 */
ca.CATabBar = {

/**
 * @method setSelectedBackgroundImage
 * @param {ca.CAImage} arg0
 */
setSelectedBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setDelegate
 * @param {ca.CATabBarDelegate} arg0
 */
setDelegate : function (
catabbardelegate 
)
{
},

/**
 * @method getItemSize
 * @return {size_object}
 */
getItemSize : function (
)
{
    return ca.DSize;
},

/**
 * @method replaceItemAtIndex
 * @param {unsigned long} arg0
 * @param {ca.CATabBarItem} arg1
 */
replaceItemAtIndex : function (
long, 
catabbaritem 
)
{
},

/**
 * @method getSelectedIndicatorColor
 * @return {color4b_object}
 */
getSelectedIndicatorColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getBackgroundColor
 * @return {color4b_object}
 */
getBackgroundColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getContentViewFrame
 * @return {rect_object}
 */
getContentViewFrame : function (
)
{
    return ca.DRect;
},

/**
 * @method getTitleBoldForSelected
 * @return {bool}
 */
getTitleBoldForSelected : function (
)
{
    return false;
},

/**
 * @method setSelectedAtIndex
 * @param {int} arg0
 */
setSelectedAtIndex : function (
int 
)
{
},

/**
 * @method showSelectedIndicator
 */
showSelectedIndicator : function (
)
{
},

/**
 * @method addForbidSelectedAtIndex
 * @param {int} arg0
 */
addForbidSelectedAtIndex : function (
int 
)
{
},

/**
 * @method getSelectedIndex
 * @return {int}
 */
getSelectedIndex : function (
)
{
    return 0;
},

/**
 * @method setSelectedIndicatorImage
 * @param {ca.CAImage} arg0
 */
setSelectedIndicatorImage : function (
caimage 
)
{
},

/**
 * @method getTitleColorForNormal
 * @return {color4b_object}
 */
getTitleColorForNormal : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getTitleColorForSelected
 * @return {color4b_object}
 */
getTitleColorForSelected : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setItems
 * @param {Array} arg0
 */
setItems : function (
array 
)
{
},

/**
 * @method getBackgroundImage
 * @return {ca.CAImage}
 */
getBackgroundImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setTitleBoldForSelected
 * @param {bool} arg0
 */
setTitleBoldForSelected : function (
bool 
)
{
},

/**
 * @method setBackgroundImage
 * @param {ca.CAImage} arg0
 */
setBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setBackgroundColor
 * @param {color4b_object} arg0
 */
setBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method setTitleColorForSelected
 * @param {color4b_object} arg0
 */
setTitleColorForSelected : function (
cacolor4b 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method setSelectedIndicatorColor
 * @param {color4b_object} arg0
 */
setSelectedIndicatorColor : function (
cacolor4b 
)
{
},

/**
 * @method getSelectedBackgroundColor
 * @return {color4b_object}
 */
getSelectedBackgroundColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setSelectedBackgroundColor
 * @param {color4b_object} arg0
 */
setSelectedBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method getDelegate
 * @return {ca.CATabBarDelegate}
 */
getDelegate : function (
)
{
    return ca.CATabBarDelegate;
},

/**
 * @method getSelectedIndicatorImage
 * @return {ca.CAImage}
 */
getSelectedIndicatorImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setTitleColorForNormal
 * @param {color4b_object} arg0
 */
setTitleColorForNormal : function (
cacolor4b 
)
{
},

/**
 * @method getSelectedBackgroundImage
 * @return {ca.CAImage}
 */
getSelectedBackgroundImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {bool} arg1
 * @return {ca.CATabBar}
 */
createWithFrame : function (
drect, 
bool 
)
{
    return ca.CATabBar;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {bool} arg1
 * @return {ca.CATabBar}
 */
createWithLayout : function (
dlayout, 
bool 
)
{
    return ca.CATabBar;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {bool} arg1
 * @return {ca.CATabBar}
 */
createWithCenter : function (
drect, 
bool 
)
{
    return ca.CATabBar;
},

/**
 * @method CATabBar
 * @constructor
 */
CATabBar : function (
)
{
},

};

/**
 * @class CAActivityIndicatorView
 */
ca.CAActivityIndicatorView = {

/**
 * @method onCancel
 * @param {function} arg0
 */
onCancel : function (
func 
)
{
},

/**
 * @method setCycleTime
 * @param {float} arg0
 */
setCycleTime : function (
float 
)
{
},

/**
 * @method onEnter
 */
onEnter : function (
)
{
},

/**
 * @method onExit
 */
onExit : function (
)
{
},

/**
 * @method getActivityBackView
 * @return {ca.CAView}
 */
getActivityBackView : function (
)
{
    return ca.CAView;
},

/**
 * @method getActivityIndicatorView
 * @return {ca.CAView}
 */
getActivityIndicatorView : function (
)
{
    return ca.CAView;
},

/**
 * @method setTimesOneCycle
 * @param {float} arg0
 */
setTimesOneCycle : function (
float 
)
{
},

/**
 * @method getColor
 * @return {color4b_object}
 */
getColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setActivityBackView
 * @param {ca.CAView} arg0
 */
setActivityBackView : function (
caview 
)
{
},

/**
 * @method setStyle
 * @param {ca.CAActivityIndicatorView::Style} arg0
 */
setStyle : function (
style 
)
{
},

/**
 * @method setLoadingMinTime
 * @param {float} arg0
 */
setLoadingMinTime : function (
float 
)
{
},

/**
 * @method setActivityIndicatorOffset
 * @param {size_object} arg0
 */
setActivityIndicatorOffset : function (
dsize 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method isAnimating
 * @return {bool}
 */
isAnimating : function (
)
{
    return false;
},

/**
 * @method setActivityIndicatorView
 * @param {ca.CAView} arg0
 */
setActivityIndicatorView : function (
caview 
)
{
},

/**
 * @method getLoadingMinTime
 * @return {float}
 */
getLoadingMinTime : function (
)
{
    return 0;
},

/**
 * @method startAnimating
 */
startAnimating : function (
)
{
},

/**
 * @method stopAnimating
 */
stopAnimating : function (
)
{
},

/**
 * @method create
 * @return {ca.CAActivityIndicatorView}
 */
create : function (
)
{
    return ca.CAActivityIndicatorView;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAActivityIndicatorView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAActivityIndicatorView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAActivityIndicatorView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAActivityIndicatorView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAActivityIndicatorView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAActivityIndicatorView;
},

/**
 * @method CAActivityIndicatorView
 * @constructor
 */
CAActivityIndicatorView : function (
)
{
},

};

/**
 * @class CAPullToRefreshView
 */
ca.CAPullToRefreshView = {

/**
 * @method getLoadingView
 * @return {ca.CAActivityIndicatorView}
 */
getLoadingView : function (
)
{
    return ca.CAActivityIndicatorView;
},

/**
 * @method setPullToRefreshText
 * @param {String} arg0
 */
setPullToRefreshText : function (
str 
)
{
},

/**
 * @method getType
 * @return {ca.CAPullToRefreshView::Type}
 */
getType : function (
)
{
    return 0;
},

/**
 * @method getRefreshingText
 * @return {String}
 */
getRefreshingText : function (
)
{
    return ;
},

/**
 * @method setLoadingView
 * @param {ca.CAActivityIndicatorView} arg0
 */
setLoadingView : function (
caactivityindicatorview 
)
{
},

/**
 * @method setRefreshingText
 * @param {String} arg0
 */
setRefreshingText : function (
str 
)
{
},

/**
 * @method getLabelColor
 * @return {color4b_object}
 */
getLabelColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getPullToImage
 * @return {ca.CAImage}
 */
getPullToImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getReleaseToRefreshText
 * @return {String}
 */
getReleaseToRefreshText : function (
)
{
    return ;
},

/**
 * @method setLabelColor
 * @param {color4b_object} arg0
 */
setLabelColor : function (
cacolor4b 
)
{
},

/**
 * @method setReleaseToRefreshText
 * @param {String} arg0
 */
setReleaseToRefreshText : function (
str 
)
{
},

/**
 * @method setPullToImage
 * @param {ca.CAImage} arg0
 */
setPullToImage : function (
caimage 
)
{
},

/**
 * @method getPullToRefreshText
 * @return {String}
 */
getPullToRefreshText : function (
)
{
    return ;
},

/**
 * @method create
 * @param {ca.CAPullToRefreshView::Type} arg0
 * @return {ca.CAPullToRefreshView}
 */
create : function (
type 
)
{
    return ca.CAPullToRefreshView;
},

/**
 * @method CAPullToRefreshView
 * @constructor
 * @param {ca.CAPullToRefreshView::Type} arg0
 */
CAPullToRefreshView : function (
type 
)
{
},

};

/**
 * @class CAScrollView
 */
ca.CAScrollView = {

/**
 * @method setBounceVertical
 * @param {bool} arg0
 */
setBounceVertical : function (
bool 
)
{
},

/**
 * @method removeAllSubviews
 */
removeAllSubviews : function (
)
{
},

/**
 * @method isTracking
 * @return {bool}
 */
isTracking : function (
)
{
    return false;
},

/**
 * @method isZooming
 * @return {bool}
 */
isZooming : function (
)
{
    return false;
},

/**
 * @method getHeaderRefreshView
 * @return {ca.CAPullToRefreshView}
 */
getHeaderRefreshView : function (
)
{
    return ca.CAPullToRefreshView;
},

/**
 * @method setDidMovedCallback
 * @param {function} arg0
 */
setDidMovedCallback : function (
func 
)
{
},

/**
 * @method isShowsScrollIndicators
 * @return {bool}
 */
isShowsScrollIndicators : function (
)
{
    return false;
},

/**
 * @method isShowsHorizontalScrollIndicator
 * @return {bool}
 */
isShowsHorizontalScrollIndicator : function (
)
{
    return false;
},

/**
 * @method setTouchEnabledAtSubviews
 * @param {bool} arg0
 */
setTouchEnabledAtSubviews : function (
bool 
)
{
},

/**
 * @method getZoomScale
 * @return {float}
 */
getZoomScale : function (
)
{
    return 0;
},

/**
 * @method insertSubview
 * @param {ca.CAView} arg0
 * @param {int} arg1
 */
insertSubview : function (
caview, 
int 
)
{
},

/**
 * @method setDidZoomCallback
 * @param {function} arg0
 */
setDidZoomCallback : function (
func 
)
{
},

/**
 * @method endFooterRefresh
 */
endFooterRefresh : function (
)
{
},

/**
 * @method isBounceHorizontal
 * @return {bool}
 */
isBounceHorizontal : function (
)
{
    return false;
},

/**
 * @method setFooterRefreshView
 * @param {ca.CAPullToRefreshView} arg0
 */
setFooterRefreshView : function (
capulltorefreshview 
)
{
},

/**
 * @method isBounceVertical
 * @return {bool}
 */
isBounceVertical : function (
)
{
    return false;
},

/**
 * @method addSubview
 * @param {ca.CAView} arg0
 */
addSubview : function (
caview 
)
{
},

/**
 * @method setShowsVerticalScrollIndicator
 * @param {bool} arg0
 */
setShowsVerticalScrollIndicator : function (
bool 
)
{
},

/**
 * @method setContentOffset
 * @param {point_object} arg0
 * @param {bool} arg1
 */
setContentOffset : function (
dpoint, 
bool 
)
{
},

/**
 * @method setStopMovedCallback
 * @param {function} arg0
 */
setStopMovedCallback : function (
func 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method isShowsVerticalScrollIndicator
 * @return {bool}
 */
isShowsVerticalScrollIndicator : function (
)
{
    return false;
},

/**
 * @method startPullToHeaderRefreshView
 */
startPullToHeaderRefreshView : function (
)
{
},

/**
 * @method getSubviews
 * @return {Array}
 */
getSubviews : function (
)
{
    return new Array();
},

/**
 * @method getMultitouchGesture
 * @return {ca.CAScrollView::MultitouchGesture}
 */
getMultitouchGesture : function (
)
{
    return 0;
},

/**
 * @method setHeaderRefreshView
 * @param {ca.CAPullToRefreshView} arg0
 */
setHeaderRefreshView : function (
capulltorefreshview 
)
{
},

/**
 * @method startDeaccelerateScroll
 */
startDeaccelerateScroll : function (
)
{
},

/**
 * @method getScrollViewDelegate
 * @return {ca.CAScrollViewDelegate}
 */
getScrollViewDelegate : function (
)
{
    return ca.CAScrollViewDelegate;
},

/**
 * @method setBounces
 * @param {bool} arg0
 */
setBounces : function (
bool 
)
{
},

/**
 * @method getContentOffset
 * @return {point_object}
 */
getContentOffset : function (
)
{
    return ca.DPoint;
},

/**
 * @method setViewSize
 * @param {size_object} arg0
 */
setViewSize : function (
dsize 
)
{
},

/**
 * @method setWillBeginDraggingCallback
 * @param {function} arg0
 */
setWillBeginDraggingCallback : function (
func 
)
{
},

/**
 * @method setShowsScrollIndicators
 * @param {bool} arg0
 */
setShowsScrollIndicators : function (
bool 
)
{
},

/**
 * @method removeSubviewByTag
 * @param {int} arg0
 */
removeSubviewByTag : function (
int 
)
{
},

/**
 * @method getSubviewByTag
 * @param {int} arg0
 * @return {ca.CAView}
 */
getSubviewByTag : function (
int 
)
{
    return ca.CAView;
},

/**
 * @method isBounces
 * @return {bool}
 */
isBounces : function (
)
{
    return false;
},

/**
 * @method setBackgroundColor
 * @param {color4b_object} arg0
 */
setBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method getMaximumZoomScale
 * @return {float}
 */
getMaximumZoomScale : function (
)
{
    return 0;
},

/**
 * @method getViewSize
 * @return {size_object}
 */
getViewSize : function (
)
{
    return ca.DSize;
},

/**
 * @method setMaximumZoomScale
 * @param {float} arg0
 */
setMaximumZoomScale : function (
float 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method isReachBoundaryDown
 * @return {bool}
 */
isReachBoundaryDown : function (
)
{
    return false;
},

/**
 * @method setFooterBeginRefreshingCallback
 * @param {function} arg0
 */
setFooterBeginRefreshingCallback : function (
func 
)
{
},

/**
 * @method setBackgroundImage
 * @param {ca.CAImage} arg0
 */
setBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setTouchUpWithoutMovedCallback
 * @param {function} arg0
 */
setTouchUpWithoutMovedCallback : function (
func 
)
{
},

/**
 * @method setHeaderBeginRefreshingCallback
 * @param {function} arg0
 */
setHeaderBeginRefreshingCallback : function (
func 
)
{
},

/**
 * @method switchPCMode
 * @param {bool} arg0
 */
switchPCMode : function (
bool 
)
{
},

/**
 * @method isReachBoundaryUp
 * @return {bool}
 */
isReachBoundaryUp : function (
)
{
    return false;
},

/**
 * @method isReachBoundaryLeft
 * @return {bool}
 */
isReachBoundaryLeft : function (
)
{
    return false;
},

/**
 * @method getFooterRefreshView
 * @return {ca.CAPullToRefreshView}
 */
getFooterRefreshView : function (
)
{
    return ca.CAPullToRefreshView;
},

/**
 * @method setShowsHorizontalScrollIndicator
 * @param {bool} arg0
 */
setShowsHorizontalScrollIndicator : function (
bool 
)
{
},

/**
 * @method stopDeaccelerateScroll
 */
stopDeaccelerateScroll : function (
)
{
},

/**
 * @method setDraggingCallback
 * @param {function} arg0
 */
setDraggingCallback : function (
func 
)
{
},

/**
 * @method isDecelerating
 * @return {bool}
 */
isDecelerating : function (
)
{
    return false;
},

/**
 * @method isTouchEnabledAtSubviews
 * @return {bool}
 */
isTouchEnabledAtSubviews : function (
)
{
    return false;
},

/**
 * @method isReachBoundaryRight
 * @return {bool}
 */
isReachBoundaryRight : function (
)
{
    return false;
},

/**
 * @method setDidEndDraggingCallback
 * @param {function} arg0
 */
setDidEndDraggingCallback : function (
func 
)
{
},

/**
 * @method setMinimumZoomScale
 * @param {float} arg0
 */
setMinimumZoomScale : function (
float 
)
{
},

/**
 * @method endHeaderRefresh
 */
endHeaderRefresh : function (
)
{
},

/**
 * @method getMinimumZoomScale
 * @return {float}
 */
getMinimumZoomScale : function (
)
{
    return 0;
},

/**
 * @method setBounceHorizontal
 * @param {bool} arg0
 */
setBounceHorizontal : function (
bool 
)
{
},

/**
 * @method removeSubview
 * @param {ca.CAView} arg0
 */
removeSubview : function (
caview 
)
{
},

/**
 * @method setZoomScale
 * @param {float} arg0
 */
setZoomScale : function (
float 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method setMultitouchGesture
 * @param {ca.CAScrollView::MultitouchGesture} arg0
 */
setMultitouchGesture : function (
multitouchgesture 
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAScrollView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAScrollView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAScrollView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAScrollView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAScrollView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAScrollView;
},

/**
 * @method CAScrollView
 * @constructor
 */
CAScrollView : function (
)
{
},

};

/**
 * @class CAPageView
 */
ca.CAPageView = {

/**
 * @method setSpacing
 * @param {int} arg0
 */
setSpacing : function (
int 
)
{
},

/**
 * @method setEndTurningCallback
 * @param {function} arg0
 */
setEndTurningCallback : function (
func 
)
{
},

/**
 * @method getPageCount
 * @return {unsigned int}
 */
getPageCount : function (
)
{
    return 0;
},

/**
 * @method getOrientation
 * @return {CAPageView::Orientation}
 */
getOrientation : function (
)
{
    return CAPageView::Orientation;
},

/**
 * @method getSpacing
 * @return {int}
 */
getSpacing : function (
)
{
    return 0;
},

/**
 * @method getCurrPage
 * @return {int}
 */
getCurrPage : function (
)
{
    return 0;
},

/**
 * @method setCurrPage
 * @param {int} arg0
 * @param {bool} arg1
 * @param {bool} arg2
 */
setCurrPage : function (
int, 
bool, 
bool 
)
{
},

/**
 * @method getPageViewDelegate
 * @return {CAPageViewDelegate}
 */
getPageViewDelegate : function (
)
{
    return CAPageViewDelegate;
},

/**
 * @method setDidSelectedPageAtIndexCallback
 * @param {function} arg0
 */
setDidSelectedPageAtIndexCallback : function (
func 
)
{
},

/**
 * @method setBeginTurningCallback
 * @param {function} arg0
 */
setBeginTurningCallback : function (
func 
)
{
},

/**
 * @method getSubViewAtIndex
 * @param {int} arg0
 * @return {ca.CAView}
 */
getSubViewAtIndex : function (
int 
)
{
    return ca.CAView;
},

/**
 * @method setViews
* @param {Array|ca.CADeque<ca.CAView >} array
*/
setViews : function(
cadeque<crossapp::caview > 
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {CAPageView::Orientation} arg1
 * @return {CAPageView}
 */
createWithFrame : function (
drect, 
orientation 
)
{
    return CAPageView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {CAPageView::Orientation} arg1
 * @return {CAPageView}
 */
createWithLayout : function (
dlayout, 
orientation 
)
{
    return CAPageView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {CAPageView::Orientation} arg1
 * @return {CAPageView}
 */
createWithCenter : function (
drect, 
orientation 
)
{
    return CAPageView;
},

/**
 * @method CAPageView
 * @constructor
 * @param {CAPageView::Orientation} arg0
 */
CAPageView : function (
orientation 
)
{
},

};

/**
 * @class CAViewController
 */
ca.CAViewController = {

/**
 * @method getView
 * @return {ca.CAView}
 */
getView : function (
)
{
    return ca.CAView;
},

/**
 * @method dismissModalViewController
 * @param {bool} arg0
 */
dismissModalViewController : function (
bool 
)
{
},

/**
 * @method getTabBarItem
 * @return {ca.CATabBarItem}
 */
getTabBarItem : function (
)
{
    return ca.CATabBarItem;
},

/**
 * @method keyBackClicked
 */
keyBackClicked : function (
)
{
},

/**
 * @method setTabBarItem
 * @param {ca.CATabBarItem} arg0
 */
setTabBarItem : function (
catabbaritem 
)
{
},

/**
 * @method getViewWithID
 * @param {String} arg0
 * @return {ca.CAView}
 */
getViewWithID : function (
str 
)
{
    return ca.CAView;
},

/**
 * @method setTitle
 * @param {String} arg0
 */
setTitle : function (
str 
)
{
},

/**
 * @method isKeypadEnabled
 * @return {bool}
 */
isKeypadEnabled : function (
)
{
    return false;
},

/**
 * @method isViewRunning
 * @return {bool}
 */
isViewRunning : function (
)
{
    return false;
},

/**
 * @method viewDidLoad
 */
viewDidLoad : function (
)
{
},

/**
 * @method presentModalViewController
 * @param {ca.CAViewController} arg0
 * @param {bool} arg1
 */
presentModalViewController : function (
caviewcontroller, 
bool 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getNavigationBarItem
 * @return {ca.CANavigationBarItem}
 */
getNavigationBarItem : function (
)
{
    return ca.CANavigationBarItem;
},

/**
 * @method removeViewFromSuperview
 */
removeViewFromSuperview : function (
)
{
},

/**
 * @method viewDidDisappear
 */
viewDidDisappear : function (
)
{
},

/**
 * @method getNibName
 * @return {String}
 */
getNibName : function (
)
{
    return ;
},

/**
 * @method setNavigationBarItem
 * @param {ca.CANavigationBarItem} arg0
 */
setNavigationBarItem : function (
canavigationbaritem 
)
{
},

/**
 * @method getTitle
 * @return {String}
 */
getTitle : function (
)
{
    return ;
},

/**
 * @method viewDidAppear
 */
viewDidAppear : function (
)
{
},

/**
 * @method addViewFromSuperview
 * @param {ca.CAView} arg0
 */
addViewFromSuperview : function (
caview 
)
{
},

/**
 * @method viewSizeDidChanged
 */
viewSizeDidChanged : function (
)
{
},

/**
 * @method getNavigationController
 * @return {ca.CANavigationController}
 */
getNavigationController : function (
)
{
    return ca.CANavigationController;
},

/**
 * @method getTabBarController
 * @return {ca.CATabBarController}
 */
getTabBarController : function (
)
{
    return ca.CATabBarController;
},

/**
 * @method viewDidUnload
 */
viewDidUnload : function (
)
{
},

/**
 * @method setKeypadEnabled
 * @param {bool} arg0
 */
setKeypadEnabled : function (
bool 
)
{
},

/**
 * @method keyMenuClicked
 */
keyMenuClicked : function (
)
{
},

/**
 * @method CAViewController
 * @constructor
 */
CAViewController : function (
)
{
},

};

/**
 * @class CANavigationController
 */
ca.CANavigationController = {

/**
 * @method setNavigationBarTitleColor
 * @param {color4b_object} arg0
 */
setNavigationBarTitleColor : function (
cacolor4b 
)
{
},

/**
 * @method setNavigationBarButtonColor
 * @param {color4b_object} arg0
 */
setNavigationBarButtonColor : function (
cacolor4b 
)
{
},

/**
 * @method updateItem
 * @param {ca.CAViewController} arg0
 */
updateItem : function (
caviewcontroller 
)
{
},

/**
 * @method getBackViewController
 * @return {ca.CAViewController}
 */
getBackViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method getNavigationBarBackgroundColor
 * @return {color4b_object}
 */
getNavigationBarBackgroundColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getViewControllerCount
 * @return {unsigned long}
 */
getViewControllerCount : function (
)
{
    return 0;
},

/**
 * @method setNavigationBarHidden
 * @param {bool} arg0
 * @param {bool} arg1
 */
setNavigationBarHidden : function (
bool, 
bool 
)
{
},

/**
 * @method replaceViewController
 * @param {ca.CAViewController} arg0
 * @param {bool} arg1
 */
replaceViewController : function (
caviewcontroller, 
bool 
)
{
},

/**
 * @method popToRootViewControllerAnimated
 * @param {bool} arg0
 */
popToRootViewControllerAnimated : function (
bool 
)
{
},

/**
 * @method getNavigationBarGoBackBarButtonItem
 * @return {ca.CABarButtonItem}
 */
getNavigationBarGoBackBarButtonItem : function (
)
{
    return ca.CABarButtonItem;
},

/**
 * @method pushViewController
 * @param {ca.CAViewController} arg0
 * @param {bool} arg1
 */
pushViewController : function (
caviewcontroller, 
bool 
)
{
},

/**
 * @method isReachBoundaryDown
 * @return {bool}
 */
isReachBoundaryDown : function (
)
{
    return false;
},

/**
 * @method setTouchMoved
 * @param {bool} arg0
 */
setTouchMoved : function (
bool 
)
{
},

/**
 * @method initWithRootViewController
 * @param {ca.CAViewController} arg0
 * @return {bool}
 */
initWithRootViewController : function (
caviewcontroller 
)
{
    return false;
},

/**
 * @method isReachBoundaryRight
 * @return {bool}
 */
isReachBoundaryRight : function (
)
{
    return false;
},

/**
 * @method popViewControllerAnimated
 * @param {bool} arg0
 * @return {ca.CAViewController}
 */
popViewControllerAnimated : function (
bool 
)
{
    return ca.CAViewController;
},

/**
 * @method getNavigationBarButtonColor
 * @return {color4b_object}
 */
getNavigationBarButtonColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method isTouchMoved
 * @return {bool}
 */
isTouchMoved : function (
)
{
    return false;
},

/**
 * @method getNavigationBarTitleColor
 * @return {color4b_object}
 */
getNavigationBarTitleColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method isReachBoundaryUp
 * @return {bool}
 */
isReachBoundaryUp : function (
)
{
    return false;
},

/**
 * @method isReachBoundaryLeft
 * @return {bool}
 */
isReachBoundaryLeft : function (
)
{
    return false;
},

/**
 * @method setNavigationBarBackgroundColor
 * @param {color4b_object} arg0
 */
setNavigationBarBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method setNavigationBarGoBackBarButtonItem
 * @param {ca.CABarButtonItem} arg0
 */
setNavigationBarGoBackBarButtonItem : function (
cabarbuttonitem 
)
{
},

/**
 * @method isNavigationBarHidden
 * @return {bool}
 */
isNavigationBarHidden : function (
)
{
    return false;
},

/**
 * @method getNavigationBarBackgroundImage
 * @return {ca.CAImage}
 */
getNavigationBarBackgroundImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method getViewControllerAtIndex
 * @param {int} arg0
 * @return {ca.CAViewController}
 */
getViewControllerAtIndex : function (
int 
)
{
    return ca.CAViewController;
},

/**
 * @method setNavigationBarBackgroundImage
 * @param {ca.CAImage} arg0
 */
setNavigationBarBackgroundImage : function (
caimage 
)
{
},

/**
 * @method popFirstViewController
 * @return {ca.CAViewController}
 */
popFirstViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method popViewControllerAtIndex
 * @param {int} arg0
 * @return {ca.CAViewController}
 */
popViewControllerAtIndex : function (
int 
)
{
    return ca.CAViewController;
},

/**
 * @method CANavigationController
 * @constructor
 */
CANavigationController : function (
)
{
},

};

/**
 * @class CATabBarController
 */
ca.CATabBarController = {

/**
 * @method getSelectedViewController
 * @return {ca.CAViewController}
 */
getSelectedViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method setTabBarSelectedBackgroundImage
 * @param {ca.CAImage} arg0
 */
setTabBarSelectedBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setTabBarBackgroundImage
 * @param {ca.CAImage} arg0
 */
setTabBarBackgroundImage : function (
caimage 
)
{
},

/**
 * @method isScrollEnabled
 * @return {bool}
 */
isScrollEnabled : function (
)
{
    return false;
},

/**
 * @method setTabBarTitleColorForSelected
 * @param {color4b_object} arg0
 */
setTabBarTitleColorForSelected : function (
cacolor4b 
)
{
},

/**
 * @method showSelectedViewControllerAtIndex
 * @param {unsigned int} arg0
 * @return {bool}
 */
showSelectedViewControllerAtIndex : function (
int 
)
{
    return false;
},

/**
 * @method setTabBarHidden
 * @param {bool} arg0
 * @param {bool} arg1
 */
setTabBarHidden : function (
bool, 
bool 
)
{
},

/**
 * @method updateItem
 * @param {ca.CAViewController} arg0
 */
updateItem : function (
caviewcontroller 
)
{
},

/**
 * @method setTabBarTitleColorForNormal
 * @param {color4b_object} arg0
 */
setTabBarTitleColorForNormal : function (
cacolor4b 
)
{
},

/**
 * @method setTabBarSelectedIndicatorImage
 * @param {ca.CAImage} arg0
 */
setTabBarSelectedIndicatorImage : function (
caimage 
)
{
},

/**
 * @method getTabBarTitleColorForSelected
 * @return {color4b_object}
 */
getTabBarTitleColorForSelected : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getSelectedViewControllerAtIndex
 * @return {unsigned int}
 */
getSelectedViewControllerAtIndex : function (
)
{
    return 0;
},

/**
 * @method getTabBarSelectedBackgroundColor
 * @return {color4b_object}
 */
getTabBarSelectedBackgroundColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setScrollEnabled
 * @param {bool} arg0
 */
setScrollEnabled : function (
bool 
)
{
},

/**
 * @method showSelectedViewController
 * @param {ca.CAViewController} arg0
 * @return {bool}
 */
showSelectedViewController : function (
caviewcontroller 
)
{
    return false;
},

/**
 * @method getTabBarSelectedBackgroundImage
 * @return {ca.CAImage}
 */
getTabBarSelectedBackgroundImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setTabBarTitleBoldForSelected
 * @param {bool} arg0
 */
setTabBarTitleBoldForSelected : function (
bool 
)
{
},

/**
 * @method getTabBarBackgroundColor
 * @return {color4b_object}
 */
getTabBarBackgroundColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getTabBarBackgroundImage
 * @return {ca.CAImage}
 */
getTabBarBackgroundImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method getTabBarVerticalAlignment
 * @return {ca.CABarVerticalAlignment}
 */
getTabBarVerticalAlignment : function (
)
{
    return 0;
},

/**
 * @method getTabBarSelectedIndicatorColor
 * @return {color4b_object}
 */
getTabBarSelectedIndicatorColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getTabBarTitleBoldForSelected
 * @return {bool}
 */
getTabBarTitleBoldForSelected : function (
)
{
    return false;
},

/**
 * @method setTabBarSelectedIndicatorColor
 * @param {color4b_object} arg0
 */
setTabBarSelectedIndicatorColor : function (
cacolor4b 
)
{
},

/**
 * @method showTabBarSelectedIndicator
 */
showTabBarSelectedIndicator : function (
)
{
},

/**
 * @method getTabBarSelectedIndicatorImage
 * @return {ca.CAImage}
 */
getTabBarSelectedIndicatorImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method initWithViewControllers
 * @param {Array} arg0
 * @param {ca.CABarVerticalAlignment} arg1
 * @return {bool}
 */
initWithViewControllers : function (
array, 
cabarverticalalignment 
)
{
    return false;
},

/**
 * @method getTabBarTitleColorForNormal
 * @return {color4b_object}
 */
getTabBarTitleColorForNormal : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getViewControllerAtIndex
 * @param {unsigned int} arg0
 * @return {ca.CAViewController}
 */
getViewControllerAtIndex : function (
int 
)
{
    return ca.CAViewController;
},

/**
 * @method setTabBarBackgroundColor
 * @param {color4b_object} arg0
 */
setTabBarBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method setTabBarSelectedBackgroundColor
 * @param {color4b_object} arg0
 */
setTabBarSelectedBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method isTabBarHidden
 * @return {bool}
 */
isTabBarHidden : function (
)
{
    return false;
},

/**
 * @method CATabBarController
 * @constructor
 */
CATabBarController : function (
)
{
},

};

/**
 * @class CAWindow
 */
ca.CAWindow = {

/**
 * @method presentModalViewController
 * @param {ca.CAViewController} arg0
 * @param {bool} arg1
 */
presentModalViewController : function (
caviewcontroller, 
bool 
)
{
},

/**
 * @method setCameraOrderDirty
 */
setCameraOrderDirty : function (
)
{
},

/**
 * @method render
 * @param {ca.Renderer} arg0
 * @param {ca.Mat4} arg1
 * @param {ca.Mat4} arg2
 */
render : function (
renderer, 
mat4, 
mat4 
)
{
},

/**
 * @method dismissModalViewController
 * @param {bool} arg0
 */
dismissModalViewController : function (
bool 
)
{
},

/**
 * @method getRootViewController
 * @return {ca.CAViewController}
 */
getRootViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method getModalViewController
 * @return {ca.CAViewController}
 */
getModalViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method setRootViewController
 * @param {ca.CAViewController} arg0
 */
setRootViewController : function (
caviewcontroller 
)
{
},

/**
 * @method getDefaultCamera
 * @return {ca.CACamera}
 */
getDefaultCamera : function (
)
{
    return ca.CACamera;
},

/**
 * @method create
 * @return {ca.CAWindow}
 */
create : function (
)
{
    return ca.CAWindow;
},

/**
 * @method CAWindow
 * @constructor
 */
CAWindow : function (
)
{
},

};

/**
 * @class CANotificationCenter
 */
ca.CANotificationCenter = {

/**
 * @method postNotificationWithIntValue
 * @param {String} arg0
 * @param {int} arg1
 */
postNotificationWithIntValue : function (
str, 
int 
)
{
},

/**
 * @method postNotification
* @param {String|String} str
* @param {ca.CAObject} caobject
*/
postNotification : function(
str,
caobject 
)
{
},

/**
 * @method postNotificationWithStringValue
 * @param {String} arg0
 * @param {String} arg1
 */
postNotificationWithStringValue : function (
str, 
str 
)
{
},

/**
 * @method removeObserver
 * @param {ca.CAObject} arg0
 * @param {String} arg1
 */
removeObserver : function (
caobject, 
str 
)
{
},

/**
 * @method getObserverHandlerByName
 * @param {String} arg0
 * @return {int}
 */
getObserverHandlerByName : function (
str 
)
{
    return 0;
},

/**
 * @method removeAllObservers
 * @param {ca.CAObject} arg0
 * @return {int}
 */
removeAllObservers : function (
caobject 
)
{
    return 0;
},

/**
 * @method postNotificationWithDoubleValue
 * @param {String} arg0
 * @param {double} arg1
 */
postNotificationWithDoubleValue : function (
str, 
double 
)
{
},

/**
 * @method unregisterScriptObserver
 * @param {ca.CAObject} arg0
 * @param {String} arg1
 */
unregisterScriptObserver : function (
caobject, 
str 
)
{
},

/**
 * @method postNotificationWithFloatValue
 * @param {String} arg0
 * @param {float} arg1
 */
postNotificationWithFloatValue : function (
str, 
float 
)
{
},

/**
 * @method getScriptHandler
 * @return {int}
 */
getScriptHandler : function (
)
{
    return 0;
},

/**
 * @method addObserver
 * @param {function} arg0
 * @param {ca.CAObject} arg1
 * @param {String} arg2
 */
addObserver : function (
func, 
caobject, 
str 
)
{
},

/**
 * @method registerScriptObserver
 * @param {ca.CAObject} arg0
 * @param {String} arg1
 * @param {int} arg2
 */
registerScriptObserver : function (
caobject, 
str, 
int 
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {ca.CANotificationCenter}
 */
getInstance : function (
)
{
    return ca.CANotificationCenter;
},

/**
 * @method CANotificationCenter
 * @constructor
 */
CANotificationCenter : function (
)
{
},

};

/**
 * @class CARenderImage
 */
ca.CARenderImage = {

/**
 * @method getImageView
 * @return {ca.CAImageView}
 */
getImageView : function (
)
{
    return ca.CAImageView;
},

/**
 * @method printscreenWithView
* @param {ca.CAView|ca.CAView|ca.CAView|ca.CAView} caview
* @param {point_object|color4b_object|point_object} dpoint
* @param {color4b_object} cacolor4b
*/
printscreenWithView : function(
caview,
dpoint,
cacolor4b 
)
{
},

/**
 * @method getClearStencil
 * @return {int}
 */
getClearStencil : function (
)
{
    return 0;
},

/**
 * @method saveToFile
 * @param {char} arg0
 * @return {bool}
 */
saveToFile : function (
char 
)
{
    return false;
},

/**
 * @method setClearStencil
 * @param {float} arg0
 */
setClearStencil : function (
float 
)
{
},

/**
 * @method setClearFlags
 * @param {unsigned int} arg0
 */
setClearFlags : function (
int 
)
{
},

/**
 * @method setImageView
 * @param {ca.CAImageView} arg0
 */
setImageView : function (
caimageview 
)
{
},

/**
 * @method initWithWidthAndHeight
* @param {int|int} int
* @param {int|int} int
* @param {ca.CAImage::PixelFormat|ca.CAImage::PixelFormat} pixelformat
* @param {unsigned int} int
* @return {bool|bool}
*/
initWithWidthAndHeight : function(
int,
int,
pixelformat,
int 
)
{
    return false;
},

/**
 * @method setAutoDraw
 * @param {bool} arg0
 */
setAutoDraw : function (
bool 
)
{
},

/**
 * @method setClearColor
 * @param {color4f_object} arg0
 */
setClearColor : function (
cacolor4f 
)
{
},

/**
 * @method getClearColor
 * @return {color4f_object}
 */
getClearColor : function (
)
{
    return ca.CAColor4F;
},

/**
 * @method getClearFlags
 * @return {unsigned int}
 */
getClearFlags : function (
)
{
    return 0;
},

/**
 * @method isAutoDraw
 * @return {bool}
 */
isAutoDraw : function (
)
{
    return false;
},

/**
 * @method setClearDepth
 * @param {float} arg0
 */
setClearDepth : function (
float 
)
{
},

/**
 * @method getClearDepth
 * @return {float}
 */
getClearDepth : function (
)
{
    return 0;
},

/**
 * @method create
* @param {int|int|int} int
* @param {int|int|int} int
* @param {ca.CAImage::PixelFormat|ca.CAImage::PixelFormat} pixelformat
* @param {unsigned int} int
* @return {ca.CARenderImage|ca.CARenderImage|ca.CARenderImage}
*/
create : function(
int,
int,
pixelformat,
int 
)
{
    return ca.CARenderImage;
},

/**
 * @method CARenderImage
 * @constructor
 */
CARenderImage : function (
)
{
},

};

/**
 * @class CAProgress
 */
ca.CAProgress = {

/**
 * @method setProgressTintImage
 * @param {ca.CAImage} arg0
 */
setProgressTintImage : function (
caimage 
)
{
},

/**
 * @method getProgressTintImage
 * @return {ca.CAImage}
 */
getProgressTintImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setProgressTrackColor
 * @param {color4b_object} arg0
 */
setProgressTrackColor : function (
cacolor4b 
)
{
},

/**
 * @method setColor
 * @param {color4b_object} arg0
 */
setColor : function (
cacolor4b 
)
{
},

/**
 * @method setProgressTrackImage
 * @param {ca.CAImage} arg0
 */
setProgressTrackImage : function (
caimage 
)
{
},

/**
 * @method getProgressTintColor
 * @return {color4b_object}
 */
getProgressTintColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getProgressTrackImage
 * @return {ca.CAImage}
 */
getProgressTrackImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method getProgressTrackColor
 * @return {color4b_object}
 */
getProgressTrackColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getProgress
 * @return {float}
 */
getProgress : function (
)
{
    return 0;
},

/**
 * @method setProgress
 * @param {float} arg0
 * @param {bool} arg1
 */
setProgress : function (
float, 
bool 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method setProgressTintColor
 * @param {color4b_object} arg0
 */
setProgressTintColor : function (
cacolor4b 
)
{
},

/**
 * @method create
 * @return {ca.CAProgress}
 */
create : function (
)
{
    return ca.CAProgress;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAProgress}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAProgress;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAProgress}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAProgress;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAProgress}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAProgress;
},

/**
 * @method CAProgress
 * @constructor
 */
CAProgress : function (
)
{
},

};

/**
 * @class CASwitch
 */
ca.CASwitch = {

/**
 * @method getOnImage
 * @return {ca.CAImage}
 */
getOnImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setOffImage
 * @param {ca.CAImage} arg0
 */
setOffImage : function (
caimage 
)
{
},

/**
 * @method setTarget
 * @param {function} arg0
 */
setTarget : function (
func 
)
{
},

/**
 * @method getThumbTintImage
 * @return {ca.CAImage}
 */
getThumbTintImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setIsOn
 * @param {bool} arg0
 * @param {bool} arg1
 */
setIsOn : function (
bool, 
bool 
)
{
},

/**
 * @method isOn
* @return {bool|bool}
*/
isOn : function(
)
{
    return false;
},

/**
 * @method setOnImage
 * @param {ca.CAImage} arg0
 */
setOnImage : function (
caimage 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getOffImage
 * @return {ca.CAImage}
 */
getOffImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method setThumbTintImage
 * @param {ca.CAImage} arg0
 */
setThumbTintImage : function (
caimage 
)
{
},

/**
 * @method create
 * @param {ca.CASwitch::Type} arg0
 * @return {ca.CASwitch}
 */
create : function (
type 
)
{
    return ca.CASwitch;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {ca.CASwitch::Type} arg1
 * @return {ca.CASwitch}
 */
createWithFrame : function (
drect, 
type 
)
{
    return ca.CASwitch;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {ca.CASwitch::Type} arg1
 * @return {ca.CASwitch}
 */
createWithLayout : function (
dlayout, 
type 
)
{
    return ca.CASwitch;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {ca.CASwitch::Type} arg1
 * @return {ca.CASwitch}
 */
createWithCenter : function (
drect, 
type 
)
{
    return ca.CASwitch;
},

/**
 * @method CASwitch
 * @constructor
 * @param {ca.CASwitch::Type} arg0
 */
CASwitch : function (
type 
)
{
},

};

/**
 * @class CASlider
 */
ca.CASlider = {

/**
 * @method setTargetForTouchUpSide
 * @param {function} arg0
 */
setTargetForTouchUpSide : function (
func 
)
{
},

/**
 * @method initWithCenter
 * @param {rect_object} arg0
 * @return {bool}
 */
initWithCenter : function (
drect 
)
{
    return false;
},

/**
 * @method getTrackHeight
 * @return {float}
 */
getTrackHeight : function (
)
{
    return 0;
},

/**
 * @method setMinValue
 * @param {float} arg0
 */
setMinValue : function (
float 
)
{
},

/**
 * @method getMinValue
 * @return {float}
 */
getMinValue : function (
)
{
    return 0;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getMaxValue
 * @return {float}
 */
getMaxValue : function (
)
{
    return 0;
},

/**
 * @method setMaxTrackTintImage
 * @param {ca.CAImage} arg0
 */
setMaxTrackTintImage : function (
caimage 
)
{
},

/**
 * @method setValue
 * @param {float} arg0
 */
setValue : function (
float 
)
{
},

/**
 * @method isTouchClick
 * @return {bool}
 */
isTouchClick : function (
)
{
    return false;
},

/**
 * @method initWithFrame
 * @param {rect_object} arg0
 * @return {bool}
 */
initWithFrame : function (
drect 
)
{
    return false;
},

/**
 * @method setTarget
 * @param {function} arg0
 */
setTarget : function (
func 
)
{
},

/**
 * @method layoutSubViews
 */
layoutSubViews : function (
)
{
},

/**
 * @method getMaxTrackTintImage
 * @return {ca.CAImage}
 */
getMaxTrackTintImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setThumbTintImage
 * @param {ca.CAImage} arg0
 */
setThumbTintImage : function (
caimage 
)
{
},

/**
 * @method getMinTrackTintImage
 * @return {ca.CAImage}
 */
getMinTrackTintImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setTrackHeight
 * @param {float} arg0
 */
setTrackHeight : function (
float 
)
{
},

/**
 * @method getThumbTintImage
 * @return {ca.CAImage}
 */
getThumbTintImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setMaxValue
 * @param {float} arg0
 */
setMaxValue : function (
float 
)
{
},

/**
 * @method getValue
 * @return {float}
 */
getValue : function (
)
{
    return 0;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method setMinTrackTintImage
 * @param {ca.CAImage} arg0
 */
setMinTrackTintImage : function (
caimage 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method create
 * @return {ca.CASlider}
 */
create : function (
)
{
    return ca.CASlider;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CASlider}
 */
createWithFrame : function (
drect 
)
{
    return ca.CASlider;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CASlider}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CASlider;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CASlider}
 */
createWithCenter : function (
drect 
)
{
    return ca.CASlider;
},

/**
 * @method CASlider
 * @constructor
 */
CASlider : function (
)
{
},

};

/**
 * @class CAPageControl
 */
ca.CAPageControl = {

/**
 * @method setDefersCurrentPageDisplay
 * @param {bool} arg0
 */
setDefersCurrentPageDisplay : function (
bool 
)
{
},

/**
 * @method getPageIndicatorImage
 * @return {ca.CAImage}
 */
getPageIndicatorImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method initWithCenter
 * @param {rect_object} arg0
 * @return {bool}
 */
initWithCenter : function (
drect 
)
{
    return false;
},

/**
 * @method isSinglePage
 * @return {bool}
 */
isSinglePage : function (
)
{
    return false;
},

/**
 * @method setPageIndicatorImage
 * @param {ca.CAImage} arg0
 */
setPageIndicatorImage : function (
caimage 
)
{
},

/**
 * @method setNumberOfPages
 * @param {int} arg0
 */
setNumberOfPages : function (
int 
)
{
},

/**
 * @method getNumberOfPages
 * @return {int}
 */
getNumberOfPages : function (
)
{
    return 0;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setTouchEnabled
 * @param {bool} arg0
 */
setTouchEnabled : function (
bool 
)
{
},

/**
 * @method setPageIndicatorTintColor
 * @param {color4b_object} arg0
 */
setPageIndicatorTintColor : function (
cacolor4b 
)
{
},

/**
 * @method initWithFrame
 * @param {rect_object} arg0
 * @return {bool}
 */
initWithFrame : function (
drect 
)
{
    return false;
},

/**
 * @method setTarget
 * @param {function} arg0
 */
setTarget : function (
func 
)
{
},

/**
 * @method setSinglePage
 * @param {bool} arg0
 */
setSinglePage : function (
bool 
)
{
},

/**
 * @method getStyle
 * @return {ca.CAPageControl::Style}
 */
getStyle : function (
)
{
    return 0;
},

/**
 * @method getPageIndicatorTintColor
 * @return {color4b_object}
 */
getPageIndicatorTintColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setStyle
 * @param {ca.CAPageControl::Style} arg0
 */
setStyle : function (
style 
)
{
},

/**
 * @method isDefersCurrentPageDisplay
 * @return {bool}
 */
isDefersCurrentPageDisplay : function (
)
{
    return false;
},

/**
 * @method setCurrentPageIndicatorTintColor
 * @param {color4b_object} arg0
 */
setCurrentPageIndicatorTintColor : function (
cacolor4b 
)
{
},

/**
 * @method setCurrentPage
 * @param {int} arg0
 */
setCurrentPage : function (
int 
)
{
},

/**
 * @method updateCurrentPageDisplay
 */
updateCurrentPageDisplay : function (
)
{
},

/**
 * @method getCurrentPage
 * @return {int}
 */
getCurrentPage : function (
)
{
    return 0;
},

/**
 * @method getCurrentPageIndicatorTintColor
 * @return {color4b_object}
 */
getCurrentPageIndicatorTintColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setCurrIndicatorImage
 * @param {ca.CAImage} arg0
 */
setCurrIndicatorImage : function (
caimage 
)
{
},

/**
 * @method getCurrIndicatorImage
 * @return {ca.CAImage}
 */
getCurrIndicatorImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method create
 * @return {ca.CAPageControl}
 */
create : function (
)
{
    return ca.CAPageControl;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAPageControl}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAPageControl;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAPageControl}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAPageControl;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAPageControl}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAPageControl;
},

/**
 * @method CAPageControl
 * @constructor
 */
CAPageControl : function (
)
{
},

};

/**
 * @class CAStepper
 */
ca.CAStepper = {

/**
 * @method setContinuous
 * @param {bool} arg0
 */
setContinuous : function (
bool 
)
{
},

/**
 * @method setWraps
 * @param {bool} arg0
 */
setWraps : function (
bool 
)
{
},

/**
 * @method setValue
 * @param {float} arg0
 */
setValue : function (
float 
)
{
},

/**
 * @method setTailorImageAtIndex
 * @param {int} arg0
 */
setTailorImageAtIndex : function (
int 
)
{
},

/**
 * @method getContinuous
 * @return {bool}
 */
getContinuous : function (
)
{
    return false;
},

/**
 * @method getTailorImageAtIndex
 * @param {int} arg0
 * @return {ca.CAView}
 */
getTailorImageAtIndex : function (
int 
)
{
    return ca.CAView;
},

/**
 * @method getAutoRepeat
 * @return {bool}
 */
getAutoRepeat : function (
)
{
    return false;
},

/**
 * @method setMinValue
 * @param {float} arg0
 */
setMinValue : function (
float 
)
{
},

/**
 * @method getMinValue
 * @return {float}
 */
getMinValue : function (
)
{
    return 0;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setDividerColor
 * @param {color4b_object} arg0
 */
setDividerColor : function (
cacolor4b 
)
{
},

/**
 * @method getMaxValue
 * @return {float}
 */
getMaxValue : function (
)
{
    return 0;
},

/**
 * @method setDecrementImage
 * @param {ca.CAControl::State} arg0
 * @param {ca.CAImage} arg1
 */
setDecrementImage : function (
state, 
caimage 
)
{
},

/**
 * @method getWraps
 * @return {bool}
 */
getWraps : function (
)
{
    return false;
},

/**
 * @method setStepValue
 * @param {float} arg0
 */
setStepValue : function (
float 
)
{
},

/**
 * @method setBackgroundImage
 * @param {ca.CAControl::State} arg0
 * @param {ca.CAImage} arg1
 */
setBackgroundImage : function (
state, 
caimage 
)
{
},

/**
 * @method setTarget
 * @param {function} arg0
 */
setTarget : function (
func 
)
{
},

/**
 * @method setAutoRepeat
 * @param {bool} arg0
 */
setAutoRepeat : function (
bool 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getDividerColor
 * @return {color4b_object}
 */
getDividerColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setTouchEffect
 * @param {bool} arg0
 */
setTouchEffect : function (
bool 
)
{
},

/**
 * @method setIncrementImage
 * @param {ca.CAControl::State} arg0
 * @param {ca.CAImage} arg1
 */
setIncrementImage : function (
state, 
caimage 
)
{
},

/**
 * @method getStepValue
 * @return {float}
 */
getStepValue : function (
)
{
    return 0;
},

/**
 * @method setMaxValue
 * @param {float} arg0
 */
setMaxValue : function (
float 
)
{
},

/**
 * @method getValue
 * @return {float}
 */
getValue : function (
)
{
    return 0;
},

/**
 * @method getTouchEffect
 * @return {bool}
 */
getTouchEffect : function (
)
{
    return false;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method create
 * @return {ca.CAStepper}
 */
create : function (
)
{
    return ca.CAStepper;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {ca.CAStepper::Orientation} arg1
 * @return {ca.CAStepper}
 */
createWithFrame : function (
drect, 
orientation 
)
{
    return ca.CAStepper;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {ca.CAStepper::Orientation} arg1
 * @return {ca.CAStepper}
 */
createWithLayout : function (
dlayout, 
orientation 
)
{
    return ca.CAStepper;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {ca.CAStepper::Orientation} arg1
 * @return {ca.CAStepper}
 */
createWithCenter : function (
drect, 
orientation 
)
{
    return ca.CAStepper;
},

/**
 * @method CAStepper
 * @constructor
 */
CAStepper : function (
)
{
},

};

/**
 * @class CACheckbox
 */
ca.CACheckbox = {

/**
 * @method setImageSize
 * @param {size_object} arg0
 */
setImageSize : function (
dsize 
)
{
},

/**
 * @method setTitleFontSize
 * @param {float} arg0
 */
setTitleFontSize : function (
float 
)
{
},

/**
 * @method setTitleColorStateSelected
 * @param {color4b_object} arg0
 */
setTitleColorStateSelected : function (
cacolor4b 
)
{
},

/**
 * @method setTitleStateSelected
 * @param {String} arg0
 */
setTitleStateSelected : function (
str 
)
{
},

/**
 * @method setTitleTextAlignment
 * @param {ca.CATextAlignment} arg0
 */
setTitleTextAlignment : function (
catextalignment 
)
{
},

/**
 * @method setImageColorStateSelected
 * @param {color4b_object} arg0
 */
setImageColorStateSelected : function (
cacolor4b 
)
{
},

/**
 * @method isOn
 * @return {bool}
 */
isOn : function (
)
{
    return false;
},

/**
 * @method getImageStateNormal
 * @return {ca.CAImage}
 */
getImageStateNormal : function (
)
{
    return ca.CAImage;
},

/**
 * @method setImageColorStateNormal
 * @param {color4b_object} arg0
 */
setImageColorStateNormal : function (
cacolor4b 
)
{
},

/**
 * @method setTitleLabelSize
 * @param {size_object} arg0
 */
setTitleLabelSize : function (
dsize 
)
{
},

/**
 * @method setImageStateSelected
 * @param {ca.CAImage} arg0
 */
setImageStateSelected : function (
caimage 
)
{
},

/**
 * @method setIsOn
 * @param {bool} arg0
 */
setIsOn : function (
bool 
)
{
},

/**
 * @method setTarget
 * @param {function} arg0
 */
setTarget : function (
func 
)
{
},

/**
 * @method getTitleStateNormal
 * @return {String}
 */
getTitleStateNormal : function (
)
{
    return ;
},

/**
 * @method setTitleFontName
 * @param {String} arg0
 */
setTitleFontName : function (
str 
)
{
},

/**
 * @method setTitleStateNormal
 * @param {String} arg0
 */
setTitleStateNormal : function (
str 
)
{
},

/**
 * @method setTitleOffset
 * @param {size_object} arg0
 */
setTitleOffset : function (
dsize 
)
{
},

/**
 * @method setTitleColorStateNormal
 * @param {color4b_object} arg0
 */
setTitleColorStateNormal : function (
cacolor4b 
)
{
},

/**
 * @method getImageStateSelected
 * @return {ca.CAImage}
 */
getImageStateSelected : function (
)
{
    return ca.CAImage;
},

/**
 * @method setTitleBold
 * @param {bool} arg0
 */
setTitleBold : function (
bool 
)
{
},

/**
 * @method setImageOffset
 * @param {size_object} arg0
 */
setImageOffset : function (
dsize 
)
{
},

/**
 * @method setImageStateNormal
 * @param {ca.CAImage} arg0
 */
setImageStateNormal : function (
caimage 
)
{
},

/**
 * @method getTitleStateSelected
 * @return {String}
 */
getTitleStateSelected : function (
)
{
    return ;
},

/**
 * @method create
 * @param {ca.CACheckbox::Type} arg0
 * @return {ca.CACheckbox}
 */
create : function (
type 
)
{
    return ca.CACheckbox;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {ca.CACheckbox::Type} arg1
 * @return {ca.CACheckbox}
 */
createWithFrame : function (
drect, 
type 
)
{
    return ca.CACheckbox;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {ca.CACheckbox::Type} arg1
 * @return {ca.CACheckbox}
 */
createWithLayout : function (
dlayout, 
type 
)
{
    return ca.CACheckbox;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {ca.CACheckbox::Type} arg1
 * @return {ca.CACheckbox}
 */
createWithCenter : function (
drect, 
type 
)
{
    return ca.CACheckbox;
},

/**
 * @method CACheckbox
 * @constructor
 * @param {ca.CACheckbox::Type} arg0
 */
CACheckbox : function (
type 
)
{
},

};

/**
 * @class CADrawerController
 */
ca.CADrawerController = {

/**
 * @method hideLeftViewController
 * @param {bool} arg0
 */
hideLeftViewController : function (
bool 
)
{
},

/**
 * @method isReachBoundaryLeft
 * @return {bool}
 */
isReachBoundaryLeft : function (
)
{
    return false;
},

/**
 * @method showLeftViewController
 * @param {bool} arg0
 */
showLeftViewController : function (
bool 
)
{
},

/**
 * @method setBackgroundImage
 * @param {ca.CAImage} arg0
 */
setBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setTouchMoved
 * @param {bool} arg0
 */
setTouchMoved : function (
bool 
)
{
},

/**
 * @method getEffect3D
 * @return {bool}
 */
getEffect3D : function (
)
{
    return false;
},

/**
 * @method getRightViewController
 * @return {ca.CAViewController}
 */
getRightViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method isShowLeftViewController
 * @return {bool}
 */
isShowLeftViewController : function (
)
{
    return false;
},

/**
 * @method initWithController
 * @param {ca.CAViewController} arg0
 * @param {ca.CAViewController} arg1
 * @return {bool}
 */
initWithController : function (
caviewcontroller, 
caviewcontroller 
)
{
    return false;
},

/**
 * @method setEffect3D
 * @param {bool} arg0
 */
setEffect3D : function (
bool 
)
{
},

/**
 * @method isReachBoundaryRight
 * @return {bool}
 */
isReachBoundaryRight : function (
)
{
    return false;
},

/**
 * @method replaceRightViewController
 * @param {ca.CAViewController} arg0
 */
replaceRightViewController : function (
caviewcontroller 
)
{
},

/**
 * @method getLeftViewController
 * @return {ca.CAViewController}
 */
getLeftViewController : function (
)
{
    return ca.CAViewController;
},

/**
 * @method isTouchMoved
 * @return {bool}
 */
isTouchMoved : function (
)
{
    return false;
},

/**
 * @method CADrawerController
 * @constructor
 */
CADrawerController : function (
)
{
},

};

/**
 * @class CATouchController
 */
ca.CATouchController = {

/**
 * @method touchMoved
 */
touchMoved : function (
)
{
},

/**
 * @method setEvent
 * @param {ca.CAEvent} arg0
 */
setEvent : function (
caevent 
)
{
},

/**
 * @method getEvent
 * @return {ca.CAEvent}
 */
getEvent : function (
)
{
    return ca.CAEvent;
},

/**
 * @method getTouch
 * @return {ca.CATouch}
 */
getTouch : function (
)
{
    return ca.CATouch;
},

/**
 * @method touchBegan
 */
touchBegan : function (
)
{
},

/**
 * @method touchEnded
 */
touchEnded : function (
)
{
},

/**
 * @method getTouchID
 * @return {int}
 */
getTouchID : function (
)
{
    return 0;
},

/**
 * @method setTouch
 * @param {ca.CATouch} arg0
 */
setTouch : function (
catouch 
)
{
},

/**
 * @method touchCancelled
 */
touchCancelled : function (
)
{
},

/**
 * @method CATouchController
 * @constructor
 */
CATouchController : function (
)
{
},

};

/**
 * @class CAGif
 */
ca.CAGif = {

/**
 * @method getDelay
 * @return {float}
 */
getDelay : function (
)
{
    return 0;
},

/**
 * @method getImages
 * @return {Array}
 */
getImages : function (
)
{
    return new Array();
},

/**
 * @method initWithFilePath
 * @param {String} arg0
 * @return {bool}
 */
initWithFilePath : function (
str 
)
{
    return false;
},

/**
 * @method initWithData
 * @param {ca.CAData} arg0
 * @return {bool}
 */
initWithData : function (
cadata 
)
{
    return false;
},

/**
 * @method getImageWithIndex
 * @param {unsigned int} arg0
 * @return {ca.CAImage}
 */
getImageWithIndex : function (
int 
)
{
    return ca.CAImage;
},

/**
 * @method getPixelsHigh
 * @return {unsigned int}
 */
getPixelsHigh : function (
)
{
    return 0;
},

/**
 * @method getPixelsWide
 * @return {unsigned int}
 */
getPixelsWide : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CAGif}
 */
create : function (
str 
)
{
    return ca.CAGif;
},

/**
 * @method createWithData
 * @param {ca.CAData} arg0
 * @return {ca.CAGif}
 */
createWithData : function (
cadata 
)
{
    return ca.CAGif;
},

/**
 * @method CAGif
 * @constructor
 */
CAGif : function (
)
{
},

};

/**
 * @class CAGifView
 */
ca.CAGifView = {

/**
 * @method setTimes
 * @param {float} arg0
 */
setTimes : function (
float 
)
{
},

/**
 * @method onEnter
 */
onEnter : function (
)
{
},

/**
 * @method onExit
 */
onExit : function (
)
{
},

/**
 * @method initWithGif
 * @param {ca.CAGif} arg0
 * @return {bool}
 */
initWithGif : function (
cagif 
)
{
    return false;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setGif
 * @param {ca.CAGif} arg0
 */
setGif : function (
cagif 
)
{
},

/**
 * @method getGif
 * @return {ca.CAGif}
 */
getGif : function (
)
{
    return ca.CAGif;
},

/**
 * @method isRepeatForever
 * @return {bool}
 */
isRepeatForever : function (
)
{
    return false;
},

/**
 * @method setRepeatForever
 * @param {bool} arg0
 */
setRepeatForever : function (
bool 
)
{
},

/**
 * @method createWithGif
 * @param {ca.CAGif} arg0
 * @return {ca.CAGifView}
 */
createWithGif : function (
cagif 
)
{
    return ca.CAGifView;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAGifView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAGifView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAGifView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAGifView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAGifView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAGifView;
},

/**
 * @method CAGifView
 * @constructor
 */
CAGifView : function (
)
{
},

};

/**
 * @class CARichLabel
 */
ca.CARichLabel = {

/**
 * @method setTextAlignment
 * @param {ca.CATextAlignment} arg0
 */
setTextAlignment : function (
catextalignment 
)
{
},

/**
 * @method setVerticalTextAlignmet
 * @param {ca.CAVerticalTextAlignment} arg0
 */
setVerticalTextAlignmet : function (
caverticaltextalignment 
)
{
},

/**
 * @method visitEve
 */
visitEve : function (
)
{
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method getLabelSize
 * @return {size_object}
 */
getLabelSize : function (
)
{
    return ca.DSize;
},

/**
 * @method setNumberOfLine
 * @param {unsigned int} arg0
 */
setNumberOfLine : function (
int 
)
{
},

/**
 * @method appendText
 * @param {String} arg0
 * @param {font_object} arg1
 */
appendText : function (
str, 
cafont 
)
{
},

/**
 * @method create
 * @return {ca.CARichLabel}
 */
create : function (
)
{
    return ca.CARichLabel;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CARichLabel}
 */
createWithFrame : function (
drect 
)
{
    return ca.CARichLabel;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CARichLabel}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CARichLabel;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CARichLabel}
 */
createWithCenter : function (
drect 
)
{
    return ca.CARichLabel;
},

/**
 * @method CARichLabel
 * @constructor
 */
CARichLabel : function (
)
{
},

};

/**
 * @class CACell
 */
ca.CACell = {

/**
 * @method getContentView
 * @return {ca.CAView}
 */
getContentView : function (
)
{
    return ca.CAView;
},

/**
 * @method setReuseIdentifier
 * @param {String} arg0
 */
setReuseIdentifier : function (
str 
)
{
},

/**
 * @method isAllowsSelected
 * @return {bool}
 */
isAllowsSelected : function (
)
{
    return false;
},

/**
 * @method getReuseIdentifier
 * @return {String}
 */
getReuseIdentifier : function (
)
{
    return ;
},

/**
 * @method setAllowsSelected
 * @param {bool} arg0
 */
setAllowsSelected : function (
bool 
)
{
},

/**
 * @method setControlStateHighlighted
 */
setControlStateHighlighted : function (
)
{
},

/**
 * @method setControlStateEffect
 * @param {bool} arg0
 */
setControlStateEffect : function (
bool 
)
{
},

/**
 * @method setControlState
 * @param {ca.CAControl::State} arg0
 */
setControlState : function (
state 
)
{
},

/**
 * @method getBackgroundView
 * @return {ca.CAView}
 */
getBackgroundView : function (
)
{
    return ca.CAView;
},

/**
 * @method getControlState
 * @return {ca.CAControl::State}
 */
getControlState : function (
)
{
    return 0;
},

/**
 * @method getViewWithID
 * @param {String} arg0
 * @return {ca.CAView}
 */
getViewWithID : function (
str 
)
{
    return ca.CAView;
},

/**
 * @method isControlStateEffect
 * @return {bool}
 */
isControlStateEffect : function (
)
{
    return false;
},

/**
 * @method setControlStateNormal
 */
setControlStateNormal : function (
)
{
},

/**
 * @method setControlStateSelected
 */
setControlStateSelected : function (
)
{
},

/**
 * @method initWithReuseIdentifier
 * @param {String} arg0
 * @return {bool}
 */
initWithReuseIdentifier : function (
str 
)
{
    return false;
},

/**
 * @method setControlStateDisabled
 */
setControlStateDisabled : function (
)
{
},

/**
 * @method setBackgroundView
 * @param {ca.CAView} arg0
 */
setBackgroundView : function (
caview 
)
{
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CACell}
 */
create : function (
str 
)
{
    return ca.CACell;
},

/**
 * @method CACell
 * @constructor
 */
CACell : function (
)
{
},

};

/**
 * @class CAListViewDataSource
 */
ca.CAListViewDataSource = {

/**
 * @method listViewCellAtIndex
 * @param {ca.CAListView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAListViewCell}
 */
listViewCellAtIndex : function (
calistview, 
dsize, 
int 
)
{
    return ca.CAListViewCell;
},

/**
 * @method numberOfIndex
 * @param {ca.CAListView} arg0
 * @return {unsigned int}
 */
numberOfIndex : function (
calistview 
)
{
    return 0;
},

/**
 * @method listViewWillDisplayCellAtIndex
 * @param {ca.CAListView} arg0
 * @param {ca.CAListViewCell} arg1
 * @param {unsigned int} arg2
 */
listViewWillDisplayCellAtIndex : function (
calistview, 
calistviewcell, 
int 
)
{
},

/**
 * @method listViewHeightForIndex
 * @param {ca.CAListView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
listViewHeightForIndex : function (
calistview, 
int 
)
{
    return 0;
},

};

/**
 * @class CAListView
 */
ca.CAListView = {

/**
 * @method isAllowsSelection
 * @return {bool}
 */
isAllowsSelection : function (
)
{
    return false;
},

/**
 * @method getOrientation
 * @return {ca.CAListView::Orientation}
 */
getOrientation : function (
)
{
    return 0;
},

/**
 * @method setListFooterHeight
 * @param {unsigned int} arg0
 */
setListFooterHeight : function (
int 
)
{
},

/**
 * @method setNumberOfRowsAtIndexPathCallback
 * @param {function} arg0
 */
setNumberOfRowsAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setSeparatorColor
 * @param {color4b_object} arg0
 */
setSeparatorColor : function (
cacolor4b 
)
{
},

/**
 * @method getListViewDelegate
 * @return {ca.CAListViewDelegate}
 */
getListViewDelegate : function (
)
{
    return ca.CAListViewDelegate;
},

/**
 * @method setSelectAtIndex
 * @param {unsigned int} arg0
 */
setSelectAtIndex : function (
int 
)
{
},

/**
 * @method getSeparatorViewHeight
 * @return {unsigned int}
 */
getSeparatorViewHeight : function (
)
{
    return 0;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getListViewDataSource
 * @return {ca.CAListViewDataSource}
 */
getListViewDataSource : function (
)
{
    return ca.CAListViewDataSource;
},

/**
 * @method getSeparatorColor
 * @return {color4b_object}
 */
getSeparatorColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setAllowsSelection
 * @param {bool} arg0
 */
setAllowsSelection : function (
bool 
)
{
},

/**
 * @method reloadData
 */
reloadData : function (
)
{
},

/**
 * @method setAllowsMultipleSelection
 * @param {bool} arg0
 */
setAllowsMultipleSelection : function (
bool 
)
{
},

/**
 * @method isAllowsMultipleSelection
 * @return {bool}
 */
isAllowsMultipleSelection : function (
)
{
    return false;
},

/**
 * @method displayingListCell
 * @return {Array}
 */
displayingListCell : function (
)
{
    return new Array();
},

/**
 * @method setListHeaderView
 * @param {ca.CAView} arg0
 */
setListHeaderView : function (
caview 
)
{
},

/**
 * @method setCellHeightAtIndexPathCallback
 * @param {function} arg0
 */
setCellHeightAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getListFooterHeight
 * @return {unsigned int}
 */
getListFooterHeight : function (
)
{
    return 0;
},

/**
 * @method setShowsScrollIndicators
 * @param {bool} arg0
 */
setShowsScrollIndicators : function (
bool 
)
{
},

/**
 * @method setListHeaderHeight
 * @param {unsigned int} arg0
 */
setListHeaderHeight : function (
int 
)
{
},

/**
 * @method setWillDisplayCellAtIndexPathCallback
 * @param {function} arg0
 */
setWillDisplayCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getListHeaderView
 * @return {ca.CAView}
 */
getListHeaderView : function (
)
{
    return ca.CAView;
},

/**
 * @method setDidSelectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidSelectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setSeparatorViewHeight
 * @param {unsigned int} arg0
 */
setSeparatorViewHeight : function (
int 
)
{
},

/**
 * @method setOrientation
 * @param {ca.CAListView::Orientation} arg0
 */
setOrientation : function (
orientation 
)
{
},

/**
 * @method getListHeaderHeight
 * @return {unsigned int}
 */
getListHeaderHeight : function (
)
{
    return 0;
},

/**
 * @method switchPCMode
 * @param {bool} arg0
 */
switchPCMode : function (
bool 
)
{
},

/**
 * @method setListFooterView
 * @param {ca.CAView} arg0
 */
setListFooterView : function (
caview 
)
{
},

/**
 * @method getListFooterView
 * @return {ca.CAView}
 */
getListFooterView : function (
)
{
    return ca.CAView;
},

/**
 * @method cellForRowAtIndex
 * @param {unsigned int} arg0
 * @return {ca.CAListViewCell}
 */
cellForRowAtIndex : function (
int 
)
{
    return ca.CAListViewCell;
},

/**
 * @method setDidDeselectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidDeselectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setCellAtIndexPathCallback
 * @param {function} arg0
 */
setCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setUnSelectAtIndex
 * @param {unsigned int} arg0
 */
setUnSelectAtIndex : function (
int 
)
{
},

/**
 * @method dequeueReusableCellWithIdentifier
 * @param {char} arg0
 * @return {ca.CAListViewCell}
 */
dequeueReusableCellWithIdentifier : function (
char 
)
{
    return ca.CAListViewCell;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAListView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAListView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAListView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAListView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAListView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAListView;
},

/**
 * @method CAListView
 * @constructor
 */
CAListView : function (
)
{
},

};

/**
 * @class CAListViewCell
 */
ca.CAListViewCell = {

/**
 * @method getIndex
 * @return {unsigned int}
 */
getIndex : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CAListViewCell}
 */
create : function (
str 
)
{
    return ca.CAListViewCell;
},

/**
 * @method CAListViewCell
 * @constructor
 */
CAListViewCell : function (
)
{
},

};

/**
 * @class CATableViewDataSource
 */
ca.CATableViewDataSource = {

/**
 * @method tableViewHeightForFooterInSection
 * @param {ca.CATableView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
tableViewHeightForFooterInSection : function (
catableview, 
int 
)
{
    return 0;
},

/**
 * @method tableViewHeightForRowAtIndexPath
 * @param {ca.CATableView} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {unsigned int}
 */
tableViewHeightForRowAtIndexPath : function (
catableview, 
int, 
int 
)
{
    return 0;
},

/**
 * @method numberOfSections
 * @param {ca.CATableView} arg0
 * @return {unsigned int}
 */
numberOfSections : function (
catableview 
)
{
    return 0;
},

/**
 * @method tableCellAtIndex
 * @param {ca.CATableView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @return {ca.CATableViewCell}
 */
tableCellAtIndex : function (
catableview, 
dsize, 
int, 
int 
)
{
    return ca.CATableViewCell;
},

/**
 * @method numberOfRowsInSection
 * @param {ca.CATableView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
numberOfRowsInSection : function (
catableview, 
int 
)
{
    return 0;
},

/**
 * @method tableViewHeightForHeaderInSection
 * @param {ca.CATableView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
tableViewHeightForHeaderInSection : function (
catableview, 
int 
)
{
    return 0;
},

/**
 * @method tableViewWillDisplayCellAtIndex
 * @param {ca.CATableView} arg0
 * @param {ca.CATableViewCell} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 */
tableViewWillDisplayCellAtIndex : function (
catableview, 
catableviewcell, 
int, 
int 
)
{
},

};

/**
 * @class CATableView
 */
ca.CATableView = {

/**
 * @method getTableFooterView
 * @return {ca.CAView}
 */
getTableFooterView : function (
)
{
    return ca.CAView;
},

/**
 * @method isAllowsSelection
 * @return {bool}
 */
isAllowsSelection : function (
)
{
    return false;
},

/**
 * @method setNumberOfSectionsCallback
 * @param {function} arg0
 */
setNumberOfSectionsCallback : function (
func 
)
{
},

/**
 * @method setHeightForHeaderInSectionCallback
 * @param {function} arg0
 */
setHeightForHeaderInSectionCallback : function (
func 
)
{
},

/**
 * @method setSectionViewForFooterInSectionCallback
 * @param {function} arg0
 */
setSectionViewForFooterInSectionCallback : function (
func 
)
{
},

/**
 * @method getSectionFooterHeightInSection
 * @param {unsigned int} arg0
 * @return {float}
 */
getSectionFooterHeightInSection : function (
int 
)
{
    return 0;
},

/**
 * @method setNumberOfRowsAtIndexPathCallback
 * @param {function} arg0
 */
setNumberOfRowsAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setSeparatorColor
 * @param {color4b_object} arg0
 */
setSeparatorColor : function (
cacolor4b 
)
{
},

/**
 * @method setTableFooterHeight
 * @param {unsigned int} arg0
 */
setTableFooterHeight : function (
int 
)
{
},

/**
 * @method setTableHeaderHeight
 * @param {unsigned int} arg0
 */
setTableHeaderHeight : function (
int 
)
{
},

/**
 * @method setCellAtIndexPathCallBack
 * @param {function} arg0
 */
setCellAtIndexPathCallBack : function (
func 
)
{
},

/**
 * @method isAlwaysBottomSectionFooter
 * @return {bool}
 */
isAlwaysBottomSectionFooter : function (
)
{
    return false;
},

/**
 * @method setHeightForFooterInSectionCallback
 * @param {function} arg0
 */
setHeightForFooterInSectionCallback : function (
func 
)
{
},

/**
 * @method getRowHeightInSectionInRow
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @return {float}
 */
getRowHeightInSectionInRow : function (
int, 
int 
)
{
    return 0;
},

/**
 * @method setTableHeaderView
 * @param {ca.CAView} arg0
 */
setTableHeaderView : function (
caview 
)
{
},

/**
 * @method getNumberOfSections
 * @return {unsigned int}
 */
getNumberOfSections : function (
)
{
    return 0;
},

/**
 * @method getSeparatorViewHeight
 * @return {unsigned int}
 */
getSeparatorViewHeight : function (
)
{
    return 0;
},

/**
 * @method getTableViewDataSource
 * @return {ca.CATableViewDataSource}
 */
getTableViewDataSource : function (
)
{
    return ca.CATableViewDataSource;
},

/**
 * @method setSelectRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 */
setSelectRowAtIndexPath : function (
int, 
int 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getSectionHeightInSection
 * @param {unsigned int} arg0
 * @return {float}
 */
getSectionHeightInSection : function (
int 
)
{
    return 0;
},

/**
 * @method isAllowsMultipleSelection
 * @return {bool}
 */
isAllowsMultipleSelection : function (
)
{
    return false;
},

/**
 * @method getSeparatorColor
 * @return {color4b_object}
 */
getSeparatorColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setAllowsSelection
 * @param {bool} arg0
 */
setAllowsSelection : function (
bool 
)
{
},

/**
 * @method reloadData
 */
reloadData : function (
)
{
},

/**
 * @method setAllowsMultipleSelection
 * @param {bool} arg0
 */
setAllowsMultipleSelection : function (
bool 
)
{
},

/**
 * @method getTableFooterHeight
 * @return {unsigned int}
 */
getTableFooterHeight : function (
)
{
    return 0;
},

/**
 * @method setCellHeightAtIndexPathCallback
 * @param {function} arg0
 */
setCellHeightAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setAlwaysTopSectionHeader
 * @param {bool} arg0
 */
setAlwaysTopSectionHeader : function (
bool 
)
{
},

/**
 * @method setShowsScrollIndicators
 * @param {bool} arg0
 */
setShowsScrollIndicators : function (
bool 
)
{
},

/**
 * @method cellForRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @return {ca.CATableViewCell}
 */
cellForRowAtIndexPath : function (
int, 
int 
)
{
    return ca.CATableViewCell;
},

/**
 * @method displayingTableCell
 * @return {Array}
 */
displayingTableCell : function (
)
{
    return new Array();
},

/**
 * @method getTableHeaderView
 * @return {ca.CAView}
 */
getTableHeaderView : function (
)
{
    return ca.CAView;
},

/**
 * @method setWillDisplayCellAtIndexPathCallback
 * @param {function} arg0
 */
setWillDisplayCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setAlwaysBottomSectionFooter
 * @param {bool} arg0
 */
setAlwaysBottomSectionFooter : function (
bool 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method isAlwaysTopSectionHeader
 * @return {bool}
 */
isAlwaysTopSectionHeader : function (
)
{
    return false;
},

/**
 * @method setDidSelectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidSelectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setTableFooterView
 * @param {ca.CAView} arg0
 */
setTableFooterView : function (
caview 
)
{
},

/**
 * @method setSeparatorViewHeight
 * @param {unsigned int} arg0
 */
setSeparatorViewHeight : function (
int 
)
{
},

/**
 * @method setSectionViewForHeaderInSectionCallback
 * @param {function} arg0
 */
setSectionViewForHeaderInSectionCallback : function (
func 
)
{
},

/**
 * @method switchPCMode
 * @param {bool} arg0
 */
switchPCMode : function (
bool 
)
{
},

/**
 * @method getNumberOfRowsInSection
 * @param {unsigned int} arg0
 * @return {unsigned int}
 */
getNumberOfRowsInSection : function (
int 
)
{
    return 0;
},

/**
 * @method setUnSelectRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 */
setUnSelectRowAtIndexPath : function (
int, 
int 
)
{
},

/**
 * @method getTableViewDelegate
 * @return {ca.CATableViewDelegate}
 */
getTableViewDelegate : function (
)
{
    return ca.CATableViewDelegate;
},

/**
 * @method getSectionHeaderHeightInSection
 * @param {unsigned int} arg0
 * @return {float}
 */
getSectionHeaderHeightInSection : function (
int 
)
{
    return 0;
},

/**
 * @method setDidDeselectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidDeselectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method dequeueReusableCellWithIdentifier
 * @param {char} arg0
 * @return {ca.CATableViewCell}
 */
dequeueReusableCellWithIdentifier : function (
char 
)
{
    return ca.CATableViewCell;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method getTableHeaderHeight
 * @return {unsigned int}
 */
getTableHeaderHeight : function (
)
{
    return 0;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CATableView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CATableView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CATableView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CATableView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CATableView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CATableView;
},

/**
 * @method CATableView
 * @constructor
 */
CATableView : function (
)
{
},

};

/**
 * @class CATableViewCell
 */
ca.CATableViewCell = {

/**
 * @method setDraggingLength
 * @param {unsigned int} arg0
 */
setDraggingLength : function (
int 
)
{
},

/**
 * @method getSection
 * @return {unsigned int}
 */
getSection : function (
)
{
    return 0;
},

/**
 * @method getDraggingLength
 * @return {unsigned int}
 */
getDraggingLength : function (
)
{
    return 0;
},

/**
 * @method getRow
 * @return {unsigned int}
 */
getRow : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CATableViewCell}
 */
create : function (
str 
)
{
    return ca.CATableViewCell;
},

/**
 * @method CATableViewCell
 * @constructor
 */
CATableViewCell : function (
)
{
},

};

/**
 * @class CACollectionViewDataSource
 */
ca.CACollectionViewDataSource = {

/**
 * @method numberOfSections
 * @param {ca.CACollectionView} arg0
 * @return {unsigned int}
 */
numberOfSections : function (
cacollectionview 
)
{
    return 0;
},

/**
 * @method collectionViewHeightForRowAtIndexPath
 * @param {ca.CACollectionView} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {unsigned int}
 */
collectionViewHeightForRowAtIndexPath : function (
cacollectionview, 
int, 
int 
)
{
    return 0;
},

/**
 * @method collectionViewHeightForHeaderInSection
 * @param {ca.CACollectionView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
collectionViewHeightForHeaderInSection : function (
cacollectionview, 
int 
)
{
    return 0;
},

/**
 * @method collectionViewHeightForFooterInSection
 * @param {ca.CACollectionView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
collectionViewHeightForFooterInSection : function (
cacollectionview, 
int 
)
{
    return 0;
},

/**
 * @method collectionViewSectionViewForHeaderInSection
 * @param {ca.CACollectionView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAView}
 */
collectionViewSectionViewForHeaderInSection : function (
cacollectionview, 
dsize, 
int 
)
{
    return ca.CAView;
},

/**
 * @method numberOfItemsInRowsInSection
 * @param {ca.CACollectionView} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {unsigned int}
 */
numberOfItemsInRowsInSection : function (
cacollectionview, 
int, 
int 
)
{
    return 0;
},

/**
 * @method numberOfRowsInSection
 * @param {ca.CACollectionView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
numberOfRowsInSection : function (
cacollectionview, 
int 
)
{
    return 0;
},

/**
 * @method collectionViewWillDisplayCellAtIndex
 * @param {ca.CACollectionView} arg0
 * @param {ca.CACollectionViewCell} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @param {unsigned int} arg4
 */
collectionViewWillDisplayCellAtIndex : function (
cacollectionview, 
cacollectionviewcell, 
int, 
int, 
int 
)
{
},

/**
 * @method collectionViewSectionViewForFooterInSection
 * @param {ca.CACollectionView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAView}
 */
collectionViewSectionViewForFooterInSection : function (
cacollectionview, 
dsize, 
int 
)
{
    return ca.CAView;
},

/**
 * @method collectionCellAtIndex
 * @param {ca.CACollectionView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @param {unsigned int} arg4
 * @return {ca.CACollectionViewCell}
 */
collectionCellAtIndex : function (
cacollectionview, 
dsize, 
int, 
int, 
int 
)
{
    return ca.CACollectionViewCell;
},

};

/**
 * @class CACollectionView
 */
ca.CACollectionView = {

/**
 * @method setCollectionFooterHeight
 * @param {unsigned int} arg0
 */
setCollectionFooterHeight : function (
int 
)
{
},

/**
 * @method setNumberOfSectionsCallback
 * @param {function} arg0
 */
setNumberOfSectionsCallback : function (
func 
)
{
},

/**
 * @method setHeightForHeaderInSectionCallback
 * @param {function} arg0
 */
setHeightForHeaderInSectionCallback : function (
func 
)
{
},

/**
 * @method setSectionViewForFooterInSectionCallback
 * @param {function} arg0
 */
setSectionViewForFooterInSectionCallback : function (
func 
)
{
},

/**
 * @method setCollectionHeaderView
 * @param {ca.CAView} arg0
 */
setCollectionHeaderView : function (
caview 
)
{
},

/**
 * @method getVertInterval
 * @return {unsigned int}
 */
getVertInterval : function (
)
{
    return 0;
},

/**
 * @method setCollectionFooterView
 * @param {ca.CAView} arg0
 */
setCollectionFooterView : function (
caview 
)
{
},

/**
 * @method setNumberOfRowsAtIndexPathCallback
 * @param {function} arg0
 */
setNumberOfRowsAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getCollectionFooterView
 * @return {ca.CAView}
 */
getCollectionFooterView : function (
)
{
    return ca.CAView;
},

/**
 * @method setAlwaysTopSectionHeader
 * @param {bool} arg0
 */
setAlwaysTopSectionHeader : function (
bool 
)
{
},

/**
 * @method isAlwaysBottomSectionFooter
 * @return {bool}
 */
isAlwaysBottomSectionFooter : function (
)
{
    return false;
},

/**
 * @method setHeightForFooterInSectionCallback
 * @param {function} arg0
 */
setHeightForFooterInSectionCallback : function (
func 
)
{
},

/**
 * @method getHoriInterval
 * @return {unsigned int}
 */
getHoriInterval : function (
)
{
    return 0;
},

/**
 * @method clearData
 */
clearData : function (
)
{
},

/**
 * @method setHoriInterval
 * @param {unsigned int} arg0
 */
setHoriInterval : function (
int 
)
{
},

/**
 * @method setSelectRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 */
setSelectRowAtIndexPath : function (
int, 
int, 
int 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method isAllowsMultipleSelection
 * @return {bool}
 */
isAllowsMultipleSelection : function (
)
{
    return false;
},

/**
 * @method setNumberOfItemsAtIndexPathCallback
 * @param {function} arg0
 */
setNumberOfItemsAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setAllowsSelection
 * @param {bool} arg0
 */
setAllowsSelection : function (
bool 
)
{
},

/**
 * @method reloadData
 */
reloadData : function (
)
{
},

/**
 * @method setAllowsMultipleSelection
 * @param {bool} arg0
 */
setAllowsMultipleSelection : function (
bool 
)
{
},

/**
 * @method getCollectionHeaderView
 * @return {ca.CAView}
 */
getCollectionHeaderView : function (
)
{
    return ca.CAView;
},

/**
 * @method setCellHeightAtIndexPathCallback
 * @param {function} arg0
 */
setCellHeightAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setShowsScrollIndicators
 * @param {bool} arg0
 */
setShowsScrollIndicators : function (
bool 
)
{
},

/**
 * @method cellForRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {ca.CACollectionViewCell}
 */
cellForRowAtIndexPath : function (
int, 
int, 
int 
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method getCollectionViewDelegate
 * @return {ca.CACollectionViewDelegate}
 */
getCollectionViewDelegate : function (
)
{
    return ca.CACollectionViewDelegate;
},

/**
 * @method setWillDisplayCellAtIndexPathCallback
 * @param {function} arg0
 */
setWillDisplayCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getCollectionViewDataSource
 * @return {ca.CACollectionViewDataSource}
 */
getCollectionViewDataSource : function (
)
{
    return ca.CACollectionViewDataSource;
},

/**
 * @method setAlwaysBottomSectionFooter
 * @param {bool} arg0
 */
setAlwaysBottomSectionFooter : function (
bool 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method displayingCollectionCell
 * @return {Array}
 */
displayingCollectionCell : function (
)
{
    return new Array();
},

/**
 * @method isAlwaysTopSectionHeader
 * @return {bool}
 */
isAlwaysTopSectionHeader : function (
)
{
    return false;
},

/**
 * @method setDidSelectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidSelectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method switchPCMode
 * @param {bool} arg0
 */
switchPCMode : function (
bool 
)
{
},

/**
 * @method setSectionViewForHeaderInSectionCallback
 * @param {function} arg0
 */
setSectionViewForHeaderInSectionCallback : function (
func 
)
{
},

/**
 * @method setVertInterval
 * @param {unsigned int} arg0
 */
setVertInterval : function (
int 
)
{
},

/**
 * @method getCollectionHeaderHeight
 * @return {unsigned int}
 */
getCollectionHeaderHeight : function (
)
{
    return 0;
},

/**
 * @method getCollectionFooterHeight
 * @return {unsigned int}
 */
getCollectionFooterHeight : function (
)
{
    return 0;
},

/**
 * @method setCollectionHeaderHeight
 * @param {unsigned int} arg0
 */
setCollectionHeaderHeight : function (
int 
)
{
},

/**
 * @method setUnSelectRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 */
setUnSelectRowAtIndexPath : function (
int, 
int, 
int 
)
{
},

/**
 * @method getHighlightCollectionCell
 * @return {ca.CACollectionViewCell}
 */
getHighlightCollectionCell : function (
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method setDidDeselectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidDeselectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setCellAtIndexPathCallback
 * @param {function} arg0
 */
setCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method isAllowsSelection
 * @return {bool}
 */
isAllowsSelection : function (
)
{
    return false;
},

/**
 * @method dequeueReusableCellWithIdentifier
 * @param {char} arg0
 * @return {ca.CACollectionViewCell}
 */
dequeueReusableCellWithIdentifier : function (
char 
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CACollectionView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CACollectionView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CACollectionView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CACollectionView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CACollectionView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CACollectionView;
},

/**
 * @method CACollectionView
 * @constructor
 */
CACollectionView : function (
)
{
},

};

/**
 * @class CACollectionViewCell
 */
ca.CACollectionViewCell = {

/**
 * @method getSection
 * @return {unsigned int}
 */
getSection : function (
)
{
    return 0;
},

/**
 * @method getItem
 * @return {unsigned int}
 */
getItem : function (
)
{
    return 0;
},

/**
 * @method getRow
 * @return {unsigned int}
 */
getRow : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CACollectionViewCell}
 */
create : function (
str 
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method CACollectionViewCell
 * @constructor
 */
CACollectionViewCell : function (
)
{
},

};

/**
 * @class CAAutoCollectionViewDataSource
 */
ca.CAAutoCollectionViewDataSource = {

/**
 * @method numberOfItemsInSection
 * @param {ca.CAAutoCollectionView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
numberOfItemsInSection : function (
caautocollectionview, 
int 
)
{
    return 0;
},

/**
 * @method numberOfSections
 * @param {ca.CAAutoCollectionView} arg0
 * @return {unsigned int}
 */
numberOfSections : function (
caautocollectionview 
)
{
    return 0;
},

/**
 * @method collectionViewHeightForHeaderInSection
 * @param {ca.CAAutoCollectionView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
collectionViewHeightForHeaderInSection : function (
caautocollectionview, 
int 
)
{
    return 0;
},

/**
 * @method collectionViewHeightForFooterInSection
 * @param {ca.CAAutoCollectionView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
collectionViewHeightForFooterInSection : function (
caautocollectionview, 
int 
)
{
    return 0;
},

/**
 * @method collectionViewSectionViewForHeaderInSection
 * @param {ca.CAAutoCollectionView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAView}
 */
collectionViewSectionViewForHeaderInSection : function (
caautocollectionview, 
dsize, 
int 
)
{
    return ca.CAView;
},

/**
 * @method collectionViewWillDisplayCellAtIndex
 * @param {ca.CAAutoCollectionView} arg0
 * @param {ca.CACollectionViewCell} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 */
collectionViewWillDisplayCellAtIndex : function (
caautocollectionview, 
cacollectionviewcell, 
int, 
int 
)
{
},

/**
 * @method collectionViewSectionViewForFooterInSection
 * @param {ca.CAAutoCollectionView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAView}
 */
collectionViewSectionViewForFooterInSection : function (
caautocollectionview, 
dsize, 
int 
)
{
    return ca.CAView;
},

/**
 * @method collectionViewCellSizeAtIndexPathCallback
 * @param {ca.CAAutoCollectionView} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {size_object}
 */
collectionViewCellSizeAtIndexPathCallback : function (
caautocollectionview, 
int, 
int 
)
{
    return ca.DSize;
},

/**
 * @method collectionCellAtIndex
 * @param {ca.CAAutoCollectionView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @param {unsigned int} arg3
 * @return {ca.CACollectionViewCell}
 */
collectionCellAtIndex : function (
caautocollectionview, 
dsize, 
int, 
int 
)
{
    return ca.CACollectionViewCell;
},

};

/**
 * @class CAAutoCollectionView
 */
ca.CAAutoCollectionView = {

/**
 * @method setCollectionFooterHeight
 * @param {unsigned int} arg0
 */
setCollectionFooterHeight : function (
int 
)
{
},

/**
 * @method setNumberOfSectionsCallback
 * @param {function} arg0
 */
setNumberOfSectionsCallback : function (
func 
)
{
},

/**
 * @method setHeightForHeaderInSectionCallback
 * @param {function} arg0
 */
setHeightForHeaderInSectionCallback : function (
func 
)
{
},

/**
 * @method getCellVertAlign
 * @return {ca.CAAutoCollectionView::CellVertAlign}
 */
getCellVertAlign : function (
)
{
    return 0;
},

/**
 * @method setSectionViewForFooterInSectionCallback
 * @param {function} arg0
 */
setSectionViewForFooterInSectionCallback : function (
func 
)
{
},

/**
 * @method setCollectionHeaderView
 * @param {ca.CAView} arg0
 */
setCollectionHeaderView : function (
caview 
)
{
},

/**
 * @method getOrientation
 * @return {ca.CAAutoCollectionView::Orientation}
 */
getOrientation : function (
)
{
    return 0;
},

/**
 * @method setCollectionFooterView
 * @param {ca.CAView} arg0
 */
setCollectionFooterView : function (
caview 
)
{
},

/**
 * @method getCollectionFooterView
 * @return {ca.CAView}
 */
getCollectionFooterView : function (
)
{
    return ca.CAView;
},

/**
 * @method setHoriCellInterval
 * @param {unsigned int} arg0
 */
setHoriCellInterval : function (
int 
)
{
},

/**
 * @method setCellSizeAtIndexPathCallback
 * @param {function} arg0
 */
setCellSizeAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getCellHoriAlign
 * @return {ca.CAAutoCollectionView::CellHoriAlign}
 */
getCellHoriAlign : function (
)
{
    return 0;
},

/**
 * @method getHoriMargins
 * @return {unsigned int}
 */
getHoriMargins : function (
)
{
    return 0;
},

/**
 * @method isAlwaysBottomSectionFooter
 * @return {bool}
 */
isAlwaysBottomSectionFooter : function (
)
{
    return false;
},

/**
 * @method setHeightForFooterInSectionCallback
 * @param {function} arg0
 */
setHeightForFooterInSectionCallback : function (
func 
)
{
},

/**
 * @method getVertMargins
 * @return {unsigned int}
 */
getVertMargins : function (
)
{
    return 0;
},

/**
 * @method setCellHoriAlign
 * @param {ca.CAAutoCollectionView::CellHoriAlign} arg0
 */
setCellHoriAlign : function (
cellhorialign 
)
{
},

/**
 * @method setSelectRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 */
setSelectRowAtIndexPath : function (
int, 
int 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getHoriCellInterval
 * @return {unsigned int}
 */
getHoriCellInterval : function (
)
{
    return 0;
},

/**
 * @method isAllowsMultipleSelection
 * @return {bool}
 */
isAllowsMultipleSelection : function (
)
{
    return false;
},

/**
 * @method setNumberOfItemsAtIndexPathCallback
 * @param {function} arg0
 */
setNumberOfItemsAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setVertMargins
 * @param {unsigned int} arg0
 */
setVertMargins : function (
int 
)
{
},

/**
 * @method setAllowsSelection
 * @param {bool} arg0
 */
setAllowsSelection : function (
bool 
)
{
},

/**
 * @method reloadData
 */
reloadData : function (
)
{
},

/**
 * @method setAllowsMultipleSelection
 * @param {bool} arg0
 */
setAllowsMultipleSelection : function (
bool 
)
{
},

/**
 * @method getCollectionHeaderView
 * @return {ca.CAView}
 */
getCollectionHeaderView : function (
)
{
    return ca.CAView;
},

/**
 * @method setAlwaysTopSectionHeader
 * @param {bool} arg0
 */
setAlwaysTopSectionHeader : function (
bool 
)
{
},

/**
 * @method setShowsScrollIndicators
 * @param {bool} arg0
 */
setShowsScrollIndicators : function (
bool 
)
{
},

/**
 * @method cellForRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @return {ca.CACollectionViewCell}
 */
cellForRowAtIndexPath : function (
int, 
int 
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method getCollectionViewDelegate
 * @return {ca.CAAutoCollectionViewDelegate}
 */
getCollectionViewDelegate : function (
)
{
    return ca.CAAutoCollectionViewDelegate;
},

/**
 * @method setWillDisplayCellAtIndexPathCallback
 * @param {function} arg0
 */
setWillDisplayCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getCollectionViewDataSource
 * @return {ca.CAAutoCollectionViewDataSource}
 */
getCollectionViewDataSource : function (
)
{
    return ca.CAAutoCollectionViewDataSource;
},

/**
 * @method setAlwaysBottomSectionFooter
 * @param {bool} arg0
 */
setAlwaysBottomSectionFooter : function (
bool 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method setCellVertAlign
 * @param {ca.CAAutoCollectionView::CellVertAlign} arg0
 */
setCellVertAlign : function (
cellvertalign 
)
{
},

/**
 * @method displayingCollectionCell
 * @return {Array}
 */
displayingCollectionCell : function (
)
{
    return new Array();
},

/**
 * @method isAlwaysTopSectionHeader
 * @return {bool}
 */
isAlwaysTopSectionHeader : function (
)
{
    return false;
},

/**
 * @method setDidSelectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidSelectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method switchPCMode
 * @param {bool} arg0
 */
switchPCMode : function (
bool 
)
{
},

/**
 * @method setOrientation
 * @param {ca.CAAutoCollectionView::Orientation} arg0
 */
setOrientation : function (
orientation 
)
{
},

/**
 * @method setSectionViewForHeaderInSectionCallback
 * @param {function} arg0
 */
setSectionViewForHeaderInSectionCallback : function (
func 
)
{
},

/**
 * @method getVertCellInterval
 * @return {unsigned int}
 */
getVertCellInterval : function (
)
{
    return 0;
},

/**
 * @method getCollectionHeaderHeight
 * @return {unsigned int}
 */
getCollectionHeaderHeight : function (
)
{
    return 0;
},

/**
 * @method getCollectionFooterHeight
 * @return {unsigned int}
 */
getCollectionFooterHeight : function (
)
{
    return 0;
},

/**
 * @method setHoriMargins
 * @param {unsigned int} arg0
 */
setHoriMargins : function (
int 
)
{
},

/**
 * @method setCollectionHeaderHeight
 * @param {unsigned int} arg0
 */
setCollectionHeaderHeight : function (
int 
)
{
},

/**
 * @method setUnSelectRowAtIndexPath
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 */
setUnSelectRowAtIndexPath : function (
int, 
int 
)
{
},

/**
 * @method getHighlightCollectionCell
 * @return {ca.CACollectionViewCell}
 */
getHighlightCollectionCell : function (
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method setVertCellInterval
 * @param {unsigned int} arg0
 */
setVertCellInterval : function (
int 
)
{
},

/**
 * @method setDidDeselectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidDeselectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setCellAtIndexPathCallback
 * @param {function} arg0
 */
setCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method isAllowsSelection
 * @return {bool}
 */
isAllowsSelection : function (
)
{
    return false;
},

/**
 * @method dequeueReusableCellWithIdentifier
 * @param {char} arg0
 * @return {ca.CACollectionViewCell}
 */
dequeueReusableCellWithIdentifier : function (
char 
)
{
    return ca.CACollectionViewCell;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAAutoCollectionView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAAutoCollectionView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAAutoCollectionView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAAutoCollectionView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAAutoCollectionView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAAutoCollectionView;
},

/**
 * @method CAAutoCollectionView
 * @constructor
 */
CAAutoCollectionView : function (
)
{
},

};

/**
 * @class CAWaterfallViewDataSource
 */
ca.CAWaterfallViewDataSource = {

/**
 * @method waterfallViewHeightForItemAtIndex
 * @param {ca.CAWaterfallView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
waterfallViewHeightForItemAtIndex : function (
cawaterfallview, 
int 
)
{
    return 0;
},

/**
 * @method waterfallViewWillDisplayCellAtIndex
 * @param {ca.CAWaterfallView} arg0
 * @param {ca.CAWaterfallViewCell} arg1
 * @param {unsigned int} arg2
 */
waterfallViewWillDisplayCellAtIndex : function (
cawaterfallview, 
cawaterfallviewcell, 
int 
)
{
},

/**
 * @method numberOfItems
 * @param {ca.CAWaterfallView} arg0
 * @return {unsigned int}
 */
numberOfItems : function (
cawaterfallview 
)
{
    return 0;
},

/**
 * @method waterfallCellAtIndex
 * @param {ca.CAWaterfallView} arg0
 * @param {size_object} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAWaterfallViewCell}
 */
waterfallCellAtIndex : function (
cawaterfallview, 
dsize, 
int 
)
{
    return ca.CAWaterfallViewCell;
},

};

/**
 * @class CAWaterfallView
 */
ca.CAWaterfallView = {

/**
 * @method isAllowsSelection
 * @return {bool}
 */
isAllowsSelection : function (
)
{
    return false;
},

/**
 * @method getWaterfallViewDataSource
 * @return {ca.CAWaterfallViewDataSource}
 */
getWaterfallViewDataSource : function (
)
{
    return ca.CAWaterfallViewDataSource;
},

/**
 * @method setColumnMargin
 * @param {unsigned int} arg0
 */
setColumnMargin : function (
int 
)
{
},

/**
 * @method getWaterfallHeaderView
 * @return {ca.CAView}
 */
getWaterfallHeaderView : function (
)
{
    return ca.CAView;
},

/**
 * @method getColumnCount
 * @return {unsigned int}
 */
getColumnCount : function (
)
{
    return 0;
},

/**
 * @method setAlwaysTopSectionHeader
 * @param {bool} arg0
 */
setAlwaysTopSectionHeader : function (
bool 
)
{
},

/**
 * @method getWaterfallViewDelegate
 * @return {ca.CAWaterfallViewDelegate}
 */
getWaterfallViewDelegate : function (
)
{
    return ca.CAWaterfallViewDelegate;
},

/**
 * @method isAlwaysBottomSectionFooter
 * @return {bool}
 */
isAlwaysBottomSectionFooter : function (
)
{
    return false;
},

/**
 * @method setDidSelectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidSelectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getWaterfallHeaderHeight
 * @return {unsigned int}
 */
getWaterfallHeaderHeight : function (
)
{
    return 0;
},

/**
 * @method setColumnCount
 * @param {unsigned int} arg0
 */
setColumnCount : function (
int 
)
{
},

/**
 * @method setWaterfallHeaderView
 * @param {ca.CAView} arg0
 */
setWaterfallHeaderView : function (
caview 
)
{
},

/**
 * @method setWaterfallFooterHeight
 * @param {unsigned int} arg0
 */
setWaterfallFooterHeight : function (
int 
)
{
},

/**
 * @method setSelectRowAtIndexPath
 * @param {unsigned int} arg0
 */
setSelectRowAtIndexPath : function (
int 
)
{
},

/**
 * @method setWaterfallHeaderHeight
 * @param {unsigned int} arg0
 */
setWaterfallHeaderHeight : function (
int 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method isAllowsMultipleSelection
 * @return {bool}
 */
isAllowsMultipleSelection : function (
)
{
    return false;
},

/**
 * @method setNumberOfItemsAtIndexPathCallback
 * @param {function} arg0
 */
setNumberOfItemsAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getHighlightWaterfallCell
 * @return {ca.CAWaterfallViewCell}
 */
getHighlightWaterfallCell : function (
)
{
    return ca.CAWaterfallViewCell;
},

/**
 * @method setAllowsSelection
 * @param {bool} arg0
 */
setAllowsSelection : function (
bool 
)
{
},

/**
 * @method reloadData
 */
reloadData : function (
)
{
},

/**
 * @method setAllowsMultipleSelection
 * @param {bool} arg0
 */
setAllowsMultipleSelection : function (
bool 
)
{
},

/**
 * @method setCellHeightAtIndexPathCallback
 * @param {function} arg0
 */
setCellHeightAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setShowsScrollIndicators
 * @param {bool} arg0
 */
setShowsScrollIndicators : function (
bool 
)
{
},

/**
 * @method cellForRowAtIndexPath
 * @param {unsigned int} arg0
 * @return {ca.CAWaterfallViewCell}
 */
cellForRowAtIndexPath : function (
int 
)
{
    return ca.CAWaterfallViewCell;
},

/**
 * @method setWaterfallFooterView
 * @param {ca.CAView} arg0
 */
setWaterfallFooterView : function (
caview 
)
{
},

/**
 * @method getColumnMargin
 * @return {unsigned int}
 */
getColumnMargin : function (
)
{
    return 0;
},

/**
 * @method setWillDisplayCellAtIndexPathCallback
 * @param {function} arg0
 */
setWillDisplayCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method setAlwaysBottomSectionFooter
 * @param {bool} arg0
 */
setAlwaysBottomSectionFooter : function (
bool 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getWaterfallFooterView
 * @return {ca.CAView}
 */
getWaterfallFooterView : function (
)
{
    return ca.CAView;
},

/**
 * @method isAlwaysTopSectionHeader
 * @return {bool}
 */
isAlwaysTopSectionHeader : function (
)
{
    return false;
},

/**
 * @method displayingWaterfallCell
 * @return {Array}
 */
displayingWaterfallCell : function (
)
{
    return new Array();
},

/**
 * @method setItemMargin
 * @param {unsigned int} arg0
 */
setItemMargin : function (
int 
)
{
},

/**
 * @method setDidDeselectCellAtIndexPathCallback
 * @param {function} arg0
 */
setDidDeselectCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method getItemMargin
 * @return {unsigned int}
 */
getItemMargin : function (
)
{
    return 0;
},

/**
 * @method setUnSelectRowAtIndexPath
 * @param {unsigned int} arg0
 */
setUnSelectRowAtIndexPath : function (
int 
)
{
},

/**
 * @method getWaterfallFooterHeight
 * @return {unsigned int}
 */
getWaterfallFooterHeight : function (
)
{
    return 0;
},

/**
 * @method switchPCMode
 * @param {bool} arg0
 */
switchPCMode : function (
bool 
)
{
},

/**
 * @method setCellAtIndexPathCallback
 * @param {function} arg0
 */
setCellAtIndexPathCallback : function (
func 
)
{
},

/**
 * @method dequeueReusableCellWithIdentifier
 * @param {char} arg0
 * @return {ca.CAWaterfallViewCell}
 */
dequeueReusableCellWithIdentifier : function (
char 
)
{
    return ca.CAWaterfallViewCell;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAWaterfallView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAWaterfallView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAWaterfallView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAWaterfallView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAWaterfallView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAWaterfallView;
},

/**
 * @method CAWaterfallView
 * @constructor
 */
CAWaterfallView : function (
)
{
},

};

/**
 * @class CAWaterfallViewCell
 */
ca.CAWaterfallViewCell = {

/**
 * @method getItem
 * @return {unsigned int}
 */
getItem : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @return {ca.CAWaterfallViewCell}
 */
create : function (
str 
)
{
    return ca.CAWaterfallViewCell;
},

/**
 * @method CAWaterfallViewCell
 * @constructor
 */
CAWaterfallViewCell : function (
)
{
},

};

/**
 * @class FileUtils
 */
ca.FileUtils = {

/**
 * @method writeDataToFile
 * @param {unsigned char} arg0
 * @param {unsigned long} arg1
 * @param {String} arg2
 * @return {bool}
 */
writeDataToFile : function (
char, 
long, 
str 
)
{
    return false;
},

/**
 * @method removeFile
 * @param {String} arg0
 * @return {bool}
 */
removeFile : function (
str 
)
{
    return false;
},

/**
 * @method getDataFromFile
 * @param {String} arg0
 * @return {ca.CAData}
 */
getDataFromFile : function (
str 
)
{
    return ca.CAData;
},

/**
 * @method purgeCachedEntries
 */
purgeCachedEntries : function (
)
{
},

/**
 * @method isAbsolutePath
 * @param {String} arg0
 * @return {bool}
 */
isAbsolutePath : function (
str 
)
{
    return false;
},

/**
 * @method renameFile
* @param {String|String} str
* @param {String|String} str
* @param {String} str
* @return {bool|bool}
*/
renameFile : function(
str,
str,
str 
)
{
    return false;
},

/**
 * @method getDefaultResourceRootPath
 * @return {String}
 */
getDefaultResourceRootPath : function (
)
{
    return ;
},

/**
 * @method isPopupNotify
 * @return {bool}
 */
isPopupNotify : function (
)
{
    return false;
},

/**
 * @method removeDirectory
 * @param {String} arg0
 * @return {bool}
 */
removeDirectory : function (
str 
)
{
    return false;
},

/**
 * @method getFileString
 * @param {String} arg0
 * @return {String}
 */
getFileString : function (
str 
)
{
    return ;
},

/**
 * @method getFileSize
 * @param {String} arg0
 * @return {long}
 */
getFileSize : function (
str 
)
{
    return 0;
},

/**
 * @method getFileData
 * @param {String} arg0
 * @param {char} arg1
 * @param {unsigned long} arg2
 * @return {unsigned char}
 */
getFileData : function (
str, 
char, 
long 
)
{
    return 0;
},

/**
 * @method writeStringToFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
writeStringToFile : function (
str, 
str 
)
{
    return false;
},

/**
 * @method getFileDataFromZip
 * @param {String} arg0
 * @param {String} arg1
 * @param {unsigned long} arg2
 * @return {unsigned char}
 */
getFileDataFromZip : function (
str, 
str, 
long 
)
{
    return 0;
},

/**
 * @method addSearchPath
 * @param {String} arg0
 * @param {bool} arg1
 */
addSearchPath : function (
str, 
bool 
)
{
},

/**
 * @method isFileExist
 * @param {String} arg0
 * @return {bool}
 */
isFileExist : function (
str 
)
{
    return false;
},

/**
 * @method fullPathForFilename
 * @param {String} arg0
 * @return {String}
 */
fullPathForFilename : function (
str 
)
{
    return ;
},

/**
 * @method fullPathFromRelativeFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
fullPathFromRelativeFile : function (
str, 
str 
)
{
    return ;
},

/**
 * @method getFileExtension
 * @param {String} arg0
 * @return {String}
 */
getFileExtension : function (
str 
)
{
    return ;
},

/**
 * @method setPopupNotify
 * @param {bool} arg0
 */
setPopupNotify : function (
bool 
)
{
},

/**
 * @method isDirectoryExist
 * @param {String} arg0
 * @return {bool}
 */
isDirectoryExist : function (
str 
)
{
    return false;
},

/**
 * @method setDefaultResourceRootPath
 * @param {String} arg0
 */
setDefaultResourceRootPath : function (
str 
)
{
},

/**
 * @method createDirectory
 * @param {String} arg0
 * @return {bool}
 */
createDirectory : function (
str 
)
{
    return false;
},

/**
 * @method loadFilenameLookupDictionaryFromFile
 * @param {String} arg0
 */
loadFilenameLookupDictionaryFromFile : function (
str 
)
{
},

/**
 * @method getWritablePath
 * @return {String}
 */
getWritablePath : function (
)
{
    return ;
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method setDelegate
 * @param {ca.FileUtils} arg0
 */
setDelegate : function (
fileutils 
)
{
},

/**
 * @method getInstance
 * @return {ca.FileUtils}
 */
getInstance : function (
)
{
    return ca.FileUtils;
},

};

/**
 * @class CAWebView
 */
ca.CAWebView = {

/**
 * @method draw
 * @param {ca.Renderer} arg0
 * @param {ca.Mat4} arg1
 * @param {unsigned int} arg2
 */
draw : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method setFinishLoadingCallback
 * @param {function} arg0
 */
setFinishLoadingCallback : function (
func 
)
{
},

/**
 * @method setJSCallback
 * @param {function} arg0
 */
setJSCallback : function (
func 
)
{
},

/**
 * @method canGoBack
 * @return {bool}
 */
canGoBack : function (
)
{
    return false;
},

/**
 * @method loadHTMLString
 * @param {String} arg0
 * @param {String} arg1
 */
loadHTMLString : function (
str, 
str 
)
{
},

/**
 * @method setStartLoadingCallback
 * @param {function} arg0
 */
setStartLoadingCallback : function (
func 
)
{
},

/**
 * @method reload
 */
reload : function (
)
{
},

/**
 * @method goForward
 */
goForward : function (
)
{
},

/**
 * @method goBack
 */
goBack : function (
)
{
},

/**
 * @method setScalesPageToFit
 * @param {bool} arg0
 */
setScalesPageToFit : function (
bool 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method showNativeWeb
 */
showNativeWeb : function (
)
{
},

/**
 * @method loadFile
 * @param {String} arg0
 */
loadFile : function (
str 
)
{
},

/**
 * @method loadURL
 * @param {String} arg0
 */
loadURL : function (
str 
)
{
},

/**
 * @method evaluateJS
 * @param {String} arg0
 * @return {String}
 */
evaluateJS : function (
str 
)
{
    return ;
},

/**
 * @method showLoadingActivity
 * @param {bool} arg0
 */
showLoadingActivity : function (
bool 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method setActivityView
 * @param {ca.CAActivityIndicatorView} arg0
 */
setActivityView : function (
caactivityindicatorview 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method stopLoading
 */
stopLoading : function (
)
{
},

/**
 * @method setFailLoadingCallback
 * @param {function} arg0
 */
setFailLoadingCallback : function (
func 
)
{
},

/**
 * @method getHTMLSource
 * @return {String}
 */
getHTMLSource : function (
)
{
    return ;
},

/**
 * @method canGoForward
 * @return {bool}
 */
canGoForward : function (
)
{
    return false;
},

/**
 * @method setJavascriptInterfaceScheme
 * @param {String} arg0
 */
setJavascriptInterfaceScheme : function (
str 
)
{
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method hideNativeWebAndShowImage
 */
hideNativeWebAndShowImage : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAWebView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAWebView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAWebView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAWebView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAWebView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAWebView;
},

/**
 * @method CAWebView
 * @constructor
 */
CAWebView : function (
)
{
},

};

/**
 * @class CAClippingView
 */
ca.CAClippingView = {

/**
 * @method isClippingEnabled
 * @return {bool}
 */
isClippingEnabled : function (
)
{
    return false;
},

/**
 * @method onEnter
 */
onEnter : function (
)
{
},

/**
 * @method onExit
 */
onExit : function (
)
{
},

/**
 * @method setInverted
 * @param {bool} arg0
 */
setInverted : function (
bool 
)
{
},

/**
 * @method visit
 * @param {ca.Renderer} arg0
 * @param {ca.Mat4} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method setStencil
 * @param {ca.CAView} arg0
 */
setStencil : function (
caview 
)
{
},

/**
 * @method getAlphaThreshold
 * @return {float}
 */
getAlphaThreshold : function (
)
{
    return 0;
},

/**
 * @method init
* @param {ca.CAView} caview
* @return {bool|bool}
*/
init : function(
caview 
)
{
    return false;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getStencil
 * @return {ca.CAView}
 */
getStencil : function (
)
{
    return ca.CAView;
},

/**
 * @method setClippingEnabled
 * @param {bool} arg0
 */
setClippingEnabled : function (
bool 
)
{
},

/**
 * @method setAlphaThreshold
 * @param {float} arg0
 */
setAlphaThreshold : function (
float 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method isInverted
 * @return {bool}
 */
isInverted : function (
)
{
    return false;
},

/**
 * @method create
* @param {ca.CAView} caview
* @return {ca.CAClippingView|ca.CAClippingView}
*/
create : function(
caview 
)
{
    return ca.CAClippingView;
},

};

/**
 * @class CAAlertView
 */
ca.CAAlertView = {

/**
 * @method show
* @param {function} func
*/
show : function(
func 
)
{
},

/**
 * @method setButtonTitles
 * @param {Array} arg0
 */
setButtonTitles : function (
array 
)
{
},

/**
 * @method addButtonTitle
 * @param {String} arg0
 */
addButtonTitle : function (
str 
)
{
},

/**
 * @method create
* @param {String|String} str
* @param {String|String} str
* @param {Array} array
* @return {ca.CAAlertView|ca.CAAlertView}
*/
create : function(
str,
str,
array 
)
{
    return ca.CAAlertView;
},

};

/**
 * @class CAPickerViewDataSource
 */
ca.CAPickerViewDataSource = {

/**
 * @method numberOfComponentsInPickerView
 * @param {ca.CAPickerView} arg0
 * @return {unsigned int}
 */
numberOfComponentsInPickerView : function (
capickerview 
)
{
    return 0;
},

/**
 * @method numberOfRowsInComponent
 * @param {ca.CAPickerView} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
numberOfRowsInComponent : function (
capickerview, 
int 
)
{
    return 0;
},

/**
 * @method viewForSelect
 * @param {ca.CAPickerView} arg0
 * @param {unsigned int} arg1
 * @param {size_object} arg2
 * @return {ca.CAView}
 */
viewForSelect : function (
capickerview, 
int, 
dsize 
)
{
    return ca.CAView;
},

/**
 * @method viewForRow
 * @param {ca.CAPickerView} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {ca.CAView}
 */
viewForRow : function (
capickerview, 
int, 
int 
)
{
    return ca.CAView;
},

/**
 * @method widthForComponent
 * @param {ca.CAPickerView} arg0
 * @param {unsigned int} arg1
 * @return {float}
 */
widthForComponent : function (
capickerview, 
int 
)
{
    return 0;
},

/**
 * @method titleForRow
 * @param {ca.CAPickerView} arg0
 * @param {unsigned int} arg1
 * @param {unsigned int} arg2
 * @return {char}
 */
titleForRow : function (
capickerview, 
int, 
int 
)
{
    return 0;
},

/**
 * @method rowHeightForComponent
 * @param {ca.CAPickerView} arg0
 * @param {unsigned int} arg1
 * @return {float}
 */
rowHeightForComponent : function (
capickerview, 
int 
)
{
    return 0;
},

};

/**
 * @class CAPickerView
 */
ca.CAPickerView = {

/**
 * @method setViewForSelectedCallback
 * @param {function} arg0
 */
setViewForSelectedCallback : function (
func 
)
{
},

/**
 * @method setTitleForRowCallback
 * @param {function} arg0
 */
setTitleForRowCallback : function (
func 
)
{
},

/**
 * @method setFontSizeNormal
 * @param {float} arg0
 */
setFontSizeNormal : function (
float 
)
{
},

/**
 * @method setFontSizeSelected
 * @param {float} arg0
 */
setFontSizeSelected : function (
float 
)
{
},

/**
 * @method setHeightForComponentCallback
 * @param {function} arg0
 */
setHeightForComponentCallback : function (
func 
)
{
},

/**
 * @method setDidSelectRowCallback
 * @param {function} arg0
 */
setDidSelectRowCallback : function (
func 
)
{
},

/**
 * @method getFontSizeNormal
 * @return {float}
 */
getFontSizeNormal : function (
)
{
    return 0;
},

/**
 * @method getPickerViewDataSource
 * @return {ca.CAPickerViewDataSource}
 */
getPickerViewDataSource : function (
)
{
    return ca.CAPickerViewDataSource;
},

/**
 * @method reloadAllComponents
 */
reloadAllComponents : function (
)
{
},

/**
 * @method getPickerViewDelegate
 * @return {ca.CAPickerViewDelegate}
 */
getPickerViewDelegate : function (
)
{
    return ca.CAPickerViewDelegate;
},

/**
 * @method getFontSizeSelected
 * @return {float}
 */
getFontSizeSelected : function (
)
{
    return 0;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setNumberOfComponentsCallback
 * @param {function} arg0
 */
setNumberOfComponentsCallback : function (
func 
)
{
},

/**
 * @method reloadComponent
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @param {bool} arg2
 */
reloadComponent : function (
int, 
int, 
bool 
)
{
},

/**
 * @method setViewForRowCallback
 * @param {function} arg0
 */
setViewForRowCallback : function (
func 
)
{
},

/**
 * @method getFontColorSelected
 * @return {color4b_object}
 */
getFontColorSelected : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method visitEve
 */
visitEve : function (
)
{
},

/**
 * @method setBackgroundColor
 * @param {color4b_object} arg0
 */
setBackgroundColor : function (
cacolor4b 
)
{
},

/**
 * @method setNumberOfRowsInComponentCallback
 * @param {function} arg0
 */
setNumberOfRowsInComponentCallback : function (
func 
)
{
},

/**
 * @method setFontColorNormal
 * @param {color4b_object} arg0
 */
setFontColorNormal : function (
cacolor4b 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getSeparateColor
 * @return {color4b_object}
 */
getSeparateColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method selectRow
 * @param {unsigned int} arg0
 * @param {unsigned int} arg1
 * @param {bool} arg2
 */
selectRow : function (
int, 
int, 
bool 
)
{
},

/**
 * @method setWidthForComponentCallback
 * @param {function} arg0
 */
setWidthForComponentCallback : function (
func 
)
{
},

/**
 * @method setFontColorSelected
 * @param {color4b_object} arg0
 */
setFontColorSelected : function (
cacolor4b 
)
{
},

/**
 * @method selectedRowInComponent
 * @param {unsigned int} arg0
 * @return {int}
 */
selectedRowInComponent : function (
int 
)
{
    return 0;
},

/**
 * @method setSeparateColor
 * @param {color4b_object} arg0
 */
setSeparateColor : function (
cacolor4b 
)
{
},

/**
 * @method getFontColorNormal
 * @return {color4b_object}
 */
getFontColorNormal : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method create
 * @return {ca.CAPickerView}
 */
create : function (
)
{
    return ca.CAPickerView;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CAPickerView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CAPickerView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CAPickerView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CAPickerView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CAPickerView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CAPickerView;
},

/**
 * @method CAPickerView
 * @constructor
 */
CAPickerView : function (
)
{
},

};

/**
 * @class CADatePickerView
 */
ca.CADatePickerView = {

/**
 * @method onEnter
 */
onEnter : function (
)
{
},

/**
 * @method onExit
 */
onExit : function (
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setDate
 * @param {int} arg0
 * @param {int} arg1
 * @param {int} arg2
 * @param {bool} arg3
 */
setDate : function (
int, 
int, 
int, 
bool 
)
{
},

/**
 * @method create
 * @param {ca.CADatePickerView::Mode} arg0
 * @return {ca.CADatePickerView}
 */
create : function (
mode 
)
{
    return ca.CADatePickerView;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @param {ca.CADatePickerView::Mode} arg1
 * @return {ca.CADatePickerView}
 */
createWithFrame : function (
drect, 
mode 
)
{
    return ca.CADatePickerView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @param {ca.CADatePickerView::Mode} arg1
 * @return {ca.CADatePickerView}
 */
createWithLayout : function (
dlayout, 
mode 
)
{
    return ca.CADatePickerView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @param {ca.CADatePickerView::Mode} arg1
 * @return {ca.CADatePickerView}
 */
createWithCenter : function (
drect, 
mode 
)
{
    return ca.CADatePickerView;
},

/**
 * @method CADatePickerView
 * @constructor
 * @param {ca.CADatePickerView::Mode} arg0
 */
CADatePickerView : function (
mode 
)
{
},

};

/**
 * @class CADrawView
 */
ca.CADrawView = {

/**
 * @method drawLine
 * @param {point_object} arg0
 * @param {point_object} arg1
 * @param {color4b_object} arg2
 */
drawLine : function (
dpoint, 
dpoint, 
cacolor4b 
)
{
},

/**
 * @method drawPoints
* @param {point_object|point_object} dpoint
* @param {unsigned int|unsigned int} int
* @param {float|color4b_object} float
* @param {color4b_object} cacolor4b
*/
drawPoints : function(
dpoint,
int,
float,
cacolor4b 
)
{
},

/**
 * @method drawRect
* @param {point_object|point_object} dpoint
* @param {point_object|point_object} dpoint
* @param {point_object|color4b_object} dpoint
* @param {point_object} dpoint
* @param {color4b_object} cacolor4b
*/
drawRect : function(
dpoint,
dpoint,
dpoint,
dpoint,
cacolor4b 
)
{
},

/**
 * @method drawSolidCircle
* @param {point_object|point_object} dpoint
* @param {float|float} float
* @param {float|float} float
* @param {unsigned int|unsigned int} int
* @param {color4b_object|float} cacolor4b
* @param {float} float
* @param {color4b_object} cacolor4b
*/
drawSolidCircle : function(
dpoint,
float,
float,
int,
float,
float,
cacolor4b 
)
{
},

/**
 * @method setLineWidth
 * @param {int} arg0
 */
setLineWidth : function (
int 
)
{
},

/**
 * @method onDrawGLPoint
 * @param {ca.Mat4} arg0
 * @param {unsigned int} arg1
 */
onDrawGLPoint : function (
mat4, 
int 
)
{
},

/**
 * @method drawPolygon
 * @param {point_object} arg0
 * @param {int} arg1
 * @param {color4b_object} arg2
 * @param {float} arg3
 * @param {color4b_object} arg4
 */
drawPolygon : function (
dpoint, 
int, 
cacolor4b, 
float, 
cacolor4b 
)
{
},

/**
 * @method drawDot
 * @param {point_object} arg0
 * @param {float} arg1
 * @param {color4b_object} arg2
 */
drawDot : function (
dpoint, 
float, 
cacolor4b 
)
{
},

/**
 * @method drawCatmullRom
 * @param {ca.PointArray} arg0
 * @param {unsigned int} arg1
 * @param {color4b_object} arg2
 */
drawCatmullRom : function (
pointarray, 
int, 
cacolor4b 
)
{
},

/**
 * @method drawSegment
 * @param {point_object} arg0
 * @param {point_object} arg1
 * @param {float} arg2
 * @param {color4b_object} arg3
 */
drawSegment : function (
dpoint, 
dpoint, 
float, 
cacolor4b 
)
{
},

/**
 * @method getBlendFunc
 * @return {ca.BlendFunc}
 */
getBlendFunc : function (
)
{
    return ca.BlendFunc;
},

/**
 * @method onDraw
 * @param {ca.Mat4} arg0
 * @param {unsigned int} arg1
 */
onDraw : function (
mat4, 
int 
)
{
},

/**
 * @method drawCircle
* @param {point_object|point_object} dpoint
* @param {float|float} float
* @param {float|float} float
* @param {unsigned int|unsigned int} int
* @param {bool|bool} bool
* @param {color4b_object|float} cacolor4b
* @param {float} float
* @param {color4b_object} cacolor4b
*/
drawCircle : function(
dpoint,
float,
float,
int,
bool,
float,
float,
cacolor4b 
)
{
},

/**
 * @method drawQuadBezier
 * @param {point_object} arg0
 * @param {point_object} arg1
 * @param {point_object} arg2
 * @param {unsigned int} arg3
 * @param {color4b_object} arg4
 */
drawQuadBezier : function (
dpoint, 
dpoint, 
dpoint, 
int, 
cacolor4b 
)
{
},

/**
 * @method onDrawGLLine
 * @param {ca.Mat4} arg0
 * @param {unsigned int} arg1
 */
onDrawGLLine : function (
mat4, 
int 
)
{
},

/**
 * @method drawSolidPoly
 * @param {point_object} arg0
 * @param {unsigned int} arg1
 * @param {color4b_object} arg2
 */
drawSolidPoly : function (
dpoint, 
int, 
cacolor4b 
)
{
},

/**
 * @method drawTriangle
 * @param {point_object} arg0
 * @param {point_object} arg1
 * @param {point_object} arg2
 * @param {color4b_object} arg3
 */
drawTriangle : function (
dpoint, 
dpoint, 
dpoint, 
cacolor4b 
)
{
},

/**
 * @method setBlendFunc
 * @param {ca.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method drawCardinalSpline
 * @param {ca.PointArray} arg0
 * @param {float} arg1
 * @param {unsigned int} arg2
 * @param {color4b_object} arg3
 */
drawCardinalSpline : function (
pointarray, 
float, 
int, 
cacolor4b 
)
{
},

/**
 * @method drawSolidRect
 * @param {point_object} arg0
 * @param {point_object} arg1
 * @param {color4b_object} arg2
 */
drawSolidRect : function (
dpoint, 
dpoint, 
cacolor4b 
)
{
},

/**
 * @method getLineWidth
 * @return {float}
 */
getLineWidth : function (
)
{
    return 0;
},

/**
 * @method drawPoly
 * @param {point_object} arg0
 * @param {unsigned int} arg1
 * @param {bool} arg2
 * @param {color4b_object} arg3
 */
drawPoly : function (
dpoint, 
int, 
bool, 
cacolor4b 
)
{
},

/**
 * @method drawPoint
 * @param {point_object} arg0
 * @param {float} arg1
 * @param {color4b_object} arg2
 */
drawPoint : function (
dpoint, 
float, 
cacolor4b 
)
{
},

/**
 * @method drawCubicBezier
 * @param {point_object} arg0
 * @param {point_object} arg1
 * @param {point_object} arg2
 * @param {point_object} arg3
 * @param {unsigned int} arg4
 * @param {color4b_object} arg5
 */
drawCubicBezier : function (
dpoint, 
dpoint, 
dpoint, 
dpoint, 
int, 
cacolor4b 
)
{
},

/**
 * @method create
 * @return {ca.CADrawView}
 */
create : function (
)
{
    return ca.CADrawView;
},

/**
 * @method CADrawView
 * @constructor
 */
CADrawView : function (
)
{
},

};

/**
 * @class CAUserDefault
 */
ca.CAUserDefault = {

/**
 * @method setIntegerForKey
 * @param {char} arg0
 * @param {int} arg1
 */
setIntegerForKey : function (
char, 
int 
)
{
},

/**
 * @method getFloatForKey
* @param {char|char} char
* @param {float} float
* @return {float|float}
*/
getFloatForKey : function(
char,
float 
)
{
    return 0;
},

/**
 * @method getBoolForKey
* @param {char|char} char
* @param {bool} bool
* @return {bool|bool}
*/
getBoolForKey : function(
char,
bool 
)
{
    return false;
},

/**
 * @method setDoubleForKey
 * @param {char} arg0
 * @param {double} arg1
 */
setDoubleForKey : function (
char, 
double 
)
{
},

/**
 * @method setFloatForKey
 * @param {char} arg0
 * @param {float} arg1
 */
setFloatForKey : function (
char, 
float 
)
{
},

/**
 * @method getStringForKey
* @param {char|char} char
* @param {String} str
* @return {String|String}
*/
getStringForKey : function(
char,
str 
)
{
    return ;
},

/**
 * @method setStringForKey
 * @param {char} arg0
 * @param {String} arg1
 */
setStringForKey : function (
char, 
str 
)
{
},

/**
 * @method flush
 */
flush : function (
)
{
},

/**
 * @method getIntegerForKey
* @param {char|char} char
* @param {int} int
* @return {int|int}
*/
getIntegerForKey : function(
char,
int 
)
{
    return 0;
},

/**
 * @method getDoubleForKey
* @param {char|char} char
* @param {double} double
* @return {double|double}
*/
getDoubleForKey : function(
char,
double 
)
{
    return 0;
},

/**
 * @method setBoolForKey
 * @param {char} arg0
 * @param {bool} arg1
 */
setBoolForKey : function (
char, 
bool 
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getXMLFilePath
 * @return {String}
 */
getXMLFilePath : function (
)
{
    return ;
},

/**
 * @method isXMLFileExist
 * @return {bool}
 */
isXMLFileExist : function (
)
{
    return false;
},

/**
 * @method getInstance
 * @return {ca.CAUserDefault}
 */
getInstance : function (
)
{
    return ca.CAUserDefault;
},

};

/**
 * @class CAHttpRequest
 */
ca.CAHttpRequest = {

/**
 * @method getUrl
 * @return {char}
 */
getUrl : function (
)
{
    return 0;
},

/**
 * @method setResponseCallback
 * @param {function} arg0
 */
setResponseCallback : function (
func 
)
{
},

/**
 * @method getCallback
 * @return {function}
 */
getCallback : function (
)
{
    return std::function<void (CrossApp::CAHttpClient , CrossApp::CAHttpResponse )>;
},

/**
 * @method getThreadID
 * @return {int}
 */
getThreadID : function (
)
{
    return 0;
},

/**
 * @method getRequestData
 * @return {char}
 */
getRequestData : function (
)
{
    return 0;
},

/**
 * @method setUrl
 * @param {String} arg0
 */
setUrl : function (
str 
)
{
},

/**
 * @method autorelease
 * @return {ca.CAObject}
 */
autorelease : function (
)
{
    return ca.CAObject;
},

/**
 * @method getHeaders
 * @return {Array}
 */
getHeaders : function (
)
{
    return new Array();
},

/**
 * @method getRequestType
 * @return {ca.CAHttpRequest::Type}
 */
getRequestType : function (
)
{
    return 0;
},

/**
 * @method setThreadID
 * @param {int} arg0
 */
setThreadID : function (
int 
)
{
},

/**
 * @method setRequestData
 * @param {char} arg0
 * @param {unsigned long} arg1
 */
setRequestData : function (
char, 
long 
)
{
},

/**
 * @method getRequestDataSize
 * @return {int}
 */
getRequestDataSize : function (
)
{
    return 0;
},

/**
 * @method setRequestType
 * @param {ca.CAHttpRequest::Type} arg0
 */
setRequestType : function (
type 
)
{
},

/**
 * @method setFileNameToPost
 * @param {String} arg0
 */
setFileNameToPost : function (
str 
)
{
},

/**
 * @method setHeaders
 * @param {Array} arg0
 */
setHeaders : function (
array 
)
{
},

/**
 * @method getFileNameToPost
 * @return {char}
 */
getFileNameToPost : function (
)
{
    return 0;
},

/**
 * @method create
 * @return {ca.CAHttpRequest}
 */
create : function (
)
{
    return ca.CAHttpRequest;
},

/**
 * @method CAHttpRequest
 * @constructor
 */
CAHttpRequest : function (
)
{
},

};

/**
 * @class CAHttpResponse
 */
ca.CAHttpResponse = {

/**
 * @method setErrorBuffer
 * @param {char} arg0
 */
setErrorBuffer : function (
char 
)
{
},

/**
 * @method getErrorBuffer
 * @return {char}
 */
getErrorBuffer : function (
)
{
    return 0;
},

/**
 * @method isSucceed
 * @return {bool}
 */
isSucceed : function (
)
{
    return false;
},

/**
 * @method getHttpRequest
 * @return {ca.CAHttpRequest}
 */
getHttpRequest : function (
)
{
    return ca.CAHttpRequest;
},

/**
 * @method setResponseData
 * @param {ca.CAData} arg0
 */
setResponseData : function (
cadata 
)
{
},

/**
 * @method autorelease
 * @return {ca.CAObject}
 */
autorelease : function (
)
{
    return ca.CAObject;
},

/**
 * @method getResponseData
 * @return {ca.CAData}
 */
getResponseData : function (
)
{
    return ca.CAData;
},

/**
 * @method setResponseHeader
 * @param {ca.CAData} arg0
 */
setResponseHeader : function (
cadata 
)
{
},

/**
 * @method setResponseCode
 * @param {long} arg0
 */
setResponseCode : function (
long 
)
{
},

/**
 * @method getResponseCode
 * @return {long}
 */
getResponseCode : function (
)
{
    return 0;
},

/**
 * @method getResponseHeader
 * @return {ca.CAData}
 */
getResponseHeader : function (
)
{
    return ca.CAData;
},

/**
 * @method setSucceed
 * @param {bool} arg0
 */
setSucceed : function (
bool 
)
{
},

/**
 * @method CAHttpResponse
 * @constructor
 * @param {ca.CAHttpRequest} arg0
 */
CAHttpResponse : function (
cahttprequest 
)
{
},

};

/**
 * @class CAHttpClient
 */
ca.CAHttpClient = {

/**
 * @method sendImmediate
 * @param {ca.CAHttpRequest} arg0
 */
sendImmediate : function (
cahttprequest 
)
{
},

/**
 * @method getSSLVerification
 * @return {String}
 */
getSSLVerification : function (
)
{
    return ;
},

/**
 * @method getCookie
 * @return {CAHttpCookie}
 */
getCookie : function (
)
{
    return CAHttpCookie;
},

/**
 * @method setTimeoutForConnect
 * @param {int} arg0
 */
setTimeoutForConnect : function (
int 
)
{
},

/**
 * @method setTimeoutForRead
 * @param {int} arg0
 */
setTimeoutForRead : function (
int 
)
{
},

/**
 * @method send
 * @param {ca.CAHttpRequest} arg0
 */
send : function (
cahttprequest 
)
{
},

/**
 * @method enableCookies
 * @param {char} arg0
 */
enableCookies : function (
char 
)
{
},

/**
 * @method setSSLVerification
 * @param {String} arg0
 */
setSSLVerification : function (
str 
)
{
},

/**
 * @method getRequestCount
 * @return {unsigned long}
 */
getRequestCount : function (
)
{
    return 0;
},

/**
 * @method getTimeoutForConnect
 * @return {int}
 */
getTimeoutForConnect : function (
)
{
    return 0;
},

/**
 * @method getTimeoutForRead
 * @return {int}
 */
getTimeoutForRead : function (
)
{
    return 0;
},

/**
 * @method getCookieFilename
 * @return {String}
 */
getCookieFilename : function (
)
{
    return ;
},

/**
 * @method destroyInstance
 * @param {int} arg0
 */
destroyInstance : function (
int 
)
{
},

/**
 * @method destroyAllInstance
 */
destroyAllInstance : function (
)
{
},

/**
 * @method getInstance
 * @param {int} arg0
 * @return {ca.CAHttpClient}
 */
getInstance : function (
int 
)
{
    return ca.CAHttpClient;
},

};

/**
 * @class CADownloadManager
 */
ca.CADownloadManager = {

/**
 * @method getDownloadMaxCount
 * @return {int}
 */
getDownloadMaxCount : function (
)
{
    return 0;
},

/**
 * @method setDownloadMaxCount
 * @param {int} arg0
 */
setDownloadMaxCount : function (
int 
)
{
},

/**
 * @method getLocalFileSize
 * @param {unsigned long} arg0
 * @return {unsigned long}
 */
getLocalFileSize : function (
long 
)
{
    return 0;
},

/**
 * @method enqueueDownload
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {String} arg3
 * @return {unsigned long}
 */
enqueueDownload : function (
str, 
str, 
str, 
str 
)
{
    return 0;
},

/**
 * @method clearOnSuccessDownloadAllRecord
 */
clearOnSuccessDownloadAllRecord : function (
)
{
},

/**
 * @method eraseDownload
 * @param {unsigned long} arg0
 */
eraseDownload : function (
long 
)
{
},

/**
 * @method enqueueDownloadEx
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {String} arg3
 * @return {unsigned long}
 */
enqueueDownloadEx : function (
str, 
str, 
str, 
str 
)
{
    return 0;
},

/**
 * @method isDownloading
 * @param {unsigned long} arg0
 * @return {bool}
 */
isDownloading : function (
long 
)
{
    return false;
},

/**
 * @method clearOnSuccessDownloadRecord
 * @param {unsigned long} arg0
 */
clearOnSuccessDownloadRecord : function (
long 
)
{
},

/**
 * @method getDownloadUrl
 * @param {unsigned long} arg0
 * @return {char}
 */
getDownloadUrl : function (
long 
)
{
    return 0;
},

/**
 * @method resumeDownload
 * @param {unsigned long} arg0
 */
resumeDownload : function (
long 
)
{
},

/**
 * @method getDownloadManagerDelegate
 * @return {ca.CADownloadManagerDelegate}
 */
getDownloadManagerDelegate : function (
)
{
    return ca.CADownloadManagerDelegate;
},

/**
 * @method getTotalFileSize
 * @param {unsigned long} arg0
 * @return {unsigned long}
 */
getTotalFileSize : function (
long 
)
{
    return 0;
},

/**
 * @method getFilePath
 * @param {unsigned long} arg0
 * @return {char}
 */
getFilePath : function (
long 
)
{
    return 0;
},

/**
 * @method getDownloadHeader
 * @param {unsigned long} arg0
 * @return {char}
 */
getDownloadHeader : function (
long 
)
{
    return 0;
},

/**
 * @method pauseDownload
 * @param {unsigned long} arg0
 */
pauseDownload : function (
long 
)
{
},

/**
 * @method isFinished
 * @param {unsigned long} arg0
 * @return {bool}
 */
isFinished : function (
long 
)
{
    return false;
},

/**
 * @method getDownloadAllTextTags
 * @return {Array}
 */
getDownloadAllTextTags : function (
)
{
    return new Array();
},

/**
 * @method getStartTime
 * @param {unsigned long} arg0
 * @return {char}
 */
getStartTime : function (
long 
)
{
    return 0;
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {ca.CADownloadManager}
 */
getInstance : function (
)
{
    return ca.CADownloadManager;
},

};

/**
 * @class CATextField
 */
ca.CATextField = {

/**
 * @method getFontSize
 * @return {int}
 */
getFontSize : function (
)
{
    return 0;
},

/**
 * @method setKeyboardType
 * @param {ca.CATextField::KeyboardType} arg0
 */
setKeyboardType : function (
keyboardtype 
)
{
},

/**
 * @method getText
 * @return {String}
 */
getText : function (
)
{
    return ;
},

/**
 * @method setClearButtonMode
 * @param {ca.CATextField::ClearButtonMode} arg0
 */
setClearButtonMode : function (
clearbuttonmode 
)
{
},

/**
 * @method getTextColor
 * @return {color4b_object}
 */
getTextColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getKeyboardType
 * @return {ca.CATextField::KeyboardType}
 */
getKeyboardType : function (
)
{
    return 0;
},

/**
 * @method isSecureTextEntry
 * @return {bool}
 */
isSecureTextEntry : function (
)
{
    return false;
},

/**
 * @method getAlign
 * @return {ca.CATextField::Align}
 */
getAlign : function (
)
{
    return 0;
},

/**
 * @method setAlign
 * @param {ca.CATextField::Align} arg0
 */
setAlign : function (
align 
)
{
},

/**
 * @method setMarginImageLeft
 * @param {size_object} arg0
 * @param {String} arg1
 */
setMarginImageLeft : function (
dsize, 
str 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method setMarginRight
 * @param {int} arg0
 */
setMarginRight : function (
int 
)
{
},

/**
 * @method getClearButtonMode
 * @return {ca.CATextField::ClearButtonMode}
 */
getClearButtonMode : function (
)
{
    return 0;
},

/**
 * @method getReturnType
 * @return {ca.CATextField::ReturnType}
 */
getReturnType : function (
)
{
    return 0;
},

/**
 * @method getPlaceHolderText
 * @return {String}
 */
getPlaceHolderText : function (
)
{
    return ;
},

/**
 * @method setAllowkeyBoardHide
 * @param {bool} arg0
 */
setAllowkeyBoardHide : function (
bool 
)
{
},

/**
 * @method getPlaceHolderColor
 * @return {color4b_object}
 */
getPlaceHolderColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setPlaceHolderText
 * @param {String} arg0
 */
setPlaceHolderText : function (
str 
)
{
},

/**
 * @method setBackgroundImage
 * @param {ca.CAImage} arg0
 */
setBackgroundImage : function (
caimage 
)
{
},

/**
 * @method getMarginRight
 * @return {int}
 */
getMarginRight : function (
)
{
    return 0;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method setMarginLeft
 * @param {int} arg0
 */
setMarginLeft : function (
int 
)
{
},

/**
 * @method setFontSize
 * @param {int} arg0
 */
setFontSize : function (
int 
)
{
},

/**
 * @method setPlaceHolderColor
 * @param {color4b_object} arg0
 */
setPlaceHolderColor : function (
cacolor4b 
)
{
},

/**
 * @method setTextColor
 * @param {color4b_object} arg0
 */
setTextColor : function (
cacolor4b 
)
{
},

/**
 * @method setReturnType
 * @param {ca.CATextField::ReturnType} arg0
 */
setReturnType : function (
returntype 
)
{
},

/**
 * @method getDelegate
 * @return {ca.CATextFieldDelegate}
 */
getDelegate : function (
)
{
    return ca.CATextFieldDelegate;
},

/**
 * @method getMaxLength
 * @return {int}
 */
getMaxLength : function (
)
{
    return 0;
},

/**
 * @method resignFirstResponder
 * @return {bool}
 */
resignFirstResponder : function (
)
{
    return false;
},

/**
 * @method setText
 * @param {String} arg0
 */
setText : function (
str 
)
{
},

/**
 * @method setMarginImageRight
 * @param {size_object} arg0
 * @param {String} arg1
 */
setMarginImageRight : function (
dsize, 
str 
)
{
},

/**
 * @method getMarginLeft
 * @return {int}
 */
getMarginLeft : function (
)
{
    return 0;
},

/**
 * @method setMaxLength
 * @param {int} arg0
 */
setMaxLength : function (
int 
)
{
},

/**
 * @method becomeFirstResponder
 * @return {bool}
 */
becomeFirstResponder : function (
)
{
    return false;
},

/**
 * @method setSecureTextEntry
 * @param {bool} arg0
 */
setSecureTextEntry : function (
bool 
)
{
},

/**
 * @method isAllowkeyBoardHide
 * @return {bool}
 */
isAllowkeyBoardHide : function (
)
{
    return false;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CATextField}
 */
createWithFrame : function (
drect 
)
{
    return ca.CATextField;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CATextField}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CATextField;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CATextField}
 */
createWithCenter : function (
drect 
)
{
    return ca.CATextField;
},

/**
 * @method CATextField
 * @constructor
 */
CATextField : function (
)
{
},

};

/**
 * @class CATextView
 */
ca.CATextView = {

/**
 * @method getDelegate
 * @return {ca.CATextViewDelegate}
 */
getDelegate : function (
)
{
    return ca.CATextViewDelegate;
},

/**
 * @method getFontSize
 * @return {int}
 */
getFontSize : function (
)
{
    return 0;
},

/**
 * @method setAlign
 * @param {ca.CATextView::Align} arg0
 */
setAlign : function (
align 
)
{
},

/**
 * @method resignFirstResponder
 * @return {bool}
 */
resignFirstResponder : function (
)
{
    return false;
},

/**
 * @method setBackgroundImage
 * @param {ca.CAImage} arg0
 */
setBackgroundImage : function (
caimage 
)
{
},

/**
 * @method setText
 * @param {String} arg0
 */
setText : function (
str 
)
{
},

/**
 * @method setFontSize
 * @param {int} arg0
 */
setFontSize : function (
int 
)
{
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getTextColor
 * @return {color4b_object}
 */
getTextColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method becomeFirstResponder
 * @return {bool}
 */
becomeFirstResponder : function (
)
{
    return false;
},

/**
 * @method getText
 * @return {String}
 */
getText : function (
)
{
    return ;
},

/**
 * @method setTextColor
 * @param {color4b_object} arg0
 */
setTextColor : function (
cacolor4b 
)
{
},

/**
 * @method getReturnType
 * @return {ca.CATextView::ReturnType}
 */
getReturnType : function (
)
{
    return 0;
},

/**
 * @method getAlign
 * @return {ca.CATextView::Align}
 */
getAlign : function (
)
{
    return 0;
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method setReturnType
 * @param {ca.CATextView::ReturnType} arg0
 */
setReturnType : function (
returntype 
)
{
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {ca.CATextView}
 */
createWithFrame : function (
drect 
)
{
    return ca.CATextView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {ca.CATextView}
 */
createWithLayout : function (
dlayout 
)
{
    return ca.CATextView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {ca.CATextView}
 */
createWithCenter : function (
drect 
)
{
    return ca.CATextView;
},

/**
 * @method CATextView
 * @constructor
 */
CATextView : function (
)
{
},

};

/**
 * @class CGNode
 */
ca.CGNode = {

/**
 * @method addChild
 * @param {ca.CGNode} arg0
 */
addChild : function (
cgnode 
)
{
},

/**
 * @method getShaderProgram
 * @return {ca.GLProgram}
 */
getShaderProgram : function (
)
{
    return ca.GLProgram;
},

/**
 * @method getChildren
 * @return {Array}
 */
getChildren : function (
)
{
    return new Array();
},

/**
 * @method setViewToParentTransform
 * @param {ca.Mat4} arg0
 */
setViewToParentTransform : function (
mat4 
)
{
},

/**
 * @method setOnExitCallback
 * @param {function} arg0
 */
setOnExitCallback : function (
func 
)
{
},

/**
 * @method isOpacityModifyRGB
 * @return {bool}
 */
isOpacityModifyRGB : function (
)
{
    return false;
},

/**
 * @method updateDisplayedAlpha
 * @param {float} arg0
 */
updateDisplayedAlpha : function (
float 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method getCameraMask
 * @return {unsigned short}
 */
getCameraMask : function (
)
{
    return 0;
},

/**
 * @method setAlpha
 * @param {float} arg0
 */
setAlpha : function (
float 
)
{
},

/**
 * @method getWorldToViewAffineTransform
 * @return {ca.AffineTransform}
 */
getWorldToViewAffineTransform : function (
)
{
    return ca.AffineTransform;
},

/**
 * @method setZOrder
 * @param {int} arg0
 */
setZOrder : function (
int 
)
{
},

/**
 * @method setScaleZ
 * @param {float} arg0
 */
setScaleZ : function (
float 
)
{
},

/**
 * @method setScaleY
 * @param {float} arg0
 */
setScaleY : function (
float 
)
{
},

/**
 * @method setScaleX
 * @param {float} arg0
 */
setScaleX : function (
float 
)
{
},

/**
 * @method processParentFlags
 * @param {ca.Mat4} arg0
 * @param {unsigned int} arg1
 * @return {unsigned int}
 */
processParentFlags : function (
mat4, 
int 
)
{
    return 0;
},

/**
 * @method visitEve
 */
visitEve : function (
)
{
},

/**
 * @method setonEnterTransitionDidFinishCallback
 * @param {function} arg0
 */
setonEnterTransitionDidFinishCallback : function (
func 
)
{
},

/**
 * @method convertRectToWorldSpace
 * @param {rect_object} arg0
 * @return {rect_object}
 */
convertRectToWorldSpace : function (
drect 
)
{
    return ca.DRect;
},

/**
 * @method getonEnterTransitionDidFinishCallback
 * @return {function}
 */
getonEnterTransitionDidFinishCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method getNodeToWorldAffineTransform
 * @return {ca.AffineTransform}
 */
getNodeToWorldAffineTransform : function (
)
{
    return ca.AffineTransform;
},

/**
 * @method getNodeToWorldTransform
 * @return {ca.Mat4}
 */
getNodeToWorldTransform : function (
)
{
    return ca.Mat4;
},

/**
 * @method onExit
 */
onExit : function (
)
{
},

/**
 * @method getPosition3D
 * @return {point_object}
 */
getPosition3D : function (
)
{
    return ca.DPoint3D;
},

/**
 * @method removeChild
 * @param {ca.CGNode} arg0
 */
removeChild : function (
cgnode 
)
{
},

/**
 * @method convertToWorldSpace
 * @param {point_object} arg0
 * @return {point_object}
 */
convertToWorldSpace : function (
dpoint 
)
{
    return ca.DPoint;
},

/**
 * @method getAlpha
 * @return {float}
 */
getAlpha : function (
)
{
    return 0;
},

/**
 * @method setSkewX
 * @param {float} arg0
 */
setSkewX : function (
float 
)
{
},

/**
 * @method setSkewY
 * @param {float} arg0
 */
setSkewY : function (
float 
)
{
},

/**
 * @method setOnEnterCallback
 * @param {function} arg0
 */
setOnEnterCallback : function (
func 
)
{
},

/**
 * @method onEnterTransitionDidFinish
 */
onEnterTransitionDidFinish : function (
)
{
},

/**
 * @method getWorldToViewTransform
 * @return {ca.Mat4}
 */
getWorldToViewTransform : function (
)
{
    return ca.Mat4;
},

/**
 * @method stopActionsByFlags
 * @param {unsigned int} arg0
 */
stopActionsByFlags : function (
int 
)
{
},

/**
 * @method setNormalizedPosition
 * @param {point_object} arg0
 */
setNormalizedPosition : function (
dpoint 
)
{
},

/**
 * @method removeChildByTextTag
 * @param {String} arg0
 */
removeChildByTextTag : function (
str 
)
{
},

/**
 * @method setonExitTransitionDidStartCallback
 * @param {function} arg0
 */
setonExitTransitionDidStartCallback : function (
func 
)
{
},

/**
 * @method convertTouchToNodeSpace
 * @param {ca.CATouch} arg0
 * @return {point_object}
 */
convertTouchToNodeSpace : function (
catouch 
)
{
    return ca.DPoint;
},

/**
 * @method getRotationZ
 * @return {float}
 */
getRotationZ : function (
)
{
    return 0;
},

/**
 * @method removeAllChildren
 */
removeAllChildren : function (
)
{
},

/**
 * @method getRotationX
 * @return {float}
 */
getRotationX : function (
)
{
    return 0;
},

/**
 * @method getRotationY
 * @return {float}
 */
getRotationY : function (
)
{
    return 0;
},

/**
 * @method convertRectToNodeSpace
 * @param {rect_object} arg0
 * @return {rect_object}
 */
convertRectToNodeSpace : function (
drect 
)
{
    return ca.DRect;
},

/**
 * @method getCAView
 * @return {ca.CAView}
 */
getCAView : function (
)
{
    return ca.CAView;
},

/**
 * @method description
 * @return {char}
 */
description : function (
)
{
    return 0;
},

/**
 * @method getNodeToParentAffineTransform
* @param {ca.CGNode} cgnode
* @return {ca.AffineTransform|ca.AffineTransform}
*/
getNodeToParentAffineTransform : function(
cgnode 
)
{
    return ca.AffineTransform;
},

/**
 * @method getonExitTransitionDidStartCallback
 * @return {function}
 */
getonExitTransitionDidStartCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method setParent
 * @param {ca.CGNode} arg0
 */
setParent : function (
cgnode 
)
{
},

/**
 * @method convertToNodeSize
 * @param {size_object} arg0
 * @return {size_object}
 */
convertToNodeSize : function (
dsize 
)
{
    return ca.DSize;
},

/**
 * @method getRotation3D
 * @return {point_object}
 */
getRotation3D : function (
)
{
    return ca.DPoint3D;
},

/**
 * @method getNodeToParentTransform
* @param {ca.CGNode} cgnode
* @return {ca.Mat4|ca.Mat4}
*/
getNodeToParentTransform : function(
cgnode 
)
{
    return ca.Mat4;
},

/**
 * @method getOnEnterCallback
 * @return {function}
 */
getOnEnterCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method setCameraMask
 * @param {unsigned short} arg0
 * @param {bool} arg1
 */
setCameraMask : function (
short, 
bool 
)
{
},

/**
 * @method setPosition
 * @param {point_object} arg0
 */
setPosition : function (
dpoint 
)
{
},

/**
 * @method convertToWorldSize
 * @param {size_object} arg0
 * @return {size_object}
 */
convertToWorldSize : function (
dsize 
)
{
    return ca.DSize;
},

/**
 * @method stopActionByTag
 * @param {int} arg0
 */
stopActionByTag : function (
int 
)
{
},

/**
 * @method reorderChild
 * @param {ca.CGNode} arg0
 * @param {int} arg1
 */
reorderChild : function (
cgnode, 
int 
)
{
},

/**
 * @method setGLProgramState
 * @param {ca.GLProgramState} arg0
 */
setGLProgramState : function (
glprogramstate 
)
{
},

/**
 * @method setPositionZ
 * @param {float} arg0
 */
setPositionZ : function (
float 
)
{
},

/**
 * @method setPositionY
 * @param {float} arg0
 */
setPositionY : function (
float 
)
{
},

/**
 * @method setPositionX
 * @param {float} arg0
 */
setPositionX : function (
float 
)
{
},

/**
 * @method getAnchorPoint
 * @return {point_object}
 */
getAnchorPoint : function (
)
{
    return ca.DPoint;
},

/**
 * @method getNumberOfRunningActions
 * @return {unsigned long}
 */
getNumberOfRunningActions : function (
)
{
    return 0;
},

/**
 * @method updateTransform
 */
updateTransform : function (
)
{
},

/**
 * @method isVisible
 * @return {bool}
 */
isVisible : function (
)
{
    return false;
},

/**
 * @method getChildrenCount
 * @return {unsigned int}
 */
getChildrenCount : function (
)
{
    return 0;
},

/**
 * @method setAnchorPoint
 * @param {point_object} arg0
 */
setAnchorPoint : function (
dpoint 
)
{
},

/**
 * @method onEnter
 */
onEnter : function (
)
{
},

/**
 * @method getRotationQuat
 * @return {ca.Quaternion}
 */
getRotationQuat : function (
)
{
    return ca.Quaternion;
},

/**
 * @method setShaderProgram
 * @param {ca.GLProgram} arg0
 */
setShaderProgram : function (
glprogram 
)
{
},

/**
 * @method getZOrder
 * @return {int}
 */
getZOrder : function (
)
{
    return 0;
},

/**
 * @method getAnchorPointInPoints
 * @return {point_object}
 */
getAnchorPointInPoints : function (
)
{
    return ca.DPoint;
},

/**
 * @method runAction
 * @param {ca.Action} arg0
 * @return {ca.Action}
 */
runAction : function (
action 
)
{
    return ca.Action;
},

/**
 * @method transform
 * @param {ca.Mat4} arg0
 * @return {ca.Mat4}
 */
transform : function (
mat4 
)
{
    return ca.Mat4;
},

/**
 * @method getGLProgramState
 * @return {ca.GLProgramState}
 */
getGLProgramState : function (
)
{
    return ca.GLProgramState;
},

/**
 * @method stopAllActions
 */
stopAllActions : function (
)
{
},

/**
 * @method getSkewX
 * @return {float}
 */
getSkewX : function (
)
{
    return 0;
},

/**
 * @method getSkewY
 * @return {float}
 */
getSkewY : function (
)
{
    return 0;
},

/**
 * @method getDisplayedColor
 * @return {color4b_object}
 */
getDisplayedColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setRotationZ
 * @param {float} arg0
 */
setRotationZ : function (
float 
)
{
},

/**
 * @method getActionByTag
 * @param {int} arg0
 * @return {ca.Action}
 */
getActionByTag : function (
int 
)
{
    return ca.Action;
},

/**
 * @method setRotationX
 * @param {float} arg0
 */
setRotationX : function (
float 
)
{
},

/**
 * @method setRotationY
 * @param {float} arg0
 */
setRotationY : function (
float 
)
{
},

/**
 * @method setDisplayRange
 * @param {bool} arg0
 */
setDisplayRange : function (
bool 
)
{
},

/**
 * @method setAdditionalTransform
* @param {ca.AffineTransform|ca.Mat4} affinetransform
*/
setAdditionalTransform : function(
mat4 
)
{
},

/**
 * @method getParentToNodeAffineTransform
 * @return {ca.AffineTransform}
 */
getParentToNodeAffineTransform : function (
)
{
    return ca.AffineTransform;
},

/**
 * @method getOrderOfArrival
 * @return {unsigned int}
 */
getOrderOfArrival : function (
)
{
    return 0;
},

/**
 * @method boundingBox
 * @return {rect_object}
 */
boundingBox : function (
)
{
    return ca.DRect;
},

/**
 * @method setContentSize
 * @param {size_object} arg0
 */
setContentSize : function (
dsize 
)
{
},

/**
 * @method copy
 * @return {ca.CGNode}
 */
copy : function (
)
{
    return ca.CGNode;
},

/**
 * @method getPosition
 * @return {point_object}
 */
getPosition : function (
)
{
    return ca.DPoint;
},

/**
 * @method setColor
 * @param {color4b_object} arg0
 */
setColor : function (
cacolor4b 
)
{
},

/**
 * @method isRunning
 * @return {bool}
 */
isRunning : function (
)
{
    return false;
},

/**
 * @method getParent
 * @return {ca.CGNode}
 */
getParent : function (
)
{
    return ca.CGNode;
},

/**
 * @method getPositionZ
 * @return {float}
 */
getPositionZ : function (
)
{
    return 0;
},

/**
 * @method getPositionY
 * @return {float}
 */
getPositionY : function (
)
{
    return 0;
},

/**
 * @method getPositionX
 * @return {float}
 */
getPositionX : function (
)
{
    return 0;
},

/**
 * @method removeChildByTag
 * @param {int} arg0
 */
removeChildByTag : function (
int 
)
{
},

/**
 * @method getQuad
 * @return {ca._ccV3F_C4B_T2F_Quad}
 */
getQuad : function (
)
{
    return ca._ccV3F_C4B_T2F_Quad;
},

/**
 * @method visit
 * @param {ca.Renderer} arg0
 * @param {ca.Mat4} arg1
 * @param {unsigned int} arg2
 */
visit : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method updateDisplayedColor
 * @param {color4b_object} arg0
 */
updateDisplayedColor : function (
cacolor4b 
)
{
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method getParentToNodeTransform
 * @return {ca.Mat4}
 */
getParentToNodeTransform : function (
)
{
    return ca.Mat4;
},

/**
 * @method getDisplayedAlpha
 * @return {float}
 */
getDisplayedAlpha : function (
)
{
    return 0;
},

/**
 * @method _setZOrder
 * @param {int} arg0
 */
_setZOrder : function (
int 
)
{
},

/**
 * @method setScale
* @param {float|float} float
* @param {float} float
* @param {float} float
*/
setScale : function(
float,
float,
float 
)
{
},

/**
 * @method isDisplayRange
 * @return {bool}
 */
isDisplayRange : function (
)
{
    return false;
},

/**
 * @method setRotation3D
 * @param {point_object} arg0
 */
setRotation3D : function (
dpoint3d 
)
{
},

/**
 * @method getOnExitCallback
 * @return {function}
 */
getOnExitCallback : function (
)
{
    return std::function<void ()>;
},

/**
 * @method getChildByTag
 * @param {int} arg0
 * @return {ca.CGNode}
 */
getChildByTag : function (
int 
)
{
    return ca.CGNode;
},

/**
 * @method setOrderOfArrival
 * @param {unsigned int} arg0
 */
setOrderOfArrival : function (
int 
)
{
},

/**
 * @method getScaleZ
 * @return {float}
 */
getScaleZ : function (
)
{
    return 0;
},

/**
 * @method getScaleY
 * @return {float}
 */
getScaleY : function (
)
{
    return 0;
},

/**
 * @method getScaleX
 * @return {float}
 */
getScaleX : function (
)
{
    return 0;
},

/**
 * @method isVisitableByVisitingCamera
 * @return {bool}
 */
isVisitableByVisitingCamera : function (
)
{
    return false;
},

/**
 * @method setOpacityModifyRGB
 * @param {bool} arg0
 */
setOpacityModifyRGB : function (
bool 
)
{
},

/**
 * @method insertChild
 * @param {ca.CGNode} arg0
 * @param {int} arg1
 */
insertChild : function (
cgnode, 
int 
)
{
},

/**
 * @method getContentSize
 * @return {size_object}
 */
getContentSize : function (
)
{
    return ca.DSize;
},

/**
 * @method stopAllActionsByTag
 * @param {int} arg0
 */
stopAllActionsByTag : function (
int 
)
{
},

/**
 * @method setCAView
 * @param {ca.CAView} arg0
 */
setCAView : function (
caview 
)
{
},

/**
 * @method draw
 * @param {ca.Renderer} arg0
 * @param {ca.Mat4} arg1
 * @param {unsigned int} arg2
 */
draw : function (
renderer, 
mat4, 
int 
)
{
},

/**
 * @method getBlendFunc
 * @return {ca.BlendFunc}
 */
getBlendFunc : function (
)
{
    return ca.BlendFunc;
},

/**
 * @method getChildByTextTag
 * @param {String} arg0
 * @return {ca.CGNode}
 */
getChildByTextTag : function (
str 
)
{
    return ca.CGNode;
},

/**
 * @method removeFromParent
 */
removeFromParent : function (
)
{
},

/**
 * @method setPosition3D
 * @param {point_object} arg0
 */
setPosition3D : function (
dpoint3d 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method sortAllChildren
 */
sortAllChildren : function (
)
{
},

/**
 * @method convertToNodeSpace
 * @param {point_object} arg0
 * @return {point_object}
 */
convertToNodeSpace : function (
dpoint 
)
{
    return ca.DPoint;
},

/**
 * @method onExitTransitionDidStart
 */
onExitTransitionDidStart : function (
)
{
},

/**
 * @method getScale
 * @return {float}
 */
getScale : function (
)
{
    return 0;
},

/**
 * @method getNormalizedPosition
 * @return {point_object}
 */
getNormalizedPosition : function (
)
{
    return ca.DPoint;
},

/**
 * @method setBlendFunc
 * @param {ca.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method getColor
 * @return {color4b_object}
 */
getColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method setRotationQuat
 * @param {ca.Quaternion} arg0
 */
setRotationQuat : function (
quaternion 
)
{
},

/**
 * @method stopAction
 * @param {ca.Action} arg0
 */
stopAction : function (
action 
)
{
},

/**
 * @method create
 * @return {ca.CGNode}
 */
create : function (
)
{
    return ca.CGNode;
},

/**
 * @method CGNode
 * @constructor
 */
CGNode : function (
)
{
},

};

/**
 * @class CGSprite
 */
ca.CGSprite = {

/**
 * @method setSpriteFrame
 * @param {ca.CGSpriteFrame} arg0
 */
setSpriteFrame : function (
cgspriteframe 
)
{
},

/**
 * @method initWithImage
* @param {ca.CAImage|ca.CAImage|ca.CAImage} caimage
* @param {rect_object|rect_object} drect
* @param {bool} bool
* @return {bool|bool|bool}
*/
initWithImage : function(
caimage,
drect,
bool 
)
{
    return false;
},

/**
 * @method getBatchNode
 * @return {ca.CGSpriteBatchNode}
 */
getBatchNode : function (
)
{
    return ca.CGSpriteBatchNode;
},

/**
 * @method getOffsetPosition
 * @return {point_object}
 */
getOffsetPosition : function (
)
{
    return ca.DPoint;
},

/**
 * @method isFlipX
 * @return {bool}
 */
isFlipX : function (
)
{
    return false;
},

/**
 * @method isFlipY
 * @return {bool}
 */
isFlipY : function (
)
{
    return false;
},

/**
 * @method initWithSpriteFrameName
 * @param {String} arg0
 * @return {bool}
 */
initWithSpriteFrameName : function (
str 
)
{
    return false;
},

/**
 * @method isFrameDisplayed
 * @param {ca.CGSpriteFrame} arg0
 * @return {bool}
 */
isFrameDisplayed : function (
cgspriteframe 
)
{
    return false;
},

/**
 * @method getImageRect
 * @return {rect_object}
 */
getImageRect : function (
)
{
    return ca.DRect;
},

/**
 * @method getAtlasIndex
 * @return {unsigned int}
 */
getAtlasIndex : function (
)
{
    return 0;
},

/**
 * @method setBatchNode
 * @param {ca.CGSpriteBatchNode} arg0
 */
setBatchNode : function (
cgspritebatchnode 
)
{
},

/**
 * @method setDisplayFrameWithAnimationName
 * @param {String} arg0
 * @param {int} arg1
 */
setDisplayFrameWithAnimationName : function (
str, 
int 
)
{
},

/**
 * @method getImageAtlas
 * @return {ca.CAImageAtlas}
 */
getImageAtlas : function (
)
{
    return ca.CAImageAtlas;
},

/**
 * @method setFlipY
 * @param {bool} arg0
 */
setFlipY : function (
bool 
)
{
},

/**
 * @method setFlipX
 * @param {bool} arg0
 */
setFlipX : function (
bool 
)
{
},

/**
 * @method getSpriteFrame
 * @return {ca.CGSpriteFrame}
 */
getSpriteFrame : function (
)
{
    return ca.CGSpriteFrame;
},

/**
 * @method isDirty
 * @return {bool}
 */
isDirty : function (
)
{
    return false;
},

/**
 * @method setAtlasIndex
 * @param {int} arg0
 */
setAtlasIndex : function (
int 
)
{
},

/**
 * @method setDirty
 * @param {bool} arg0
 */
setDirty : function (
bool 
)
{
},

/**
 * @method setImageRect
* @param {rect_object|rect_object} drect
* @param {bool} bool
* @param {size_object} dsize
*/
setImageRect : function(
drect,
bool,
dsize 
)
{
},

/**
 * @method isTextureRectRotated
 * @return {bool}
 */
isTextureRectRotated : function (
)
{
    return false;
},

/**
 * @method setImageAtlas
 * @param {ca.CAImageAtlas} arg0
 */
setImageAtlas : function (
caimageatlas 
)
{
},

/**
 * @method initWithFile
* @param {String|String} str
* @param {rect_object} drect
* @return {bool|bool}
*/
initWithFile : function(
str,
drect 
)
{
    return false;
},

/**
 * @method setImage
 * @param {ca.CAImage} arg0
 */
setImage : function (
caimage 
)
{
},

/**
 * @method initWithSpriteFrame
 * @param {ca.CGSpriteFrame} arg0
 * @return {bool}
 */
initWithSpriteFrame : function (
cgspriteframe 
)
{
    return false;
},

/**
 * @method getQuad
 * @return {ca._ccV3F_C4B_T2F_Quad}
 */
getQuad : function (
)
{
    return ca._ccV3F_C4B_T2F_Quad;
},

/**
 * @method setVertexRect
 * @param {rect_object} arg0
 */
setVertexRect : function (
drect 
)
{
},

/**
 * @method getImage
 * @return {ca.CAImage}
 */
getImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method create
* @param {String|String} str
* @param {rect_object} drect
* @return {ca.CGSprite|ca.CGSprite|ca.CGSprite}
*/
create : function(
str,
drect 
)
{
    return ca.CGSprite;
},

/**
 * @method createWithImage
* @param {ca.CAImage|ca.CAImage} caimage
* @param {rect_object} drect
* @return {ca.CGSprite|ca.CGSprite}
*/
createWithImage : function(
caimage,
drect 
)
{
    return ca.CGSprite;
},

/**
 * @method createWithSpriteFrameName
 * @param {String} arg0
 * @return {ca.CGSprite}
 */
createWithSpriteFrameName : function (
str 
)
{
    return ca.CGSprite;
},

/**
 * @method createWithSpriteFrame
 * @param {ca.CGSpriteFrame} arg0
 * @return {ca.CGSprite}
 */
createWithSpriteFrame : function (
cgspriteframe 
)
{
    return ca.CGSprite;
},

/**
 * @method CGSprite
 * @constructor
 */
CGSprite : function (
)
{
},

};

/**
 * @class CGSpriteFrame
 */
ca.CGSpriteFrame = {

/**
 * @method setRotated
 * @param {bool} arg0
 */
setRotated : function (
bool 
)
{
},

/**
 * @method setAnchorPoint
 * @param {point_object} arg0
 */
setAnchorPoint : function (
dpoint 
)
{
},

/**
 * @method getOffset
 * @return {point_object}
 */
getOffset : function (
)
{
    return ca.DPoint;
},

/**
 * @method getOriginalSize
 * @return {size_object}
 */
getOriginalSize : function (
)
{
    return ca.DSize;
},

/**
 * @method getRect
 * @return {rect_object}
 */
getRect : function (
)
{
    return ca.DRect;
},

/**
 * @method clone
 * @return {ca.CGSpriteFrame}
 */
clone : function (
)
{
    return ca.CGSpriteFrame;
},

/**
 * @method setImage
 * @param {ca.CAImage} arg0
 */
setImage : function (
caimage 
)
{
},

/**
 * @method initWithImage
* @param {ca.CAImage|ca.CAImage} caimage
* @param {rect_object|rect_object} drect
* @param {bool} bool
* @param {point_object} dpoint
* @param {size_object} dsize
* @return {bool|bool}
*/
initWithImage : function(
caimage,
drect,
bool,
dpoint,
dsize 
)
{
    return false;
},

/**
 * @method getAnchorPoint
 * @return {point_object}
 */
getAnchorPoint : function (
)
{
    return ca.DPoint;
},

/**
 * @method setOriginalSize
 * @param {size_object} arg0
 */
setOriginalSize : function (
dsize 
)
{
},

/**
 * @method setOffset
 * @param {point_object} arg0
 */
setOffset : function (
dpoint 
)
{
},

/**
 * @method hasAnchorPoint
 * @return {bool}
 */
hasAnchorPoint : function (
)
{
    return false;
},

/**
 * @method isRotated
 * @return {bool}
 */
isRotated : function (
)
{
    return false;
},

/**
 * @method getImage
 * @return {ca.CAImage}
 */
getImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method setRect
 * @param {rect_object} arg0
 */
setRect : function (
drect 
)
{
},

/**
 * @method initWithImageFilename
* @param {String|String} str
* @param {rect_object|rect_object} drect
* @param {bool} bool
* @param {point_object} dpoint
* @param {size_object} dsize
* @return {bool|bool}
*/
initWithImageFilename : function(
str,
drect,
bool,
dpoint,
dsize 
)
{
    return false;
},

/**
 * @method create
* @param {String|String} str
* @param {rect_object|rect_object} drect
* @param {bool} bool
* @param {point_object} dpoint
* @param {size_object} dsize
* @return {ca.CGSpriteFrame|ca.CGSpriteFrame}
*/
create : function(
str,
drect,
bool,
dpoint,
dsize 
)
{
    return ca.CGSpriteFrame;
},

/**
 * @method createWithImage
* @param {ca.CAImage|ca.CAImage} caimage
* @param {rect_object|rect_object} drect
* @param {bool} bool
* @param {point_object} dpoint
* @param {size_object} dsize
* @return {ca.CGSpriteFrame|ca.CGSpriteFrame}
*/
createWithImage : function(
caimage,
drect,
bool,
dpoint,
dsize 
)
{
    return ca.CGSpriteFrame;
},

/**
 * @method CGSpriteFrame
 * @constructor
 */
CGSpriteFrame : function (
)
{
},

};

/**
 * @class CGSpriteFrameCache
 */
ca.CGSpriteFrameCache = {

/**
 * @method getSpriteFrameByName
 * @param {String} arg0
 * @return {ca.CGSpriteFrame}
 */
getSpriteFrameByName : function (
str 
)
{
    return ca.CGSpriteFrame;
},

/**
 * @method addSpriteFramesWithFile
* @param {String|String|String} str
* @param {String|ca.CAImage} str
*/
addSpriteFramesWithFile : function(
str,
caimage 
)
{
},

/**
 * @method addSpriteFrame
 * @param {ca.CGSpriteFrame} arg0
 * @param {String} arg1
 */
addSpriteFrame : function (
cgspriteframe, 
str 
)
{
},

/**
 * @method removeUnusedSpriteFrames
 */
removeUnusedSpriteFrames : function (
)
{
},

/**
 * @method removeSpriteFramesFromFile
 * @param {String} arg0
 */
removeSpriteFramesFromFile : function (
str 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method removeSpriteFrames
 */
removeSpriteFrames : function (
)
{
},

/**
 * @method removeSpriteFrameByName
 * @param {String} arg0
 */
removeSpriteFrameByName : function (
str 
)
{
},

/**
 * @method removeSpriteFramesFromImage
 * @param {ca.CAImage} arg0
 */
removeSpriteFramesFromImage : function (
caimage 
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {ca.CGSpriteFrameCache}
 */
getInstance : function (
)
{
    return ca.CGSpriteFrameCache;
},

/**
 * @method CGSpriteFrameCache
 * @constructor
 */
CGSpriteFrameCache : function (
)
{
},

};

/**
 * @class CGSpriteBatchNode
 */
ca.CGSpriteBatchNode = {

/**
 * @method setImageAtlas
 * @param {ca.CAImageAtlas} arg0
 */
setImageAtlas : function (
caimageatlas 
)
{
},

/**
 * @method reorderBatch
 * @param {bool} arg0
 */
reorderBatch : function (
bool 
)
{
},

/**
 * @method initWithFile
 * @param {String} arg0
 * @param {unsigned int} arg1
 * @return {bool}
 */
initWithFile : function (
str, 
int 
)
{
    return false;
},

/**
 * @method getImageAtlas
 * @return {ca.CAImageAtlas}
 */
getImageAtlas : function (
)
{
    return ca.CAImageAtlas;
},

/**
 * @method lowestAtlasIndexInChild
 * @param {ca.CGSprite} arg0
 * @return {int}
 */
lowestAtlasIndexInChild : function (
cgsprite 
)
{
    return 0;
},

/**
 * @method appendChild
 * @param {ca.CGSprite} arg0
 */
appendChild : function (
cgsprite 
)
{
},

/**
 * @method atlasIndexForChild
 * @param {ca.CGSprite} arg0
 * @param {int} arg1
 * @return {int}
 */
atlasIndexForChild : function (
cgsprite, 
int 
)
{
    return 0;
},

/**
 * @method increaseAtlasCapacity
 */
increaseAtlasCapacity : function (
)
{
},

/**
 * @method rebuildIndexInOrder
 * @param {ca.CGSprite} arg0
 * @param {int} arg1
 * @return {int}
 */
rebuildIndexInOrder : function (
cgsprite, 
int 
)
{
    return 0;
},

/**
 * @method initWithImage
 * @param {ca.CAImage} arg0
 * @param {unsigned int} arg1
 * @return {bool}
 */
initWithImage : function (
caimage, 
int 
)
{
    return false;
},

/**
 * @method getDescendants
 * @return {Array}
 */
getDescendants : function (
)
{
    return new Array();
},

/**
 * @method setImage
 * @param {ca.CAImage} arg0
 */
setImage : function (
caimage 
)
{
},

/**
 * @method getBlendFunc
 * @return {ca.BlendFunc}
 */
getBlendFunc : function (
)
{
    return ca.BlendFunc;
},

/**
 * @method highestAtlasIndexInChild
 * @param {ca.CGSprite} arg0
 * @return {int}
 */
highestAtlasIndexInChild : function (
cgsprite 
)
{
    return 0;
},

/**
 * @method getImage
 * @return {ca.CAImage}
 */
getImage : function (
)
{
    return ca.CAImage;
},

/**
 * @method removeSpriteFromAtlas
 * @param {ca.CGSprite} arg0
 */
removeSpriteFromAtlas : function (
cgsprite 
)
{
},

/**
 * @method setBlendFunc
 * @param {ca.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method create
* @param {String|String} str
* @param {unsigned int} int
* @return {ca.CGSpriteBatchNode|ca.CGSpriteBatchNode}
*/
create : function(
str,
int 
)
{
    return ca.CGSpriteBatchNode;
},

/**
 * @method createWithImage
* @param {ca.CAImage|ca.CAImage} caimage
* @param {unsigned int} int
* @return {ca.CGSpriteBatchNode|ca.CGSpriteBatchNode}
*/
createWithImage : function(
caimage,
int 
)
{
    return ca.CGSpriteBatchNode;
},

/**
 * @method CGSpriteBatchNode
 * @constructor
 */
CGSpriteBatchNode : function (
)
{
},

};

/**
 * @class CGProgressTimer
 */
ca.CGProgressTimer = {

/**
 * @method setReverseProgress
 * @param {bool} arg0
 */
setReverseProgress : function (
bool 
)
{
},

/**
 * @method isReverseDirection
 * @return {bool}
 */
isReverseDirection : function (
)
{
    return false;
},

/**
 * @method setBarChangeRate
 * @param {point_object} arg0
 */
setBarChangeRate : function (
dpoint 
)
{
},

/**
 * @method setAnchorPoint
 * @param {point_object} arg0
 */
setAnchorPoint : function (
dpoint 
)
{
},

/**
 * @method getPercentage
 * @return {float}
 */
getPercentage : function (
)
{
    return 0;
},

/**
 * @method setSprite
 * @param {ca.CGSprite} arg0
 */
setSprite : function (
cgsprite 
)
{
},

/**
 * @method getType
 * @return {ca.CGProgressTimer::Type}
 */
getType : function (
)
{
    return 0;
},

/**
 * @method getSprite
 * @return {ca.CGSprite}
 */
getSprite : function (
)
{
    return ca.CGSprite;
},

/**
 * @method setMidpoint
 * @param {point_object} arg0
 */
setMidpoint : function (
dpoint 
)
{
},

/**
 * @method getMidpoint
 * @return {point_object}
 */
getMidpoint : function (
)
{
    return ca.DPoint;
},

/**
 * @method getColor
 * @return {color4b_object}
 */
getColor : function (
)
{
    return ca.CAColor4B;
},

/**
 * @method getAlpha
 * @return {float}
 */
getAlpha : function (
)
{
    return 0;
},

/**
 * @method getBarChangeRate
 * @return {point_object}
 */
getBarChangeRate : function (
)
{
    return ca.DPoint;
},

/**
 * @method setReverseDirection
 * @param {bool} arg0
 */
setReverseDirection : function (
bool 
)
{
},

/**
 * @method initWithSprite
 * @param {ca.CGSprite} arg0
 * @return {bool}
 */
initWithSprite : function (
cgsprite 
)
{
    return false;
},

/**
 * @method setPercentage
 * @param {float} arg0
 */
setPercentage : function (
float 
)
{
},

/**
 * @method setType
 * @param {ca.CGProgressTimer::Type} arg0
 */
setType : function (
type 
)
{
},

/**
 * @method create
 * @param {ca.CGSprite} arg0
 * @return {ca.CGProgressTimer}
 */
create : function (
cgsprite 
)
{
    return ca.CGProgressTimer;
},

/**
 * @method CGProgressTimer
 * @constructor
 */
CGProgressTimer : function (
)
{
},

};

/**
 * @class AnimationCache
 */
ca.AnimationCache = {

/**
 * @method getAnimation
 * @param {String} arg0
 * @return {ca.Animation}
 */
getAnimation : function (
str 
)
{
    return ca.Animation;
},

/**
 * @method addAnimation
 * @param {ca.Animation} arg0
 * @param {String} arg1
 */
addAnimation : function (
animation, 
str 
)
{
},

/**
 * @method addAnimationsWithFile
 * @param {String} arg0
 */
addAnimationsWithFile : function (
str 
)
{
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method removeAnimation
 * @param {String} arg0
 */
removeAnimation : function (
str 
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {ca.AnimationCache}
 */
getInstance : function (
)
{
    return ca.AnimationCache;
},

/**
 * @method AnimationCache
 * @constructor
 */
AnimationCache : function (
)
{
},

};

/**
 * @class Action
 */
ca.Action = {

/**
 * @method startWithTarget
 * @param {ca.CGNode} arg0
 */
startWithTarget : function (
cgnode 
)
{
},

/**
 * @method description
 * @return {String}
 */
description : function (
)
{
    return ;
},

/**
 * @method setOriginalTarget
 * @param {ca.CGNode} arg0
 */
setOriginalTarget : function (
cgnode 
)
{
},

/**
 * @method clone
 * @return {ca.Action}
 */
clone : function (
)
{
    return ca.Action;
},

/**
 * @method getOriginalTarget
 * @return {ca.CGNode}
 */
getOriginalTarget : function (
)
{
    return ca.CGNode;
},

/**
 * @method stop
 */
stop : function (
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method getTarget
 * @return {ca.CGNode}
 */
getTarget : function (
)
{
    return ca.CGNode;
},

/**
 * @method getFlags
 * @return {unsigned int}
 */
getFlags : function (
)
{
    return 0;
},

/**
 * @method step
 * @param {float} arg0
 */
step : function (
float 
)
{
},

/**
 * @method setTag
 * @param {int} arg0
 */
setTag : function (
int 
)
{
},

/**
 * @method setFlags
 * @param {unsigned int} arg0
 */
setFlags : function (
int 
)
{
},

/**
 * @method getTag
 * @return {int}
 */
getTag : function (
)
{
    return 0;
},

/**
 * @method setTarget
 * @param {ca.CGNode} arg0
 */
setTarget : function (
cgnode 
)
{
},

/**
 * @method isDone
 * @return {bool}
 */
isDone : function (
)
{
    return false;
},

/**
 * @method reverse
 * @return {ca.Action}
 */
reverse : function (
)
{
    return ca.Action;
},

};

/**
 * @class FiniteTimeAction
 */
ca.FiniteTimeAction = {

/**
 * @method setDuration
 * @param {float} arg0
 */
setDuration : function (
float 
)
{
},

/**
 * @method getDuration
 * @return {float}
 */
getDuration : function (
)
{
    return 0;
},

};

/**
 * @class ActionInterval
 */
ca.ActionInterval = {

/**
 * @method getAmplitudeRate
 * @return {float}
 */
getAmplitudeRate : function (
)
{
    return 0;
},

/**
 * @method initWithDuration
 * @param {float} arg0
 * @return {bool}
 */
initWithDuration : function (
float 
)
{
    return false;
},

/**
 * @method setAmplitudeRate
 * @param {float} arg0
 */
setAmplitudeRate : function (
float 
)
{
},

/**
 * @method getElapsed
 * @return {float}
 */
getElapsed : function (
)
{
    return 0;
},

};

/**
 * @class Sequence
 */
ca.Sequence = {

/**
 * @method init
 * @param {Array} arg0
 * @return {bool}
 */
init : function (
array 
)
{
    return false;
},

/**
 * @method initWithTwoActions
 * @param {ca.FiniteTimeAction} arg0
 * @param {ca.FiniteTimeAction} arg1
 * @return {bool}
 */
initWithTwoActions : function (
finitetimeaction, 
finitetimeaction 
)
{
    return false;
},

/**
 * @method create
 * @param {Array} arg0
 * @return {ca.Sequence}
 */
create : function (
array 
)
{
    return ca.Sequence;
},

/**
 * @method createWithTwoActions
 * @param {ca.FiniteTimeAction} arg0
 * @param {ca.FiniteTimeAction} arg1
 * @return {ca.Sequence}
 */
createWithTwoActions : function (
finitetimeaction, 
finitetimeaction 
)
{
    return ca.Sequence;
},

/**
 * @method Sequence
 * @constructor
 */
Sequence : function (
)
{
},

};

/**
 * @class Repeat
 */
ca.Repeat = {

/**
 * @method setInnerAction
 * @param {ca.FiniteTimeAction} arg0
 */
setInnerAction : function (
finitetimeaction 
)
{
},

/**
 * @method initWithAction
 * @param {ca.FiniteTimeAction} arg0
 * @param {unsigned int} arg1
 * @return {bool}
 */
initWithAction : function (
finitetimeaction, 
int 
)
{
    return false;
},

/**
 * @method getInnerAction
 * @return {ca.FiniteTimeAction}
 */
getInnerAction : function (
)
{
    return ca.FiniteTimeAction;
},

/**
 * @method create
 * @param {ca.FiniteTimeAction} arg0
 * @param {unsigned int} arg1
 * @return {ca.Repeat}
 */
create : function (
finitetimeaction, 
int 
)
{
    return ca.Repeat;
},

/**
 * @method Repeat
 * @constructor
 */
Repeat : function (
)
{
},

};

/**
 * @class RepeatForever
 */
ca.RepeatForever = {

/**
 * @method setInnerAction
 * @param {ca.ActionInterval} arg0
 */
setInnerAction : function (
actioninterval 
)
{
},

/**
 * @method initWithAction
 * @param {ca.ActionInterval} arg0
 * @return {bool}
 */
initWithAction : function (
actioninterval 
)
{
    return false;
},

/**
 * @method getInnerAction
 * @return {ca.ActionInterval}
 */
getInnerAction : function (
)
{
    return ca.ActionInterval;
},

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.RepeatForever}
 */
create : function (
actioninterval 
)
{
    return ca.RepeatForever;
},

/**
 * @method RepeatForever
 * @constructor
 */
RepeatForever : function (
)
{
},

};

/**
 * @class Spawn
 */
ca.Spawn = {

/**
 * @method init
 * @param {Array} arg0
 * @return {bool}
 */
init : function (
array 
)
{
    return false;
},

/**
 * @method initWithTwoActions
 * @param {ca.FiniteTimeAction} arg0
 * @param {ca.FiniteTimeAction} arg1
 * @return {bool}
 */
initWithTwoActions : function (
finitetimeaction, 
finitetimeaction 
)
{
    return false;
},

/**
 * @method create
 * @param {Array} arg0
 * @return {ca.Spawn}
 */
create : function (
array 
)
{
    return ca.Spawn;
},

/**
 * @method createWithTwoActions
 * @param {ca.FiniteTimeAction} arg0
 * @param {ca.FiniteTimeAction} arg1
 * @return {ca.Spawn}
 */
createWithTwoActions : function (
finitetimeaction, 
finitetimeaction 
)
{
    return ca.Spawn;
},

/**
 * @method Spawn
 * @constructor
 */
Spawn : function (
)
{
},

};

/**
 * @class RotateTo
 */
ca.RotateTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {point_object} arg1
 * @return {bool}
 */
initWithDuration : function (
float, 
dpoint3d 
)
{
    return false;
},

/**
 * @method initWithDurationZ
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDurationZ : function (
float, 
float 
)
{
    return false;
},

/**
 * @method initWithDurationY
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDurationY : function (
float, 
float 
)
{
    return false;
},

/**
 * @method initWithDurationX
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDurationX : function (
float, 
float 
)
{
    return false;
},

/**
 * @method createZ
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.RotateTo}
 */
createZ : function (
float, 
float 
)
{
    return ca.RotateTo;
},

/**
 * @method createY
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.RotateTo}
 */
createY : function (
float, 
float 
)
{
    return ca.RotateTo;
},

/**
 * @method createX
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.RotateTo}
 */
createX : function (
float, 
float 
)
{
    return ca.RotateTo;
},

/**
 * @method create
 * @param {float} arg0
 * @param {point_object} arg1
 * @return {ca.RotateTo}
 */
create : function (
float, 
dpoint3d 
)
{
    return ca.RotateTo;
},

/**
 * @method RotateTo
 * @constructor
 */
RotateTo : function (
)
{
},

};

/**
 * @class RotateBy
 */
ca.RotateBy = {

/**
 * @method initWithDurationZ
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDurationZ : function (
float, 
float 
)
{
    return false;
},

/**
 * @method initWithDurationY
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDurationY : function (
float, 
float 
)
{
    return false;
},

/**
 * @method initWithDurationX
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDurationX : function (
float, 
float 
)
{
    return false;
},

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {point_object} arg1
 * @return {bool}
 */
initWithDuration : function (
float, 
dpoint3d 
)
{
    return false;
},

/**
 * @method createZ
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.RotateBy}
 */
createZ : function (
float, 
float 
)
{
    return ca.RotateBy;
},

/**
 * @method createY
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.RotateBy}
 */
createY : function (
float, 
float 
)
{
    return ca.RotateBy;
},

/**
 * @method createX
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.RotateBy}
 */
createX : function (
float, 
float 
)
{
    return ca.RotateBy;
},

/**
 * @method create
 * @param {float} arg0
 * @param {point_object} arg1
 * @return {ca.RotateBy}
 */
create : function (
float, 
dpoint3d 
)
{
    return ca.RotateBy;
},

/**
 * @method RotateBy
 * @constructor
 */
RotateBy : function (
)
{
},

};

/**
 * @class MoveBy
 */
ca.MoveBy = {

/**
 * @method initWithDuration
* @param {float|float} float
* @param {point_object|point_object} dpoint3d
* @return {bool|bool}
*/
initWithDuration : function(
float,
dpoint 
)
{
    return false;
},

/**
 * @method create
* @param {float|float} float
* @param {point_object|point_object} dpoint3d
* @return {ca.MoveBy|ca.MoveBy}
*/
create : function(
float,
dpoint 
)
{
    return ca.MoveBy;
},

/**
 * @method MoveBy
 * @constructor
 */
MoveBy : function (
)
{
},

};

/**
 * @class MoveTo
 */
ca.MoveTo = {

/**
 * @method initWithDuration
* @param {float|float} float
* @param {point_object|point_object} dpoint3d
* @return {bool|bool}
*/
initWithDuration : function(
float,
dpoint 
)
{
    return false;
},

/**
 * @method create
* @param {float|float} float
* @param {point_object|point_object} dpoint3d
* @return {ca.MoveTo|ca.MoveTo}
*/
create : function(
float,
dpoint 
)
{
    return ca.MoveTo;
},

/**
 * @method MoveTo
 * @constructor
 */
MoveTo : function (
)
{
},

};

/**
 * @class SkewTo
 */
ca.SkewTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {bool}
 */
initWithDuration : function (
float, 
float, 
float 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {ca.SkewTo}
 */
create : function (
float, 
float, 
float 
)
{
    return ca.SkewTo;
},

/**
 * @method SkewTo
 * @constructor
 */
SkewTo : function (
)
{
},

};

/**
 * @class SkewBy
 */
ca.SkewBy = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {bool}
 */
initWithDuration : function (
float, 
float, 
float 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @return {ca.SkewBy}
 */
create : function (
float, 
float, 
float 
)
{
    return ca.SkewBy;
},

/**
 * @method SkewBy
 * @constructor
 */
SkewBy : function (
)
{
},

};

/**
 * @class JumpBy
 */
ca.JumpBy = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {point_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
dpoint, 
float, 
int 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {point_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {ca.JumpBy}
 */
create : function (
float, 
dpoint, 
float, 
int 
)
{
    return ca.JumpBy;
},

/**
 * @method JumpBy
 * @constructor
 */
JumpBy : function (
)
{
},

};

/**
 * @class JumpTo
 */
ca.JumpTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {point_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
dpoint, 
float, 
int 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {point_object} arg1
 * @param {float} arg2
 * @param {int} arg3
 * @return {ca.JumpTo}
 */
create : function (
float, 
dpoint, 
float, 
int 
)
{
    return ca.JumpTo;
},

/**
 * @method JumpTo
 * @constructor
 */
JumpTo : function (
)
{
},

};

/**
 * @class BezierBy
 */
ca.BezierBy = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {ca._ccBezierConfig} arg1
 * @return {bool}
 */
initWithDuration : function (
float, 
_ccbezierconfig 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {ca._ccBezierConfig} arg1
 * @return {ca.BezierBy}
 */
create : function (
float, 
_ccbezierconfig 
)
{
    return ca.BezierBy;
},

/**
 * @method BezierBy
 * @constructor
 */
BezierBy : function (
)
{
},

};

/**
 * @class BezierTo
 */
ca.BezierTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {ca._ccBezierConfig} arg1
 * @return {bool}
 */
initWithDuration : function (
float, 
_ccbezierconfig 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {ca._ccBezierConfig} arg1
 * @return {ca.BezierTo}
 */
create : function (
float, 
_ccbezierconfig 
)
{
    return ca.BezierTo;
},

/**
 * @method BezierTo
 * @constructor
 */
BezierTo : function (
)
{
},

};

/**
 * @class ScaleTo
 */
ca.ScaleTo = {

/**
 * @method initWithDuration
* @param {float|float|float} float
* @param {float|float|float} float
* @param {float|float} float
* @param {float} float
* @return {bool|bool|bool}
*/
initWithDuration : function(
float,
float,
float,
float 
)
{
    return false;
},

/**
 * @method create
* @param {float|float|float} float
* @param {float|float|float} float
* @param {float|float} float
* @param {float} float
* @return {ca.ScaleTo|ca.ScaleTo|ca.ScaleTo}
*/
create : function(
float,
float,
float,
float 
)
{
    return ca.ScaleTo;
},

/**
 * @method ScaleTo
 * @constructor
 */
ScaleTo : function (
)
{
},

};

/**
 * @class ScaleBy
 */
ca.ScaleBy = {

/**
 * @method create
* @param {float|float|float} float
* @param {float|float|float} float
* @param {float|float} float
* @param {float} float
* @return {ca.ScaleBy|ca.ScaleBy|ca.ScaleBy}
*/
create : function(
float,
float,
float,
float 
)
{
    return ca.ScaleBy;
},

/**
 * @method ScaleBy
 * @constructor
 */
ScaleBy : function (
)
{
},

};

/**
 * @class Blink
 */
ca.Blink = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {int} arg1
 * @return {bool}
 */
initWithDuration : function (
float, 
int 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {int} arg1
 * @return {ca.Blink}
 */
create : function (
float, 
int 
)
{
    return ca.Blink;
},

/**
 * @method Blink
 * @constructor
 */
Blink : function (
)
{
},

};

/**
 * @class FadeTo
 */
ca.FadeTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithDuration : function (
float, 
float 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @return {ca.FadeTo}
 */
create : function (
float, 
float 
)
{
    return ca.FadeTo;
},

/**
 * @method FadeTo
 * @constructor
 */
FadeTo : function (
)
{
},

};

/**
 * @class FadeIn
 */
ca.FadeIn = {

/**
 * @method setReverseAction
 * @param {ca.FadeTo} arg0
 */
setReverseAction : function (
fadeto 
)
{
},

/**
 * @method create
 * @param {float} arg0
 * @return {ca.FadeIn}
 */
create : function (
float 
)
{
    return ca.FadeIn;
},

/**
 * @method FadeIn
 * @constructor
 */
FadeIn : function (
)
{
},

};

/**
 * @class FadeOut
 */
ca.FadeOut = {

/**
 * @method setReverseAction
 * @param {ca.FadeTo} arg0
 */
setReverseAction : function (
fadeto 
)
{
},

/**
 * @method create
 * @param {float} arg0
 * @return {ca.FadeOut}
 */
create : function (
float 
)
{
    return ca.FadeOut;
},

/**
 * @method FadeOut
 * @constructor
 */
FadeOut : function (
)
{
},

};

/**
 * @class TintTo
 */
ca.TintTo = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {unsigned char} arg1
 * @param {unsigned char} arg2
 * @param {unsigned char} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
char, 
char, 
char 
)
{
    return false;
},

/**
 * @method create
* @param {float|float} float
* @param {color4b_object|unsigned char} cacolor4b
* @param {unsigned char} char
* @param {unsigned char} char
* @return {ca.TintTo|ca.TintTo}
*/
create : function(
float,
char,
char,
char 
)
{
    return ca.TintTo;
},

/**
 * @method TintTo
 * @constructor
 */
TintTo : function (
)
{
},

};

/**
 * @class TintBy
 */
ca.TintBy = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {short} arg1
 * @param {short} arg2
 * @param {short} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
short, 
short, 
short 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {short} arg1
 * @param {short} arg2
 * @param {short} arg3
 * @return {ca.TintBy}
 */
create : function (
float, 
short, 
short, 
short 
)
{
    return ca.TintBy;
},

/**
 * @method TintBy
 * @constructor
 */
TintBy : function (
)
{
},

};

/**
 * @class DelayTime
 */
ca.DelayTime = {

/**
 * @method create
 * @param {float} arg0
 * @return {ca.DelayTime}
 */
create : function (
float 
)
{
    return ca.DelayTime;
},

/**
 * @method DelayTime
 * @constructor
 */
DelayTime : function (
)
{
},

};

/**
 * @class ReverseTime
 */
ca.ReverseTime = {

/**
 * @method initWithAction
 * @param {ca.FiniteTimeAction} arg0
 * @return {bool}
 */
initWithAction : function (
finitetimeaction 
)
{
    return false;
},

/**
 * @method create
 * @param {ca.FiniteTimeAction} arg0
 * @return {ca.ReverseTime}
 */
create : function (
finitetimeaction 
)
{
    return ca.ReverseTime;
},

/**
 * @method ReverseTime
 * @constructor
 */
ReverseTime : function (
)
{
},

};

/**
 * @class Animate
 */
ca.Animate = {

/**
 * @method initWithAnimation
 * @param {ca.Animation} arg0
 * @return {bool}
 */
initWithAnimation : function (
animation 
)
{
    return false;
},

/**
 * @method getAnimation
* @return {ca.Animation|ca.Animation}
*/
getAnimation : function(
)
{
    return ca.Animation;
},

/**
 * @method getCurrentFrameIndex
 * @return {int}
 */
getCurrentFrameIndex : function (
)
{
    return 0;
},

/**
 * @method setAnimation
 * @param {ca.Animation} arg0
 */
setAnimation : function (
animation 
)
{
},

/**
 * @method create
 * @param {ca.Animation} arg0
 * @return {ca.Animate}
 */
create : function (
animation 
)
{
    return ca.Animate;
},

/**
 * @method Animate
 * @constructor
 */
Animate : function (
)
{
},

};

/**
 * @class TargetedAction
 */
ca.TargetedAction = {

/**
 * @method getForcedTarget
* @return {ca.CGNode|ca.CGNode}
*/
getForcedTarget : function(
)
{
    return ca.CGNode;
},

/**
 * @method initWithTarget
 * @param {ca.CGNode} arg0
 * @param {ca.FiniteTimeAction} arg1
 * @return {bool}
 */
initWithTarget : function (
cgnode, 
finitetimeaction 
)
{
    return false;
},

/**
 * @method setForcedTarget
 * @param {ca.CGNode} arg0
 */
setForcedTarget : function (
cgnode 
)
{
},

/**
 * @method create
 * @param {ca.CGNode} arg0
 * @param {ca.FiniteTimeAction} arg1
 * @return {ca.TargetedAction}
 */
create : function (
cgnode, 
finitetimeaction 
)
{
    return ca.TargetedAction;
},

/**
 * @method TargetedAction
 * @constructor
 */
TargetedAction : function (
)
{
},

};

/**
 * @class ActionFloat
 */
ca.ActionFloat = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {function} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
float, 
float, 
func 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {function} arg3
 * @return {ca.ActionFloat}
 */
create : function (
float, 
float, 
float, 
func 
)
{
    return ca.ActionFloat;
},

/**
 * @method ActionFloat
 * @constructor
 */
ActionFloat : function (
)
{
},

};

/**
 * @class ActionCamera
 */
ca.ActionCamera = {

/**
 * @method setEye
* @param {float|point_object} float
* @param {float} float
* @param {float} float
*/
setEye : function(
float,
float,
float 
)
{
},

/**
 * @method getEye
 * @return {point_object}
 */
getEye : function (
)
{
    return ca.DPoint3D;
},

/**
 * @method setUp
 * @param {point_object} arg0
 */
setUp : function (
dpoint3d 
)
{
},

/**
 * @method getCenter
 * @return {point_object}
 */
getCenter : function (
)
{
    return ca.DPoint3D;
},

/**
 * @method setCenter
 * @param {point_object} arg0
 */
setCenter : function (
dpoint3d 
)
{
},

/**
 * @method getUp
 * @return {point_object}
 */
getUp : function (
)
{
    return ca.DPoint3D;
},

/**
 * @method ActionCamera
 * @constructor
 */
ActionCamera : function (
)
{
},

};

/**
 * @class ActionEase
 */
ca.ActionEase = {

/**
 * @method initWithAction
 * @param {ca.ActionInterval} arg0
 * @return {bool}
 */
initWithAction : function (
actioninterval 
)
{
    return false;
},

/**
 * @method getInnerAction
 * @return {ca.ActionInterval}
 */
getInnerAction : function (
)
{
    return ca.ActionInterval;
},

/**
 * @method ActionEase
 * @constructor
 */
ActionEase : function (
)
{
},

};

/**
 * @class EaseRateAction
 */
ca.EaseRateAction = {

/**
 * @method setRate
 * @param {float} arg0
 */
setRate : function (
float 
)
{
},

/**
 * @method initWithAction
 * @param {ca.ActionInterval} arg0
 * @param {float} arg1
 * @return {bool}
 */
initWithAction : function (
actioninterval, 
float 
)
{
    return false;
},

/**
 * @method getRate
 * @return {float}
 */
getRate : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @param {float} arg1
 * @return {ca.EaseRateAction}
 */
create : function (
actioninterval, 
float 
)
{
    return ca.EaseRateAction;
},

/**
 * @method EaseRateAction
 * @constructor
 */
EaseRateAction : function (
)
{
},

};

/**
 * @class EaseBezierAction
 */
ca.EaseBezierAction = {

/**
 * @method setBezierParamer
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 * @param {float} arg3
 */
setBezierParamer : function (
float, 
float, 
float, 
float 
)
{
},

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseBezierAction}
 */
create : function (
actioninterval 
)
{
    return ca.EaseBezierAction;
},

/**
 * @method EaseBezierAction
 * @constructor
 */
EaseBezierAction : function (
)
{
},

};

/**
 * @class EaseQuadraticActionIn
 */
ca.EaseQuadraticActionIn = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuadraticActionIn}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuadraticActionIn;
},

/**
 * @method EaseQuadraticActionIn
 * @constructor
 */
EaseQuadraticActionIn : function (
)
{
},

};

/**
 * @class EaseQuadraticActionOut
 */
ca.EaseQuadraticActionOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuadraticActionOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuadraticActionOut;
},

/**
 * @method EaseQuadraticActionOut
 * @constructor
 */
EaseQuadraticActionOut : function (
)
{
},

};

/**
 * @class EaseQuadraticActionInOut
 */
ca.EaseQuadraticActionInOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuadraticActionInOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuadraticActionInOut;
},

/**
 * @method EaseQuadraticActionInOut
 * @constructor
 */
EaseQuadraticActionInOut : function (
)
{
},

};

/**
 * @class EaseQuarticActionIn
 */
ca.EaseQuarticActionIn = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuarticActionIn}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuarticActionIn;
},

/**
 * @method EaseQuarticActionIn
 * @constructor
 */
EaseQuarticActionIn : function (
)
{
},

};

/**
 * @class EaseQuarticActionOut
 */
ca.EaseQuarticActionOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuarticActionOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuarticActionOut;
},

/**
 * @method EaseQuarticActionOut
 * @constructor
 */
EaseQuarticActionOut : function (
)
{
},

};

/**
 * @class EaseQuarticActionInOut
 */
ca.EaseQuarticActionInOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuarticActionInOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuarticActionInOut;
},

/**
 * @method EaseQuarticActionInOut
 * @constructor
 */
EaseQuarticActionInOut : function (
)
{
},

};

/**
 * @class EaseQuinticActionIn
 */
ca.EaseQuinticActionIn = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuinticActionIn}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuinticActionIn;
},

/**
 * @method EaseQuinticActionIn
 * @constructor
 */
EaseQuinticActionIn : function (
)
{
},

};

/**
 * @class EaseQuinticActionOut
 */
ca.EaseQuinticActionOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuinticActionOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuinticActionOut;
},

/**
 * @method EaseQuinticActionOut
 * @constructor
 */
EaseQuinticActionOut : function (
)
{
},

};

/**
 * @class EaseQuinticActionInOut
 */
ca.EaseQuinticActionInOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseQuinticActionInOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseQuinticActionInOut;
},

/**
 * @method EaseQuinticActionInOut
 * @constructor
 */
EaseQuinticActionInOut : function (
)
{
},

};

/**
 * @class EaseCircleActionIn
 */
ca.EaseCircleActionIn = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseCircleActionIn}
 */
create : function (
actioninterval 
)
{
    return ca.EaseCircleActionIn;
},

/**
 * @method EaseCircleActionIn
 * @constructor
 */
EaseCircleActionIn : function (
)
{
},

};

/**
 * @class EaseCircleActionOut
 */
ca.EaseCircleActionOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseCircleActionOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseCircleActionOut;
},

/**
 * @method EaseCircleActionOut
 * @constructor
 */
EaseCircleActionOut : function (
)
{
},

};

/**
 * @class EaseCircleActionInOut
 */
ca.EaseCircleActionInOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseCircleActionInOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseCircleActionInOut;
},

/**
 * @method EaseCircleActionInOut
 * @constructor
 */
EaseCircleActionInOut : function (
)
{
},

};

/**
 * @class EaseCubicActionIn
 */
ca.EaseCubicActionIn = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseCubicActionIn}
 */
create : function (
actioninterval 
)
{
    return ca.EaseCubicActionIn;
},

/**
 * @method EaseCubicActionIn
 * @constructor
 */
EaseCubicActionIn : function (
)
{
},

};

/**
 * @class EaseCubicActionOut
 */
ca.EaseCubicActionOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseCubicActionOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseCubicActionOut;
},

/**
 * @method EaseCubicActionOut
 * @constructor
 */
EaseCubicActionOut : function (
)
{
},

};

/**
 * @class EaseCubicActionInOut
 */
ca.EaseCubicActionInOut = {

/**
 * @method create
 * @param {ca.ActionInterval} arg0
 * @return {ca.EaseCubicActionInOut}
 */
create : function (
actioninterval 
)
{
    return ca.EaseCubicActionInOut;
},

/**
 * @method EaseCubicActionInOut
 * @constructor
 */
EaseCubicActionInOut : function (
)
{
},

};

/**
 * @class ActionTween
 */
ca.ActionTween = {

/**
 * @method initWithDuration
 * @param {float} arg0
 * @param {String} arg1
 * @param {float} arg2
 * @param {float} arg3
 * @return {bool}
 */
initWithDuration : function (
float, 
str, 
float, 
float 
)
{
    return false;
},

/**
 * @method create
 * @param {float} arg0
 * @param {String} arg1
 * @param {float} arg2
 * @param {float} arg3
 * @return {ca.ActionTween}
 */
create : function (
float, 
str, 
float, 
float 
)
{
    return ca.ActionTween;
},

};

/**
 * @class ActionInstant
 */
ca.ActionInstant = {

};

/**
 * @class ActionManager
 */
ca.ActionManager = {

/**
 * @method getActionByTag
 * @param {int} arg0
 * @param {ca.CGNode} arg1
 * @return {ca.Action}
 */
getActionByTag : function (
int, 
cgnode 
)
{
    return ca.Action;
},

/**
 * @method removeActionByTag
 * @param {int} arg0
 * @param {ca.CGNode} arg1
 */
removeActionByTag : function (
int, 
cgnode 
)
{
},

/**
 * @method removeActionsByFlags
 * @param {unsigned int} arg0
 * @param {ca.CGNode} arg1
 */
removeActionsByFlags : function (
int, 
cgnode 
)
{
},

/**
 * @method removeAllActions
 */
removeAllActions : function (
)
{
},

/**
 * @method addAction
 * @param {ca.Action} arg0
 * @param {ca.CGNode} arg1
 * @param {bool} arg2
 */
addAction : function (
action, 
cgnode, 
bool 
)
{
},

/**
 * @method resumeTarget
 * @param {ca.CGNode} arg0
 */
resumeTarget : function (
cgnode 
)
{
},

/**
 * @method update
 * @param {float} arg0
 */
update : function (
float 
)
{
},

/**
 * @method pauseTarget
 * @param {ca.CGNode} arg0
 */
pauseTarget : function (
cgnode 
)
{
},

/**
 * @method getNumberOfRunningActionsInTarget
 * @param {ca.CGNode} arg0
 * @return {int}
 */
getNumberOfRunningActionsInTarget : function (
cgnode 
)
{
    return 0;
},

/**
 * @method removeAllActionsFromTarget
 * @param {ca.CGNode} arg0
 */
removeAllActionsFromTarget : function (
cgnode 
)
{
},

/**
 * @method resumeTargets
 * @param {Array} arg0
 */
resumeTargets : function (
array 
)
{
},

/**
 * @method removeAction
 * @param {ca.Action} arg0
 */
removeAction : function (
action 
)
{
},

/**
 * @method removeAllActionsByTag
 * @param {int} arg0
 * @param {ca.CGNode} arg1
 */
removeAllActionsByTag : function (
int, 
cgnode 
)
{
},

/**
 * @method pauseAllRunningActions
 * @return {Array}
 */
pauseAllRunningActions : function (
)
{
    return new Array();
},

/**
 * @method ActionManager
 * @constructor
 */
ActionManager : function (
)
{
},

};

/**
 * @class SimpleAudioEngine
 */
ca.SimpleAudioEngine = {

/**
 * @method stopAllEffects
 */
stopAllEffects : function (
)
{
},

/**
 * @method getEffectsVolume
 * @return {float}
 */
getEffectsVolume : function (
)
{
    return 0;
},

/**
 * @method stopEffect
 * @param {unsigned int} arg0
 */
stopEffect : function (
int 
)
{
},

/**
 * @method getBackgroundMusicVolume
 * @return {float}
 */
getBackgroundMusicVolume : function (
)
{
    return 0;
},

/**
 * @method willPlayBackgroundMusic
 * @return {bool}
 */
willPlayBackgroundMusic : function (
)
{
    return false;
},

/**
 * @method setBackgroundMusicVolume
 * @param {float} arg0
 */
setBackgroundMusicVolume : function (
float 
)
{
},

/**
 * @method stopBackgroundMusic
* @param {bool} bool
*/
stopBackgroundMusic : function(
bool 
)
{
},

/**
 * @method pauseBackgroundMusic
 */
pauseBackgroundMusic : function (
)
{
},

/**
 * @method isBackgroundMusicPlaying
 * @return {bool}
 */
isBackgroundMusicPlaying : function (
)
{
    return false;
},

/**
 * @method resumeAllEffects
 */
resumeAllEffects : function (
)
{
},

/**
 * @method pauseAllEffects
 */
pauseAllEffects : function (
)
{
},

/**
 * @method preloadBackgroundMusic
 * @param {char} arg0
 */
preloadBackgroundMusic : function (
char 
)
{
},

/**
 * @method playBackgroundMusic
* @param {char|char} char
* @param {bool} bool
*/
playBackgroundMusic : function(
char,
bool 
)
{
},

/**
 * @method playEffect
* @param {char|char} char
* @param {bool} bool
* @return {unsigned int|unsigned int}
*/
playEffect : function(
char,
bool 
)
{
    return 0;
},

/**
 * @method preloadEffect
 * @param {char} arg0
 */
preloadEffect : function (
char 
)
{
},

/**
 * @method unloadEffect
 * @param {char} arg0
 */
unloadEffect : function (
char 
)
{
},

/**
 * @method rewindBackgroundMusic
 */
rewindBackgroundMusic : function (
)
{
},

/**
 * @method pauseEffect
 * @param {unsigned int} arg0
 */
pauseEffect : function (
int 
)
{
},

/**
 * @method getClassTypeInfo
 * @return {long}
 */
getClassTypeInfo : function (
)
{
    return 0;
},

/**
 * @method resumeBackgroundMusic
 */
resumeBackgroundMusic : function (
)
{
},

/**
 * @method setEffectsVolume
 * @param {float} arg0
 */
setEffectsVolume : function (
float 
)
{
},

/**
 * @method resumeEffect
 * @param {unsigned int} arg0
 */
resumeEffect : function (
int 
)
{
},

/**
 * @method end
 */
end : function (
)
{
},

/**
 * @method sharedEngine
 * @return {CocosDenshion::SimpleAudioEngine}
 */
sharedEngine : function (
)
{
    return CocosDenshion::SimpleAudioEngine;
},

/**
 * @method SimpleAudioEngine
 * @constructor
 */
SimpleAudioEngine : function (
)
{
},

};

/**
 * @class CAVideoPlayerControlView
 */
ca.CAVideoPlayerControlView = {

/**
 * @method getPlayerControlViewDelegate
 * @return {extension::CAVideoPlayerControlViewDelegate}
 */
getPlayerControlViewDelegate : function (
)
{
    return extension::CAVideoPlayerControlViewDelegate;
},

/**
 * @method setShowBackButton
 * @param {bool} arg0
 */
setShowBackButton : function (
bool 
)
{
},

/**
 * @method setTitle
 * @param {String} arg0
 */
setTitle : function (
str 
)
{
},

/**
 * @method setUrl
 * @param {String} arg0
 */
setUrl : function (
str 
)
{
},

/**
 * @method setPlayerControlViewDelegate
 * @param {extension::CAVideoPlayerControlViewDelegate} arg0
 */
setPlayerControlViewDelegate : function (
cavideoplayercontrolviewdelegate 
)
{
},

/**
 * @method getTitle
 * @return {String}
 */
getTitle : function (
)
{
    return ;
},

/**
 * @method setFullPath
 * @param {String} arg0
 */
setFullPath : function (
str 
)
{
},

/**
 * @method getShowBackButton
 * @return {bool}
 */
getShowBackButton : function (
)
{
    return false;
},

/**
 * @method createWithFrame
 * @param {rect_object} arg0
 * @return {extension::CAVideoPlayerControlView}
 */
createWithFrame : function (
drect 
)
{
    return extension::CAVideoPlayerControlView;
},

/**
 * @method createWithLayout
 * @param {layout_object} arg0
 * @return {extension::CAVideoPlayerControlView}
 */
createWithLayout : function (
dlayout 
)
{
    return extension::CAVideoPlayerControlView;
},

/**
 * @method createWithCenter
 * @param {rect_object} arg0
 * @return {extension::CAVideoPlayerControlView}
 */
createWithCenter : function (
drect 
)
{
    return extension::CAVideoPlayerControlView;
},

/**
 * @method CAVideoPlayerControlView
 * @constructor
 */
CAVideoPlayerControlView : function (
)
{
},

};
