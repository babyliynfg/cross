ca.ENGINE_VERSION = "CrossApp-JS v2.0.0";

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

ca.CAHttpRequest.Type = {};
ca.CAHttpRequest.Type.Get = 0;
ca.CAHttpRequest.Type.Post = 1;
ca.CAHttpRequest.Type.PostFile = 2;
ca.CAHttpRequest.Type.Put = 3;
ca.CAHttpRequest.Type.Delete = 4;
ca.CAHttpRequest.Type.Unkown = 5;


ca.CAActivityIndicatorView.Style = {};
ca.CAActivityIndicatorView.Style.WhiteLarge = 0;
ca.CAActivityIndicatorView.Style.GrayLarge = 1;
ca.CAActivityIndicatorView.Style.White = 2;
ca.CAActivityIndicatorView.Style.Gray = 3;
ca.CAActivityIndicatorView.Style.Image = 4;

ca.CAScrollView.MultitouchGesture = {};
ca.CAScrollView.MultitouchGesture.Zoom = 0;
ca.CAScrollView.MultitouchGesture.Rotate = 1;
ca.CAScrollView.MultitouchGesture.ZoomAndRotate = 2;
ca.CAScrollView.MultitouchGesture.None = 3;

ca.CAListView.Orientation = {};
ca.CAListView.Orientation.Vertical = 0;
ca.CAListView.Orientation.Horizontal = 1;


//CAAutoCollectionView
ca.CAAutoCollectionView.Orientation = {};
ca.CAAutoCollectionView.Orientation.Vertical = 0;
ca.CAAutoCollectionView.Orientation.Horizontal = 1;

ca.CAAutoCollectionView.CellHoriAlign = {};
ca.CAAutoCollectionView.CellHoriAlign.HoriAlignLeft = 0;
ca.CAAutoCollectionView.CellHoriAlign.HoriAlignCenter = 1;
ca.CAAutoCollectionView.CellHoriAlign.HoriAlignRight = 2;

ca.CAAutoCollectionView.CellVertAlign = {};
ca.CAAutoCollectionView.CellVertAlign.VertAlignTop = 0;
ca.CAAutoCollectionView.CellVertAlign.VertAlignCenter = 1;
ca.CAAutoCollectionView.CellVertAlign.VertAlignBottom = 2;

ca.CABarVerticalAlignment = {};
ca.CABarVerticalAlignment.Top = 0,
ca.CABarVerticalAlignment.Bottom = 1;

ca.CAButton.Type = {};
ca.CAButton.Type.Custom = 0;
ca.CAButton.Type.SquareRect = 1;
ca.CAButton.Type.RoundedRect = 2;

ca.CAButton.Event = {};
ca.CAButton.Event.TouchDown = 0;
ca.CAButton.Event.TouchDownRepeat = 1;
ca.CAButton.Event.TouchMoved = 2;
ca.CAButton.Event.TouchMovedOutSide = 3;
ca.CAButton.Event.TouchUpInSide = 4;
ca.CAButton.Event.TouchUpOutSide = 5;
ca.CAButton.Event.TouchLongPress = 6;
ca.CAButton.Event.TouchCancelled = 7;

ca.CAControl.State = {};
ca.CAControl.State.Normal = 0;
ca.CAControl.State.Highlighted = 1;
ca.CAControl.State.Selected = 2;
ca.CAControl.State.Disabled = 3;

ca.CADatePickerView.Mode = {};
ca.CADatePickerView.Mode.Time = 0;
ca.CADatePickerView.Mode.Date = 1;
ca.CADatePickerView.Mode.DateAndTime = 2;
ca.CADatePickerView.Mode.CountDownTimer = 3;

ca.CADeviceIdiom = {};
ca.CADeviceIdiom.Unknown = -1;
ca.CADeviceIdiom.iPad = 0;
ca.CADeviceIdiom.iPhone = 1;

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

ca.CADevice = {};
ca.CADevice.NetWorkData = {};
ca.CADevice.NetWorkData.Wifi= 0;
ca.CADevice.NetWorkData.ReachableViaWWAN = 1;
ca.CADevice.NetWorkData.None =2;

ca.CADevice.VolumeData = {};
ca.CADevice.VolumeData.Music= 0;
ca.CADevice.VolumeData.System = 1;
ca.CADevice.VolumeData.Ring =2;
ca.CADevice.VolumeData.VoicCall= 0;
ca.CADevice.VolumeData.Alarm = 1;
ca.CADevice.VolumeData.Notification =2;

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

ca.CAImage.PixelFormat = {};
ca.CAImage.PixelFormat.RGBA8888 = 0;
ca.CAImage.PixelFormat.RGB888 =1;
ca.CAImage.PixelFormat.RGB565 =2;
ca.CAImage.PixelFormat.A8 =3;
ca.CAImage.PixelFormat.I8 =4;
ca.CAImage.PixelFormat.AI88 =5;
ca.CAImage.PixelFormat.RGBA4444 =6;
ca.CAImage.PixelFormat.RGB5A1 =7;
ca.CAImage.PixelFormat.DEFAULT = 0,

ca.CAImage.Format = {};
ca.CAImage.Format.JPG = 0;//! JPEG
ca.CAImage.Format.PNG = 1;//! PNG
ca.CAImage.Format.GIF = 2;//! GIF
ca.CAImage.Format.TIFF = 3;//! TIFF
ca.CAImage.Format.WEBP = 4;//! WebP
ca.CAImage.Format.ETC = 5;//! ETC
ca.CAImage.Format.TGA = 6;//! TGA
ca.CAImage.Format.RAW_DATA = 7;//! Raw Data
ca.CAImage.Format.UNKOWN = 8;//! Unknown format

ca.AsyncType = {};
ca.AsyncType.AsyncImageType = 0;
ca.AsyncType.AsyncStringType = 1;

ca.CAImageView.ScaleType = {};
ca.CAImageView.ScaleType.FitImageXY = 0;         //塞满
ca.CAImageView.ScaleType.FitImageCrop = 1;           //塞满裁剪，不变形, 居中
ca.CAImageView.ScaleType.FitImageInside = 2;         //显示全部，不变形, 居中
ca.CAImageView.ScaleType.FitViewByHorizontal = 3;    //显示全部，不变形，横向适应图片
ca.CAImageView.ScaleType.FitViewByVertical = 4;       //显示全部，不变形，纵横适应图片

ca.CAKeypadDispatcher = {};
ca.CAKeypadDispatcher.KeypadMSGType = {};
ca.CAKeypadDispatcher.KeypadMSGType.BackClicked = 1;
ca.CAKeypadDispatcher.KeypadMSGType.MenuClicked = 2;

ca.DHorizontalLayout = {};
ca.DHorizontalLayout.Type = {};
ca.DHorizontalLayout.Type.L_R = 0;
ca.DHorizontalLayout.Type.L_W = 1;
ca.DHorizontalLayout.Type.R_W = 2;
ca.DHorizontalLayout.Type.W_C = 3;
ca.DHorizontalLayout.Type.NW_C = 4;

ca.DVerticalLayout = {};
ca.DVerticalLayout.Type = {};
ca.DVerticalLayout.Type.T_B = 0;
ca.DVerticalLayout.Type.T_H = 1;
ca.DVerticalLayout.Type.B_H = 2;
ca.DVerticalLayout.Type.H_C = 3;
ca.DVerticalLayout.Type.NH_C = 4;

ca.CAPageControl.Style = {};
ca.CAPageControl.Style.Dot = 0;
ca.CAPageControl.Style.Round = 1;
ca.CAPageControl.Style.Rectangle = 2;

ca.CAProgressStyle = {};
ca.CAProgressStyle.Default = 0;
ca.CAProgressStyle.Bar = 1;

ca.CAPullToRefreshView.Type = {};
ca.CAPullToRefreshView.Type.Header = 0;
ca.CAPullToRefreshView.Type.Footer = 1;
ca.CAPullToRefreshView.Type.Custom = 2;



ca.CAIndicatorType = {};
ca.CAIndicatorType.Orientation = {};
ca.CAIndicatorType.Orientation.Horizontal = 0;
ca.CAIndicatorType.Orientation.Vertical = 1;

ca.CAStepper.Orientation = {};
ca.CAStepper.Orientation.Horizontal = 0;
ca.CAStepper.Orientation.Vertical = 1;

ca.CATextField.KeyboardType = {};
ca.CATextField.KeyboardType.Default = 0;
ca.CATextField.KeyboardType.NumbersAndPunctuation =1;
ca.CATextField.KeyboardType.URL = 2;
ca.CATextField.KeyboardType.NumberPad = 3;
ca.CATextField.KeyboardType.PhonePad = 4;
ca.CATextField.KeyboardType.NamePhonePad = 5;
ca.CATextField.KeyboardType.EmailAddress = 6;

ca.CATextField.ReturnType = {};
ca.CATextField.ReturnType.Done=0,
ca.CATextField.ReturnType.Go = 1;
ca.CATextField.ReturnType.Next = 2;
ca.CATextField.ReturnType.Search = 3;
ca.CATextField.ReturnType.Send = 4;

ca.CATextField.ClearButtonMode = {};
ca.CATextField.ClearButtonMode.None = 0,
ca.CATextField.ClearButtonMode.WhileEditing = 1;

ca.CATextField.Align = {};
ca.CATextField.Align.Left = 0;
ca.CATextField.Align.Center = 1;
ca.CATextField.Align.Right = 2;

ca.CATextView.Align = {};
ca.CATextView.Align.Left = 0;
ca.CATextView.Align.Center = 1;
ca.CATextView.Align.Right = 2;

ca.CATextView.ReturnType = {};
ca.CATextView.ReturnType.Default = 0,
ca.CATextView.ReturnType.Done =1 ;
ca.CATextView.ReturnType.Send =2 ;
ca.CATextView.ReturnType.Next = 3 ;

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

ca.CAViewAnimation.Curve = {};
ca.CAViewAnimation.Curve.Linear = 0;
ca.CAViewAnimation.Curve.EaseOut = 1;          // slow at end
ca.CAViewAnimation.Curve.EaseIn = 2;           // slow at beginning
ca.CAViewAnimation.Curve.EaseInOut = 3;         // slow at beginning and end

ca.CAVerticalTextAlignment = {};
ca.CAVerticalTextAlignment.Top = 0;
ca.CAVerticalTextAlignment.Center = 1;
ca.CAVerticalTextAlignment.Bottom = 2;

ca.CATextAlignment = {};
ca.CATextAlignment.Left = 0;
ca.CATextAlignment.Center = 1;
ca.CATextAlignment.Right = 2;

ca.CAStatusBarStyle = {};
ca.CAStatusBarStyle.Default = 0; // Dark content, for use on light backgrounds
ca.CAStatusBarStyle.LightContent = 1; // Light content, for use on dark backgrounds

ca.CAInterfaceOrientation = {};
ca.CAInterfaceOrientation.Unknown  = 0;
ca.CAInterfaceOrientation.Portrait = 1;
ca.CAInterfaceOrientation.Landscape = 2;

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

ca.CASwitch.Type = {};
ca.CASwitch.Type.SquareRect = 0;
ca.CASwitch.Type.RoundedRect = 1;

ca.CACheckbox.Type = {};
ca.CACheckbox.Type.SquareRect = 0;
ca.CACheckbox.Type.RoundedRect = 1;

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
        case ca.DHorizontalLayout.Type.L_R:
        {
            vleft = var1;
            vright = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.L_W:
        {
            vleft = var1;
            vwidth = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.R_W:
        {
            vright = var1;
            vwidth = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.W_C:
        {
            vwidth = var1;
            vcenter = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.NW_C:
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
        case ca.DVerticalLayout.Type.T_B:
        {
            vtop = var1;
            vbottom = var2;
        }
            break;
        case ca.DVerticalLayout.Type.T_H:
        {
            vtop = var1;
            vheight = var2;
        }
            break;
        case ca.DVerticalLayout.Type.B_H:
        {
            vbottom = var1;
            vheight = var2;
        }
            break;
        case ca.DVerticalLayout.Type.H_C:
        {
            vheight = var1;
            vcenter = var2;
        }
            break;
        case ca.DVerticalLayout.Type.NH_C:
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
   return DHorizontalLayout(left, right, ca.DHorizontalLayout.Type.L_R);
};

DHorizontalLayout_L_W = function(left,width){
    return DHorizontalLayout(left, width, ca.DHorizontalLayout.Type.L_W);
};

DHorizontalLayout_R_W = function(right,width){
    return DHorizontalLayout(right,width, ca.DHorizontalLayout.Type.R_W);
};

DHorizontalLayout_W_C = function(width,center){
    return DHorizontalLayout(width, center, ca.DHorizontalLayout.Type.W_C);
};
DHorizontalLayout_NW_C = function(width,center){
    return DHorizontalLayout(width, center, ca.DHorizontalLayout.Type.NW_C);
};

DVerticalLayout_T_B = function(top,bottom){
    return DVerticalLayout(top,bottom, ca.DVerticalLayout.Type.T_B);
};

DVerticalLayout_T_H = function(top,height){
    return DVerticalLayout(top,height, ca.DVerticalLayout.Type.T_H);
};

DVerticalLayout_B_H = function(bottom,height){
    return DVerticalLayout(bottom,height, ca.DVerticalLayout.Type.B_H);
};

DVerticalLayout_H_C = function(height,center){
    return DVerticalLayout(height,center, ca.DVerticalLayout.Type.H_C);
};
DVerticalLayout_NH_C = function(height,center){
    return DVerticalLayout(height,center, ca.DVerticalLayout.Type.NH_C);
};

DHorizontalLayouttZero  = DHorizontalLayout(0,0,0);
DVerticalLayoutZero     = DVerticalLayout(0,0,0);
DLayoutZero             = DLayout(DHorizontalLayouttZero,DVerticalLayoutZero);
DHorizontalLayoutFill   = DHorizontalLayout_L_R(0, 0);
DVerticalLayoutFill     = DVerticalLayout_T_B(0, 0);
DLayoutFill             = DLayout(DHorizontalLayoutFill, DVerticalLayoutFill);

CAFontShadow = function(){
    return  {
    shadowEnabled: false,
    shadowOffset: ca.DSizeZero,
    shadowBlur: 0,
    shadowColor: {r:0, g:0, b:0, a:88},
    };
};

CAFontStroke = function(){
    return  {
    strokeEnabled: false,
    strokeColor: ca.CAColor4B.BLACK,
    strokeSize: 0,
    };
};

CAFont = function(){
    return  {
    bold: false,
    underLine: false,
    deleteLine: false,
    italics: false,
    italicsValue: 0.5,
    wordWrap: false,
    fontName: "",
    fontSize: 24,
    lineSpacing: 0,
    color: ca.CAColor4B.BLACK,
    textAlignment: ca.CATextAlignment.Left,
    verticalTextAlignment: ca.CAVerticalTextAlignment.Top,
    shadow: CAFontShadow(),
    stroke: CAFontStroke(),
    };
};


ca.CAColor4B = {};
ca.CAColor4B.WHITE = {r:255, g:255, b:255,a:255};
ca.CAColor4B.YELLOW = {r:255, g:255, b:0,a:255};
ca.CAColor4B.GREEN = {r:0, g:255, b:0,a:255};
ca.CAColor4B.BLUE = {r:0, g:0, b:255,a:255};
ca.CAColor4B.RED = {r:255, g:0, b:0,a:255};
ca.CAColor4B.MAGENTA = {r:255, g:0, b:255,a:255};
ca.CAColor4B.BLACK = {r:0, g:0, b:0,a:255};
ca.CAColor4B.ORANGE = {r:255, g:127, b:0,a:255};
ca.CAColor4B.GRAY = {r:166, g:166, b:166,a:255};
ca.CAColor4B.CLEAR = {r:255, g:255, b:255,a:0};

ca.CAColor4F = {};
ca.CAColor4F.WHITE = {r:1, g:1, b:1,a:1};
ca.CAColor4F.YELLOW = {r:1, g:1, b:0,a:1};
ca.CAColor4F.GREEN = {r:0, g:1, b:0,a:1};
ca.CAColor4F.BLUE = {r:0, g:0, b:1,a:1};
ca.CAColor4F.RED = {r:1, g:0, b:0,a:1};
ca.CAColor4F.MAGENTA = {r:1, g:0, b:1,a:1};
ca.CAColor4F.BLACK = {r:0, g:0, b:0,a:1};
ca.CAColor4F.ORANGE = {r:1, g:0.5, b:0,a:1};
ca.CAColor4F.GRAY = {r:0.65, g:0.65, b:0.65,a:1};
ca.CAColor4F.CLEAR = {r:1, g:1, b:1,a:0};

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

ca.DPointEqualToDPoint = function (point1, point2) {
    return ((point1.x == point2.x) && (point1.y == point2.y));
};

ca.DPointZero = function () {
    return ca.p(0, 0);
};

//
// Basic sturcture : Size
//
ca.DSize = function(w,h)
{
    ca._reuse_size.width = w;
    ca._reuse_size.height = h;
    return ca._reuse_size;
};

ca.DSizeEqualToDSize = function (size1, size2)
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
ca.DRect = function(x,y,w,h)
{
    ca._reuse_rect.x = x;
    ca._reuse_rect.y = y;
    ca._reuse_rect.width = w;
    ca._reuse_rect.height = h;
    return ca._reuse_rect;
};
ca.RectEqualToRect = function (rect1, rect2) {
    return ( rect1.x==rect2.x && rect1.y==rect2.y && rect1.width==rect2.width && rect1.height==rect2.height);
};

ca.RectContainsRect = function (rect1, rect2) {
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

ca.CAApplicationDidChangeStatusBarOrientationNotification = "CAApplicationDidChangeStatusBarOrientationNotification";
ca.CROSSAPP_CCLOG_NOTIFICATION = "CROSSAPP_CCLOG_NOTIFICATION";

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


var ConfigType = {
NONE: 0,
COCOSTUDIO: 1
};
