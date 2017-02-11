ca.ENGINE_VERSION = "CrossApp-JS v1.4";

ca.LANGUAGE_ENGLISH    = 0;
ca.LANGUAGE_CHINESE    = 1;
ca.LANGUAGE_FRENCH     = 2;
ca.LANGUAGE_ITALIAN    = 3;
ca.LANGUAGE_GERMAN     = 4;
ca.LANGUAGE_SPANISH    = 5;
ca.LANGUAGE_RUSSIAN    = 6;
ca.LANGUAGE_KOREAN     = 7;
ca.LANGUAGE_JAPANESE   = 8;
ca.LANGUAGE_HUNGARIAN  = 9;
ca.LANGUAGE_PORTUGUESE = 10;
ca.LANGUAGE_ARABIC     = 11;

ca.CAActivityIndicatorViewStyle = {};
ca.CAActivityIndicatorViewStyle.WhiteLarge = 0;
ca.CAActivityIndicatorViewStyle.GrayLarge = 1;
ca.CAActivityIndicatorViewStyle.White = 2;
ca.CAActivityIndicatorViewStyle.Gray = 3;
ca.CAActivityIndicatorViewStyle.Image = 4;

//CAAutoCollectionView
ca.Orientation = {};
ca.Orientation.Horizontal = 0;
ca.Orientation.Vertical = 1;

ca.CellHoriAlign = {};
ca.CellHoriAlign.HoriAlignLeft = 0;
ca.CellHoriAlign.HoriAlignCenter = 1;
ca.CellHoriAlign.HoriAlignRight = 2;

ca.CellVertAlign = {};
ca.CellVertAlign.VertAlignTop = 0;
ca.CellVertAlign.VertAlignCenter = 1;
ca.CellVertAlign.VertAlignBottom = 2;

ca.CABarVerticalAlignment = {};
ca.CABarVerticalAlignment.Top = 0,
ca.CABarVerticalAlignment.Bottom = 1;

ca.CAButtonType = {};
ca.CAButtonType.Custom = 0;
ca.CAButtonType.SquareRect = 1;
ca.CAButtonType.RoundedRect = 2;

ca.CAControlEvents = {};
ca.CAControlEvents.TouchDown = 0;
ca.CAControlEvents.TouchDownRepeat = 1;
ca.CAControlEvents.TouchMoved = 2;
ca.CAControlEvents.TouchMovedOutSide = 3;
ca.CAControlEvents.TouchUpInSide = 4;
ca.CAControlEvents.TouchUpOutSide = 5;
ca.CAControlEvents.TouchValueChanged = 6;
ca.CAControlEvents.TouchLongPress = 7;
ca.CAControlEvents.TouchCancelled = 8;
ca.CAControlEvents.Max = 9;

ca.CAControlState = {};
ca.CAControlState.Normal = 0;
ca.CAControlState.Highlighted = 1;
ca.CAControlState.Disabled = 2;
ca.CAControlState.Selected = 3;
ca.CAControlState.All = 4;

ca.CADatePickerMode = {};
ca.CADatePickerMode.CADatePickerModeTime = 0;
ca.CADatePickerMode.CADatePickerModeDate = 1;
ca.CADatePickerMode.CADatePickerModeDateAndTime = 2;
ca.CADatePickerMode.CADatePickerModeCountDownTimer = 3;

ca.CADeviceIdiom = {};
ca.CADeviceIdiom.CADeviceIdiomUnknown = -1;
ca.CADeviceIdiom.CADeviceIdiomPad = 0;
ca.CADeviceIdiom.CADeviceIdiomPhone = 1;

ca.CABlueToothState = {};
ca.CABlueToothState.CABLUETOOTHOEPNSUCCESS = 0;
ca.CABlueToothState.CABLUETOOTHISOEPN = 1;
ca.CABlueToothState.CABLUETOOTHOPENING = 2;
ca.CABlueToothState.CABLUETOOTHCLOSESUCCESS = 3;
ca.CABlueToothState.CABLUETOOTHCLOSED = 4;
ca.CABlueToothState.CABLUETOOTHCLOSEFAILD = 5;

ca.CABlueToothType = {};
ca.CABlueToothType.CABLUETOOTHOPEN = 0;
ca.CABlueToothType.CABLUETOOTHCLOSE = 1;
ca.CABlueToothType.CABLUETOOTHDISCOVERY = 3 ;
ca.CABlueToothType.CABLUETOOTHCANCELDISCOVERY = 4;

ca.CANetWorkType = {};
ca.CANetWorkType.CANetWorkTypeWifi= 0;
ca.CANetWorkType.CANetWorkType3G = 1;
ca.CANetWorkType.CANetWorkTypeNone =2;

ca.ETextAlign = {};
ca.ETextAlign.kAlignCenter        = 0x33, ///< Horizontal center and vertical center.
ca.ETextAlign.kAlignTop           = 0x13, ///< Horizontal center and vertical top.
ca.ETextAlign.kAlignTopRight      = 0x12, ///< Horizontal right and vertical top.
ca.ETextAlign.kAlignRight         = 0x32, ///< Horizontal right and vertical center.
ca.ETextAlign.kAlignBottomRight   = 0x22, ///< Horizontal right and vertical bottom.
ca.ETextAlign.kAlignBottom        = 0x23, ///< Horizontal center and vertical bottom.
ca.ETextAlign.kAlignBottomLeft    = 0x21, ///< Horizontal left and vertical bottom.
ca.ETextAlign.kAlignLeft          = 0x31, ///< Horizontal left and vertical center.
ca.ETextAlign.kAlignTopLeft       = 0x11, ///< Horizontal left and vertical top.

ca.PixelFormat = {};
ca.PixelFormat.PixelFormat_RGBA8888 = 0;
ca.PixelFormat.PixelFormat_RGB888 =1;
ca.PixelFormat.PixelFormat_RGB565 =2;
ca.PixelFormat.PixelFormat_A8 =3;
ca.PixelFormat.PixelFormat_I8 =4;
ca.PixelFormat.PixelFormat_AI88 =5;
ca.PixelFormat.PixelFormat_RGBA4444 =6;
ca.PixelFormat.PixelFormat_RGB5A1 =7;
ca.PixelFormat.PixelFormat_Default = 0,

ca.Format = {};
ca.Format.JPG = 0;//! JPEG
ca.Format.PNG = 1;//! PNG
ca.Format.GIF = 2;//! GIF
ca.Format.TIFF = 3;//! TIFF
ca.Format.WEBP = 4;//! WebP
ca.Format.ETC = 5;//! ETC
ca.Format.TGA = 6;//! TGA
ca.Format.RAW_DATA = 7;//! Raw Data
ca.Format.UNKOWN = 8;//! Unknown format

ca.AsyncType = {};
ca.AsyncType.AsyncImageType = 0;
ca.AsyncType.AsyncStringType = 1;

ca.CAImageViewScaleType = {};
ca.CAImageViewScaleType.CAImageViewScaleTypeFitImageXY = 0;         //塞满
ca.CAImageViewScaleType.CAImageViewScaleTypeFitImageCrop = 1;           //塞满裁剪，不变形, 居中
ca.CAImageViewScaleType.CAImageViewScaleTypeFitImageInside = 2;         //显示全部，不变形, 居中
ca.CAImageViewScaleType.CAImageViewScaleTypeFitViewByHorizontal = 3;    //显示全部，不变形，横向适应图片
ca.CAImageViewScaleType.CAImageViewScaleTypeFitViewByVertical = 4;       //显示全部，不变形，纵横适应图片

ca.ccKeypadMSGType = {};
ca.ccKeypadMSGType.kTypeBackClicked = 1;
ca.ccKeypadMSGType.kTypeMenuClicked = 2;

ca.DHorizontalLayoutType = {};
ca.DHorizontalLayoutType.L_R = 0;
ca.DHorizontalLayoutType.L_W = 1;
ca.DHorizontalLayoutType.R_W = 2;
ca.DHorizontalLayoutType.W_C = 3;
ca.DHorizontalLayoutType.NW_C = 4;

ca.DVerticalLayoutType = {};
ca.DVerticalLayoutType.T_B = 0;
ca.DVerticalLayoutType.T_H = 1;
ca.DVerticalLayoutType.B_H = 2;
ca.DVerticalLayoutType.H_C = 3;
ca.DVerticalLayoutType.NH_C = 4;

ca.CAPageControlStyle = {};
ca.CAPageControlStyle.Dot = 0;
ca.CAPageControlStyle.Round = 1;
ca.CAPageControlStyle.Rectangle = 2;

ca.CAProgressStyle = {};
ca.CAProgressStyle.Default = 0;
ca.CAProgressStyle.Bar = 1;

ca.PullToRefreshType = {};
ca.PullToRefreshType.Header = 0;
ca.PullToRefreshType.Footer = 1;
ca.PullToRefreshType.Custom = 2;

ca.MultitouchGesture = {};
ca.MultitouchGesture.Zoom = 0;
ca.MultitouchGesture.Rotate = 1;
ca.MultitouchGesture.ZoomAndRotate = 2;
ca.MultitouchGesture.None = 3;

ca.CAIndicatorType = {};
ca.CAIndicatorType.Horizontal = 0;
ca.CAIndicatorType.Vertical = 1;

ca.CAStepperOrientation = {};
ca.CAStepperOrientation.Horizontal = 0;
ca.CAStepperOrientation.Vertical = 1;

ca.KeyboardType = {};
ca.KeyboardType.Default = 0;
ca.KeyboardType.NumbersAndPunctuation =1;
ca.KeyboardType.URL = 2;
ca.KeyboardType.NumberPad = 3;
ca.KeyboardType.PhonePad = 4;
ca.KeyboardType.NamePhonePad = 5;
ca.KeyboardType.EmailAddress = 6;

ca.ReturnType = {};
ca.ReturnType.Done=0,
ca.ReturnType.Go = 1;
ca.ReturnType.Next = 2;
ca.ReturnType.Search = 3;
ca.ReturnType.Send = 4;

ca.ClearButtonMode = {};
ca.ClearButtonMode.None = 0,
ca.ClearButtonMode.WhileEditing = 1;

ca.TextFieldAlign = {};
ca.TextFieldAlign.Left = 0;
ca.TextFieldAlign.Center = 1;
ca.TextFieldAlign.Right = 2;

ca.TextViewAlign = {};
ca.TextViewAlign.Left = 0;
ca.TextViewAlign.Center = 1;
ca.TextViewAlign.Right = 2;

//CATextVie与CATextField不统一
//ca.ReturnType.Default=0,
//ca.ReturnType.Done,
//ca.ReturnType.Send,
//ca.ReturnType.Next

ca.VPError = {};
ca.VPError.kErrorNone = 0;
ca.VPError.kErrorOpenFile = 1;
ca.VPError.kErrorStreamInfoNotFound = 2;
ca.VPError.kErrorStreamNotFound = 3;
ca.VPError.kErrorCodecNotFound = 4;
ca.VPError.kErrorOpenCodec = 5;
ca.VPError.kErrorAllocateFrame = 6;
ca.VPError.kErrorSetupScaler = 7;
ca.VPError.kErrorReSampler = 8;
ca.VPError.kErrorUnsupported = 9;
ca.VPError.kErrorUnknown = 10;

ca.VPFrameType = {};
ca.VPFrameType.kFrameTypeAudio = 0;
ca.VPFrameType.kFrameTypeVideo = 1;

ca.VPVideoFrameFormat = {};
ca.VPVideoFrameFormat.kVideoFrameFormatRGB = 0;
ca.VPVideoFrameFormat.kVideoFrameFormatYUV = 1;

ca.CALayoutLinearType = {};
ca.CALayoutLinearType.CALayoutLinearHorizontal = 0;
ca.CALayoutLinearType.CALayoutLinearVertical = 1;

ca.CAViewAnimationCurve = {};
ca.CAViewAnimationCurve.CAViewAnimationCurveLinear = 0;
ca.CAViewAnimationCurve.CAViewAnimationCurveEaseOut = 1;          // slow at end
ca.CAViewAnimationCurve.CAViewAnimationCurveEaseIn = 2;           // slow at beginning
ca.CAViewAnimationCurve.CAViewAnimationCurveEaseInOut = 3;         // slow at beginning and end

ca.CAVerticalTextAlignment = {};
ca.CAVerticalTextAlignment.CAVerticalTextAlignmentTop = 0;
ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter = 1;
ca.CAVerticalTextAlignment.CAVerticalTextAlignmentBottom = 2;

ca.CATextAlignment = {};
ca.CATextAlignment.CATextAlignmentLeft = 0;
ca.CATextAlignment.CATextAlignmentCenter = 1;
ca.CATextAlignment.CATextAlignmentRight = 2;

ca.CAStatusBarStyle = {};
ca.CAStatusBarStyle.CAStatusBarStyleDefault = 0; // Dark content, for use on light backgrounds
ca.CAStatusBarStyle.CAStatusBarStyleLightContent = 1; // Light content, for use on dark backgrounds

ca.CAInterfaceOrientation = {};
ca.CAInterfaceOrientation.CAInterfaceOrientationUnknown  = 0;
ca.CAInterfaceOrientation.CAInterfaceOrientationPortrait = 1;
ca.CAInterfaceOrientation.CAInterfaceOrientationLandscape = 2;

ca.ConversionResult = {};
ca.ConversionResult.conversionOK = 0;           /* conversion successful */
ca.ConversionResult.sourceExhausted = 1;        /* partial character in source, but hit end */
ca.ConversionResult.targetExhausted = 2;        /* insuff. room in target for conversion */
ca.ConversionResult.sourceIllegal = 3;           /* source sequence is illegal/malformed */

ca.ConversionFlags = {};
ca.ConversionFlags.strictConversion = 0;
ca.ConversionFlags.lenientConversion = 1;

ca.DicItemType = {};
ca.DicItemType.EDIC_TYPENULL = 0;
ca.DicItemType.EDIC_TYPEINT = 1;
ca.DicItemType.EDIC_TYPEUINT = 2;
ca.DicItemType.EDIC_TYPEFLOAT = 3;
ca.DicItemType.EDIC_TYPESTRING = 4;
ca.DicItemType.EDIC_TYPEBOOLEN = 5;
ca.DicItemType.EDIC_TYPEARRAY = 6;
ca.DicItemType.EDIC_TYPEOBJECT = 7;

ca.GifRecordType = {};
ca.GifRecordType.UNDEFINED_RECORD_TYPE = 0;
ca.GifRecordType.SCREEN_DESC_RECORD_TYPE = 1;
ca.GifRecordType.IMAGE_DESC_RECORD_TYPE = 2; /* Begin with ',' */
ca.GifRecordType.EXTENSION_RECORD_TYPE = 3;  /* Begin with '!' */
ca.GifRecordType.TERMINATE_RECORD_TYPE = 4;   /* Begin with ';' */

ca.HttpRequestType = {};
ca.HttpRequestType.kHttpGet = 0;
ca.HttpRequestType.kHttpPost = 1;
ca.HttpRequestType.kHttpPostFile = 2;
ca.HttpRequestType.kHttpPut = 3;
ca.HttpRequestType.kHttpDelete = 4;
ca.HttpRequestType.kHttpUnkown = 5;

ca.NetworkStatus = {};
ca.NetworkStatus.NotReachable     = 0,
ca.NetworkStatus.ReachableViaWiFi = 2,
ca.NetworkStatus.ReachableViaWWAN = 1

ca.tAudioManagerMode = {};
ca.tAudioManagerMode.kAMM_FxOnly = 0;                    //!Other apps will be able to play audio
ca.tAudioManagerMode.kAMM_FxPlusMusic = 1;                //!Only this app will play audio
ca.tAudioManagerMode.kAMM_FxPlusMusicIfNoOtherAudio = 2;    //!If another app is playing audio at start up then allow it to continue and don't play music
ca.tAudioManagerMode.kAMM_MediaPlayback = 3;                //!This app takes over audio e.g music player app
ca.tAudioManagerMode.kAMM_PlayAndRecord = 4;                //!App takes over audio and has input and output

ca.tAudioManagerState = {};
ca.tAudioManagerState.kAMStateUninitialised = 0; //!Audio manager has not been initialised - do not use
ca.tAudioManagerState.kAMStateInitialising = 1;  //!Audio manager is in the process of initialising - do not use
ca.tAudioManagerState.kAMStateInitialised = 2;       //!Audio manager is initialised - safe to use

ca.tAudioManagerResignBehavior = {};
ca.tAudioManagerResignBehavior.kAMRBDoNothing = 0;                //Audio manager will not do anything on resign or becoming active
ca.tAudioManagerResignBehavior.kAMRBStopPlay = 1;                //Background music is stopped on resign and resumed on become active
ca.tAudioManagerResignBehavior.kAMRBStop = 2;                    //Background music is stopped on resign but not resumed - maybe because you want to do this from within your game

ca.tAudioSourceChannel = {};
ca.tAudioSourceChannel.kASC_Left = 0;
ca.tAudioSourceChannel.kASC_Right = 1;

ca.tLongAudioSourceState = {};
ca.tLongAudioSourceState.kLAS_Init = 0;
ca.tLongAudioSourceState.kLAS_Loaded = 1;
ca.tLongAudioSourceState.kLAS_Playing = 2;
ca.tLongAudioSourceState.kLAS_Paused = 3;
ca.tLongAudioSourceState.kLAS_Stopped = 4;


ca.FLT_MAX = 0;
// dlayout
DHorizontalLayout = function(var1,var2,vtype){
    var vleft = ca.FLT_MAX;
    var vright = ca.FLT_MAX;
    var vwidth = ca.FLT_MAX;
    var vcenter = ca.FLT_MAX;
    var vnormalizedWidth = ca.FLT_MAX;
    
    switch (vtype)
    {
        case ca.DHorizontalLayoutType.L_R:
        {
            vleft = var1;
            vright = var2;
        }
            break;
        case ca.DHorizontalLayoutType.L_W:
        {
            vleft = var1;
            vwidth = var2;
        }
            break;
        case ca.DHorizontalLayoutType.R_W:
        {
            vright = var1;
            vwidth = var2;
        }
            break;
        case ca.DHorizontalLayoutType.W_C:
        {
            vwidth = var1;
            vcenter = var2;
        }
            break;
        case ca.DHorizontalLayoutType.NW_C:
        {
            vnormalizedWidth = var1;
            vcenter = var2;
        }
            break;
        default:
            break;
    }
    
    return {left:vleft,right:vright,width:vwidth,center:vcenter,type:vtype,normalizedWidth:vnormalizedWidth};
};

DVerticalLayout =function (var1,var2,vtype){
    
    var vtop = ca.FLT_MAX;
    var vbottom = ca.FLT_MAX;
    var vheight = ca.FLT_MAX;
    var vcenter = ca.FLT_MAX;
    var vnormalizedWidth = ca.FLT_MAX;
    
    switch (vtype)
    {
        case ca.DVerticalLayoutType.T_B:
        {
            vtop = var1;
            vbottom = var2;
        }
            break;
        case ca.DVerticalLayoutType.T_H:
        {
            vtop = var1;
            vheight = var2;
        }
            break;
        case ca.DVerticalLayoutType.B_H:
        {
            vbottom = var1;
            vheight = var2;
        }
            break;
        case ca.DVerticalLayoutType.H_C:
        {
            vheight = var1;
            vcenter = var2;
        }
            break;
        case ca.DVerticalLayoutType.NH_C:
        {
            vbottom = var1;
            vnormalizedWidth = var2;
        }
            break;
        default:
            break;
    }
    
    return {top:vtop,bottom:vbottom,height:vheight,center:vcenter,type:vtype,normalizedWidth:vnormalizedWidth};
};

DLayout = function (hor,ver){
    return {horizontal:hor,vertical:ver};
};


//ca.HorizontalLayout = HorizontalLayout;
//ca.VerticalLayout = VerticalLayout;
//ca.DLayout = DLayout;


DHorizontalLayout_L_R = function(left,right){
   return DHorizontalLayout(left, right, ca.DHorizontalLayoutType.L_R);
};

DHorizontalLayout_L_W = function(left,width){
    return DHorizontalLayout(left, width, ca.DHorizontalLayoutType.L_W);
};

//DHorizontalLayout_L_C = function(left,center){
//    return DHorizontalLayout(left, center, ca.DHorizontalLayoutType.L_C);
//};

DHorizontalLayout_R_W = function(right,width){
    return DHorizontalLayout(right,width, ca.DHorizontalLayoutType.R_W);
};

//DHorizontalLayout_R_C = function(right,center){
//    return DHorizontalLayout(right,center, ca.DHorizontalLayoutType.R_C);
//};

DHorizontalLayout_W_C = function(width,center){
    return DHorizontalLayout(width, center, ca.DHorizontalLayoutType.W_C);
};
DHorizontalLayout_NW_C = function(width,center){
    return DHorizontalLayout(width, center, ca.DHorizontalLayoutType.NW_C);
};


DVerticalLayout_T_B = function(top,bottom){
    return DVerticalLayout(top,bottom, ca.DVerticalLayoutType.T_B);
};

DVerticalLayout_T_H = function(top,height){
    return DVerticalLayout(top,height, ca.DVerticalLayoutType.T_H);
};

//DVerticalLayout_T_C = function(top,center){
//    return DVerticalLayout(top,center, ca.DVerticalLayoutType.T_C);
//};

DVerticalLayout_B_H = function(bottom,height){
    return DVerticalLayout(bottom,height, ca.DVerticalLayoutType.B_H);
};

//DVerticalLayout_B_C = function(bottom,center){
//    return DVerticalLayout(bottom,center, ca.DVerticalLayoutType.B_C);
//};

DVerticalLayout_H_C = function(height,center){
    return DVerticalLayout(height,center, ca.DVerticalLayoutType.H_C);
};
DVerticalLayout_NH_C = function(height,center){
    return DVerticalLayout(height,center, ca.DVerticalLayoutType.NH_C);
};

DHorizontalLayouttZero  = DHorizontalLayout(0,0,0);
DVerticalLayoutZero     = DVerticalLayout(0,0,0);
DLayoutZero             = DLayout(DHorizontalLayouttZero,DVerticalLayoutZero);
DHorizontalLayoutFill   = DHorizontalLayout_L_R(0, 0);
DVerticalLayoutFill     = DVerticalLayout_T_B(0, 0);
DLayoutFill             = DLayout(DHorizontalLayoutFill, DVerticalLayoutFill);


CAFont = function(){
    return  {
    fontSize: 24,
    color: ca.BLACK,
    fontName: "",
    italics: false,
    bold: false,
    underLine: false,
    deleteLine: false,
    };
}



ca.RED = {r:255, g:0, b:0,a:255};
ca.GREEN = {r:0, g:255, b:0,a:255};
ca.BLUE = {r:0, g:0, b:255,a:255};
ca.BLACK = {r:0, g:0, b:0,a:255};
ca.WHITE = {r:255, g:255, b:255,a:255};
ca.YELLOW = {r:255, g:255, b:0,a:255};



//
// Reusable objects
//
ca._reuse_p = [ {x:0, y:0}, {x:0,y:0}, {x:0,y:0}, {x:0,y:0} ];
ca._reuse_p_index = 0;
ca._reuse_size = {width:0, height:0};
ca._reuse_rect = {x:0, y:0, width:0, height:0};
ca._reuse_color3b = {r:255, g:255, b:255 };
ca._reuse_color4b = {r:255, g:255, b:255, a:255 };

//
// Basic sturcture : Point
//
ca.p = function( x, y )
{
    if (x == undefined)
        return {x: 0, y: 0};
    if (y == undefined)
        return {x: x.x, y: x.y};
    return {x:x, y:y};
};
ca.DPoint = function( x, y )
{
    if( ca._reuse_p_index == ca._reuse_p.length )
        ca._reuse_p_index = 0;
    
    var p = ca._reuse_p[ ca._reuse_p_index];
    ca._reuse_p_index++;
    p.x = x;
    p.y = y;
    return p;
};

ca.dpointEqualToDPoint = function (point1, point2) {
    return ((point1.x == point2.x) && (point1.y == point2.y));
};

ca.DPointZero = function () {
    return ca.p(0, 0);
};

//
// Basic sturcture : Size
//
ca.size = function(w,h)
{
    return {width:w, height:h};
};
ca.dsize = function(w,h)
{
    ca._reuse_size.width = w;
    ca._reuse_size.height = h;
    return ca._reuse_size;
};
ca.DRect= function(w,h)
{
    ca._reuse_size.width = w;
    ca._reuse_size.height = h;
    return ca._reuse_size;
};

ca.dsizeEqualToDSize = function (size1, size2)
{
    return ((size1.width == size2.width) && (size1.height == size2.height));
};

ca.DSizeZero = function () {
    return ca.size(0, 0);
};


/**
 * create a ca.rect object
 * @param {Number|ca.point|ca.rect} [x] a Number value as x or a ca.point object as origin or a ca.rect clone object
 * @param {Number|ca.size} [y] x1 a Number value as y or a ca.size object as size
 * @param {Number} [w]
 * @param {Number} [h]
 * @return {Object} a ca.rect object
 */
ca.rect = function(x,y,w,h)
{
    var argLen = arguments.length;
    if (argLen === 0)
        return { x: 0, y: 0, width: 0, height: 0 };
    
    if (argLen === 1)
        return { x: x.x, y: x.y, width: x.width, height: x.height };
    
    if (argLen === 2)
        return { x: x.x, y: x.y, width: y.width, height: y.height };
    
    if (argLen === 4)
        return { x: x, y: y, width: w, height: h };
    
    throw "unknown argument type";
};
ca.drect = function(x,y,w,h)
{
    ca._reuse_rect.x = x;
    ca._reuse_rect.y = y;
    ca._reuse_rect.width = w;
    ca._reuse_rect.height = h;
    return ca._reuse_rect;
};
ca.rectEqualToRect = function (rect1, rect2) {
    return ( rect1.x==rect2.x && rect1.y==rect2.y && rect1.width==rect2.width && rect1.height==rect2.height);
};

ca.rectContainsRect = function (rect1, rect2) {
    if ((rect1.x >= rect2.x) || (rect1.y >= rect2.y) ||
        ( rect1.x + rect1.width <= rect2.x + rect2.width) ||
        ( rect1.y + rect1.height <= rect2.y + rect2.height))
        return false;
    return true;
};

ca.RectZero = function () {
    return ca.drect(0, 0, 0, 0);
};


// Basic sturcture : Color
ca.Color = function (r, g, b, a) {
    this.r = r || 0;
    this.g = g || 0;
    this.b = b || 0;
    this.a = (a === undefined) ? 255 : a;
};

/**
 * Generate a color object based on multiple forms of parameters
 * @example
 *
 * // 1. All channels seperately as parameters
 * var color1 = ca.color(255, 255, 255, 255);
 *
 * // 2. Convert a hex string to a color
 * var color2 = ca.color("#000000");
 *
 * // 3. An color object as parameter
 * var color3 = ca.color({r: 255, g: 255, b: 255, a: 255});
 *
 * Alpha channel is optional. Default value is 255
 *
 * @param {Number|String|ca.Color} r
 * @param {Number} g
 * @param {Number} b
 * @param {Number} [a=255]
 * @returns {ca.Color}
 */
ca.color = function (r, g, b, a) {
    if (r === undefined)
        return {r: 0, g: 0, b: 0, a: 255};
    if (typeof r === "string")
        return ca.hexToColor(r);
    if (typeof r === "object")
        return {r: r.r, g: r.g, b: r.b, a: (r.a === undefined) ? 255 : r.a};
    return  {r: r, g: g, b: b, a: (a === undefined ? 255 : a)};
};

/**
 * returns true if both caColor3B are equal. Otherwise it returns false.
 * @param {ca.Color} color1
 * @param {ca.Color} color2
 * @return {Boolean}  true if both caColor3B are equal. Otherwise it returns false.
 */
ca.colorEqual = function(color1, color2){
    return color1.r === color2.r && color1.g === color2.g && color1.b === color2.b;
};

/**
 * convert a string of color for style to Color.
 * e.g. "#ff06ff"  to : ca.color(255,6,255)
 * @param {String} hex
 * @return {ca.Color}
 */
ca.hexToColor = function (hex) {
    hex = hex.replace(/^#?/, "0x");
    var c = parseInt(hex);
    var r = c >> 16;
    var g = (c >> 8) % 256;
    var b = c % 256;
    return ca.color(r, g, b);
};

/**
 * convert Color to a string of color for style.
 * e.g.  ca.color(255,6,255)  to : "#ff06ff"
 * @param {ca.Color} color
 * @return {String}
 */
ca.colorToHex = function (color) {
    var hR = color.r.toString(16);
    var hG = color.g.toString(16);
    var hB = color.b.toString(16);
    var hex = "#" + (color.r < 16 ? ("0" + hR) : hR) + (color.g < 16 ? ("0" + hG) : hG) + (color.b < 16 ? ("0" + hB) : hB);
    return hex;
};

/**
 * White color (255, 255, 255, 255)
 * @returns {ca.Color}
 * @private
 */
ca.color._getWhite = function(){
    return ca.color(255, 255, 255, 255);
};

/**
 *  Yellow color (255, 255, 0, 255)
 * @returns {ca.Color}
 * @private
 */
ca.color._getYellow = function () {
    return ca.color(255, 255, 0, 255);
};

/**
 *  Blue color (0, 0, 255, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getBlue = function () {
    return  ca.color(0, 0, 255, 255);
};

/**
 *  Green Color (0, 255, 0, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getGreen = function () {
    return ca.color(0, 255, 0, 255);
};

/**
 *  Red Color (255, 0, 0, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getRed = function () {
    return ca.color(255, 0, 0, 255);
};

/**
 *  Magenta Color (255, 0, 255, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getMagenta = function () {
    return ca.color(255, 0, 255, 255);
};

/**
 *  Black Color (0, 0, 0, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getBlack = function () {
    return ca.color(0, 0, 0, 255);
};

/**
 *  Orange Color (255, 127, 0, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getOrange = function () {
    return ca.color(255, 127, 0, 255);
};

/**
 *  Gray Color (166, 166, 166, 255)
 * @type {ca.Color}
 * @private
 */
ca.color._getGray = function () {
    return ca.color(166, 166, 166, 255);
};

var _proto = ca.color;
/** @expose */
_proto.WHITE;
ca.defineGetterSetter(_proto, "WHITE", _proto._getWhite);
/** @expose */
_proto.YELLOW;
ca.defineGetterSetter(_proto, "YELLOW", _proto._getYellow);
/** @expose */
_proto.BLUE;
ca.defineGetterSetter(_proto, "BLUE", _proto._getBlue);
/** @expose */
_proto.GREEN;
ca.defineGetterSetter(_proto, "GREEN", _proto._getGreen);
/** @expose */
_proto.RED;
ca.defineGetterSetter(_proto, "RED", _proto._getRed);
/** @expose */
_proto.MAGENTA;
ca.defineGetterSetter(_proto, "MAGENTA", _proto._getMagenta);
/** @expose */
_proto.BLACK;
ca.defineGetterSetter(_proto, "BLACK", _proto._getBlack);
/** @expose */
_proto.ORANGE;
ca.defineGetterSetter(_proto, "ORANGE", _proto._getOrange);
/** @expose */
_proto.GRAY;
ca.defineGetterSetter(_proto, "GRAY", _proto._getGray);

// Cocos2d-html5 supports multi scene resources preloading.
// This is a compatible function for JSB.
ca.Loader = ca.Class.extend({
                            initWith:function (resources, selector, target) {
                            if (selector) {
                            this._selector = selector;
                            this._target = target;
                            }
                            this._selector.call(this._target);
                            }
                            });

ca.Loader.preload = function (resources, selector, target) {
    if (!this._instance) {
        this._instance = new ca.Loader();
    }
    this._instance.initWith(resources, selector, target);
    return this._instance;
};

ca.LoaderScene = ca.Loader;

var ConfigType = {
NONE: 0,
COCOSTUDIO: 1
};