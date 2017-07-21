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

ca.DLayout = {}

ca.DHorizontalLayout = {}
ca.DHorizontalLayout.Type = {};
ca.DHorizontalLayout.Type.L_R = 0;
ca.DHorizontalLayout.Type.L_W = 1;
ca.DHorizontalLayout.Type.R_W = 2;
ca.DHorizontalLayout.Type.W_C = 3;
ca.DHorizontalLayout.Type.NW_C = 4;

ca.DVerticalLayout = {}
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
ca.CACheckbox.Type.Custom = 0;
ca.CACheckbox.Type.SquareRect = 1;
ca.CACheckbox.Type.RoundedRect = 2;

ca.CAAVPlayer.PlaybackBufferEmpty = "PlaybackBufferEmpty";
ca.CAAVPlayer.PlaybackLikelyToKeepUp = "PlaybackLikelyToKeepUp";
ca.CAAVPlayer.PlayStatePause = "PlayStatePause";
ca.CAAVPlayer.PlayStatePlaying = "PlayStatePlaying";
ca.CAAVPlayer.PlayStatePlayback = "PlayStatePlayback";

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


ca.FLT_MAX = 0xFFFFFFFF;
// dlayout
ca.DHorizontalLayout.set = function(var1, var2, _type)
{
    var _left = ca.FLT_MAX;
    var _right = ca.FLT_MAX;
    var _width = ca.FLT_MAX;
    var _center = ca.FLT_MAX;
    var _normalizedWidth = ca.FLT_MAX;
    
    switch (_type)
    {
        case ca.DHorizontalLayout.Type.L_R:
        {
            _left = var1;
            _right = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.L_W:
        {
            _left = var1;
            _width = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.R_W:
        {
            _right = var1;
            _width = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.W_C:
        {
            _width = var1;
            _center = var2;
        }
            break;
        case ca.DHorizontalLayout.Type.NW_C:
        {
            _normalizedWidth = var1;
            _center = var2;
        }
            break;
        default:
            break;
    }
    
    return {left:_left, right:_right, width:_width, center:_center, normalizedWidth:_normalizedWidth, type:_type};
};

ca.DVerticalLayout.set =function (var1, var2, _type){
    
    var _top = ca.FLT_MAX;
    var _bottom = ca.FLT_MAX;
    var _height = ca.FLT_MAX;
    var _center = ca.FLT_MAX;
    var _normalizedHeight = ca.FLT_MAX;
    
    switch (_type)
    {
        case ca.DVerticalLayout.Type.T_B:
        {
            _top = var1;
            _bottom = var2;
        }
            break;
        case ca.DVerticalLayout.Type.T_H:
        {
            _top = var1;
            _height = var2;
        }
            break;
        case ca.DVerticalLayout.Type.B_H:
        {
            _bottom = var1;
            _height = var2;
        }
            break;
        case ca.DVerticalLayout.Type.H_C:
        {
            _height = var1;
            _center = var2;
        }
            break;
        case ca.DVerticalLayout.Type.NH_C:
        {
            _normalizedHeight = var1;
            _center = var2;
        }
            break;
        default:
            break;
    }
    
    return {top:_top, bottom:_bottom, height:_height, center:_center, type:_type, normalizedHeight:_normalizedHeight};
};


ca.DLayout.set = function (hor, ver)
{
    return {horizontal:hor, vertical:ver};
};

ca.DHorizontalLayout_L_R = function(left,right)
{
    return ca.DHorizontalLayout.set(left, right, ca.DHorizontalLayout.Type.L_R);
};

ca.DHorizontalLayout_L_W = function(left,width)
{
    return ca.DHorizontalLayout.set(left, width, ca.DHorizontalLayout.Type.L_W);
};

ca.DHorizontalLayout_R_W = function(right,width)
{
    return ca.DHorizontalLayout.set(right,width, ca.DHorizontalLayout.Type.R_W);
};

ca.DHorizontalLayout_W_C = function(width,center)
{
    return ca.DHorizontalLayout.set(width, center, ca.DHorizontalLayout.Type.W_C);
};
ca.DHorizontalLayout_NW_C = function(width,center)
{
    return ca.DHorizontalLayout.set(width, center, ca.DHorizontalLayout.Type.NW_C);
};

ca.DVerticalLayout_T_B = function(top,bottom)
{
    return ca.DVerticalLayout.set(top,bottom, ca.DVerticalLayout.Type.T_B);
};

ca.DVerticalLayout_T_H = function(top,height)
{
    return ca.DVerticalLayout.set(top,height, ca.DVerticalLayout.Type.T_H);
};

ca.DVerticalLayout_B_H = function(bottom,height)
{
    return ca.DVerticalLayout.set(bottom,height, ca.DVerticalLayout.Type.B_H);
};

ca.DVerticalLayout_H_C = function(height,center)
{
    return ca.DVerticalLayout.set(height,center, ca.DVerticalLayout.Type.H_C);
};
ca.DVerticalLayout_NH_C = function(height,center)
{
    return ca.DVerticalLayout.set(height,center, ca.DVerticalLayout.Type.NH_C);
};

ca.DHorizontalLayouttZero  = ca.DHorizontalLayout.set(0,0,0);
ca.DVerticalLayoutZero     = ca.DVerticalLayout.set(0,0,0);
ca.DLayoutZero             = ca.DLayout.set(ca.DHorizontalLayouttZero, ca.DVerticalLayoutZero);
ca.DHorizontalLayoutFill   = ca.DHorizontalLayout_L_R(0, 0);
ca.DVerticalLayoutFill     = ca.DVerticalLayout_T_B(0, 0);
ca.DLayoutFill             = ca.DLayout.set(ca.DHorizontalLayoutFill, ca.DVerticalLayoutFill);

ca.CAFontShadow = function()
{
    return  {
    shadowEnabled: false,
    shadowOffset: ca.DSizeZero,
    shadowBlur: 0,
    shadowColor: {r:0, g:0, b:0, a:88},
    };
};

ca.CAFontStroke = function()
{
    return  {
    strokeEnabled: false,
    strokeColor: ca.CAColor4B.BLACK,
    strokeSize: 0,
    };
};

ca.CAFont = function()
{
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
    shadow: ca.CAFontShadow(),
    stroke: ca.CAFontStroke(),
    };
};

ca.CAColor4B = {}
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

ca.CAColor4B.set = function (_r, _g, _b, _a)
{
    return {r:_r, g:_g, b:_b, a:_a};
};

ca.CAColor4B.setUInt32 = function (_rgba)
{
    var _b = _rgba % 0x100;
    _rgba /= 0x100;
    var _g = _rgba % 0x100;
    _rgba /= 0x100;
    var _r = _rgba % 0x100;
    _rgba /= 0x100;
    var _a = _rgba % 0x100;
    
    return {r:_r, g:_g, b:_b, a:_a};
};

ca.CAColor4B.getUInt32 = function (_color)
{
    return (_color.b + _color.g * 0x100 + _color.r * 0x10000 + _color.a * 0x1000000);
};

ca.CAColor4BEquals = function (_color1, _color2)
{
    return (_color1.r == _color2.r && _color1.g == _color2.g && _color1.b == _color2.b && _color1.a == _color2.a);
};

ca.CAColor4F = {}
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

ca.CAColor4F.set = function (_r, _g, _b, _a)
{
    return {r:_r, g:_g, b:_b, a:_a};
};

ca.CAColor4FEquals = function (_color1, _color2)
{
    return (_color1.r == _color2.r && _color1.g == _color2.g && _color1.b == _color2.b && _color1.a == _color2.a);
};

ca.DPoint = {}
ca.DPoint.set = function( _x, _y )
{
    return {x:_x, y:_y};
};

ca.DPointZero = function ()
{
    return ca.DPoint(0, 0);
};

ca.DPointEquals = function (p1, p2)
{
    return ((p1.x == p2.x) && (p1.y == p2.y));
};

ca.DPoint.getDistance = function (p1, p2)
{
    var xx = p1.x - p2.x;
    var yy = p1.y - p2.y;
    return Math.sqrt(xx*xx + yy*yy)
}

ca.DSize = {}
ca.DSize.set = function(_width, _height)
{
    return {width:_width, height:_height};
};

ca.DSizeEquals = function (s1, s2)
{
    return ((s1.width == s2.width) && (s1.height == s2.height));
};

ca.DSizeZero = function ()
{
    return ca.DSize(0, 0);
};

ca.DRect = {}

ca.DRect.set = function(_x, _y, _width, _height)
{
    return {x:_x, y:_y, width:_width, height:_height};
};

ca.DRectZero = function ()
{
    return ca.DRect.set(0, 0, 0, 0);
};

ca.DRectEquals = function (r1, r2)
{
    return ( r1.x == r2.x && r1.y == r2.y && r1.width == r2.width && r1.height == r2.height);
};

ca.DRect.intersectsRect = function (r1, r2)
{
    if (r1.x + r1.width < r2.x)
    {
        return false;
    }
    
    if (r2.x + r2.width < r1.x)
    {
        return false;
    }
    
    if (r1.y + r1.height < r2.y)
    {
        return false;
    }
    
    if (r2.y + r2.height < r1.y)
    {
        return false;
    }
    
    return true;
};

ca.CAApplicationDidChangeStatusBarOrientationNotification = "CAApplicationDidChangeStatusBarOrientationNotification";
ca.CROSSAPP_CCLOG_NOTIFICATION = "CROSSAPP_CCLOG_NOTIFICATION";

