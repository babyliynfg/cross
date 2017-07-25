
#include "WebViewTest.h"

WebViewTest::WebViewTest()
{
    this->setTitle("CAWebView");
}

WebViewTest::~WebViewTest()
{
}

void WebViewTest::viewDidLoad()
{
    this->getView()->setColor(CAColor4B::GRAY);
    
    CAWebView* web = CAWebView::createWithLayout(DLayoutFill);
    web->loadURL("http://www.baidu.com");
    this->getView()->addSubview(web);
}

void WebViewTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

