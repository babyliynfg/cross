

#include "RootWindow.h"
#include "MenuViewController.h"
#include "CDUIShowAutoCollectionView.h"
#include "CDWebViewController.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

static RootWindow* _window = NULL;

RootWindow* RootWindow::getInstance()
{
    if (_window == NULL)
    {
        _window = new RootWindow();
        _window->init();
        _window->autorelease();
    }
    return _window;
    
}

RootWindow::RootWindow()
:m_pRootNavigationController(NULL)
,m_pRootDrawerController(NULL)
{
    CAApplication::getApplication()->getKeypadDispatcher()->onBackClicked([&]
    {
        if (this->getModalViewController())
        {
            this->dismissModalViewController(true);
        }
        else if (this->getDrawerController()->isShowLeftViewController())
        {
            this->getDrawerController()->hideLeftViewController(true);
        }
        else if (this->getRootNavigationController()->getViewControllerCount() > 1)
        {
            this->getRootNavigationController()->popViewControllerAnimated(true);
        }
        else
        {
            CAApplication::getApplication()->end();
        }
    });
}

RootWindow::~RootWindow()
{
    CAApplication::getApplication()->getKeypadDispatcher()->onBackClicked(nullptr);
}

bool RootWindow::init()
{
    if (!CAWindow::init())
    {
        return false;
    }
    
    CAApplication::getApplication()->setStatusBarStyle(CAStatusBarStyle::LightContent);
    
    CDUIShowAutoCollectionView* viewController = new CDUIShowAutoCollectionView();
    viewController->init();
    viewController->autorelease();
    
    CANavigationBarItem* temp_nav = CANavigationBarItem::create(UTF8("控件展示"));
    CABarButtonItem* item = CABarButtonItem::create("", CAImage::create("image/ic_category_list.png"), NULL);
    item->setCallbackFunction([=]()
    {
        this->getDrawerController()->showLeftViewController(true);
    });
    temp_nav->addLeftButtonItem(item);
    viewController->setNavigationBarItem(temp_nav);
    
    m_pRootNavigationController = new CANavigationController();
    m_pRootNavigationController->initWithRootViewController(viewController);

    MenuViewController* _menuview = MenuViewController::create();
    
    CADrawerController* drawer = new CADrawerController();
    drawer->initWithController(_menuview, m_pRootNavigationController);
    drawer->setBackgroundImage(CAImage::create("image/bg.jpg"));
    drawer->setEffect3D(true);
    
    this->setRootViewController(drawer);
    drawer->autorelease();
    
    m_pRootDrawerController = drawer;
    CAApplication::getApplication()->setNotificationView(NULL);

    return true;
}

