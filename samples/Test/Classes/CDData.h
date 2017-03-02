#include "CommonHttpManager.h"

#define _T(x) L##x
#define CHAR    wchar_t

static const CHAR* menuList[4] =
{
	_T("CrossApp官网"), _T("9秒官网")
};

static const char* iconTag[30] =
{
    "image/AlertView.png",
    "image/button.png",
    "image/Checkbox.png",
    
    "image/SegmentedControl.png",
    "image/ImageView.png",
    "image/Scale9ImageView.png",
    
    "image/indicatorView.png",
    "image/Progress.png",
    "image/slider.png",
    
    "image/Switch.png",
    "image/Stepper.png",
    "image/Label.png",
    
    "image/TextField.png",
    "image/TextView.png",
    "image/TabBar.png",
    
    "image/PageView.png",
    "image/PageControl.png",
    "image/ScrollView.png",
    
    "image/CollectionView.png",
    "image/CollectionView.png",
    "image/CollectionView.png",
    
    "image/CollectionView.png",
    "image/ListView.png",
    "image/TableView.png",
    
    "image/PickerView.png",
    "image/WebView.png",
    "image/GifView.png",
    
    "image/FlashView.png",
    "image/Video.png",
    "image/RenderImage.png",
    
};

