
#include "TabBarControllerTest.h"
#include "FirstViewController.h"

TabBarControllerTest::TabBarControllerTest()
{
}

TabBarControllerTest::~TabBarControllerTest()
{
}

void TabBarControllerTest::viewDidLoad()
{
    CATabBarItem* item1 = CATabBarItem::create("item1", CAImage::create(""), CAImage::create(""));
    CATabBarItem* item2 = CATabBarItem::create("item2", CAImage::create(""), CAImage::create(""));
    CATabBarItem* item3 = CATabBarItem::create("item3", CAImage::create(""), CAImage::create(""));

    CAVector<CATabBarItem*> item;
    item.pushBack(item1);
    item.pushBack(item2);
    item.pushBack(item3);
    
    CATabBar* tabBar = CATabBar::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_H_C(98, 0.33)));
    tabBar->setItems(item);
    tabBar->showSelectedIndicator();
    tabBar->setSelectedAtIndex(0);
    tabBar->setTag(100);
    
    CATabBarItem* item4 = CATabBarItem::create("", CAImage::create("image/tab_news_btn_up.png"), CAImage::create("image/tab_news_btn_down.png"));
    CATabBarItem* item5 = CATabBarItem::create("", CAImage::create("image/tab_image_btn_up.png"), CAImage::create("image/tab_image_btn_down.png"));
    CATabBarItem* item6 = CATabBarItem::create("", CAImage::create("image/tab_mine_btn_up.png"), CAImage::create("image/tab_mine_btn_down.png"));
    
    CAVector<CATabBarItem*> it1;
    it1.pushBack(item4);
    it1.pushBack(item5);
    it1.pushBack(item6);
    
    CATabBar* tabBar1 = CATabBar::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_H_C(98, 0.66)));
    tabBar1->setBackgroundImage(CAImage::create("image/tab_news_bg.png"));
    tabBar1->setSelectedBackgroundImage(nullptr);
    tabBar1->setItems(it1);
    tabBar1->setTag(100);
    tabBar1->setSelectedAtIndex(0);
    
    CAView* view1 = CAView::createWithLayout(DLayoutFill);
    view1->addSubview(tabBar);
    view1->addSubview(tabBar1);
    view1->setColor(CAColor4B::GRAY);
    this->getView()->addSubview(view1);
    

}

void TabBarControllerTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

