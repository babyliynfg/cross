
#include "WebViewTest.h"

WebViewTest::WebViewTest()
{
}

WebViewTest::~WebViewTest()
{
}

void WebViewTest::viewDidLoad()
{
    this->getView()->setColor(CAColor4B::GRAY);
    
    CAWebView* web = CAWebView::createWithLayout(DLayoutFill);
    web->loadURL("http://crossapp.9miao.com");
    this->getView()->addSubview(web);
}

void WebViewTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

