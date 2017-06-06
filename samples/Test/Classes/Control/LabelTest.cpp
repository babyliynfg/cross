
#include "LabelTest.h"
#include "CDUIShowAutoCollectionView.h"

int LabelNum = 0;

LabelTest::LabelTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

LabelTest::~LabelTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
    LabelNum = 0;
}

void CDUIShowAutoCollectionView::LabelRightBtnRightcallback(CAButton* btn)
{
    if (showLabelNavigationBar >= 2)
    {
        showLabelNavigationBar = 0;
        
        LabelNum = showLabelNavigationBar;
    }
    else
    {
        LabelNum = ++showLabelNavigationBar;
    }
    
    LabelTest* ViewContrllerLabelTest = new LabelTest();
    ViewContrllerLabelTest->init();
    ViewContrllerLabelTest->setNavigationBarItem(LabelNavigationBar);
    ViewContrllerLabelTest->autorelease();
    RootWindow::getInstance()->getRootNavigationController()->replaceViewController(ViewContrllerLabelTest, false);
}

void LabelTest::viewDidLoad()
{
	std::string s = "Hello World";

	std::u32string c;
	StringUtils::UTF8ToUTF32(s, c);
	c += 0x1F604;

	std::string cc;
	StringUtils::UTF32ToUTF8(c, cc);

	if (LabelNum == 0)
	{
        CAView* view = CAView::createWithLayout(DLayoutFill);
        view->setColor(CAColor4B::GRAY);
        this->getView()->addSubview(view);
        
		CAFont Font;
		Font.fontSize = 36;
		Font.color = CAColor4B::RED;
        Font.textAlignment = CATextAlignment::Center;
        Font.verticalTextAlignment = CAVerticalTextAlignment::Center;

		CALabel* label = CALabel::create();
		label->setText(cc);
		label->setFont(Font);
		label->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 1/8.f)));
        view->addSubview(label);
        

		CAFont Font1;
		Font1.fontSize = 36;
		Font1.color = CAColor4B::RED;
        Font1.textAlignment = CATextAlignment::Center;
        Font1.verticalTextAlignment = CAVerticalTextAlignment::Center;
        Font1.bold = true;
        
        CALabel* label1 = CALabel::create();
		label1->setText(cc);
		label1->setFont(Font1);
		label1->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 2/8.f)));
        view->addSubview(label1);
        
        
		CALabel* label2 = CALabel::create();
		CAFont Font2;
		Font2.fontSize = 36;
		Font2.color = CAColor4B::RED;
        Font2.textAlignment = CATextAlignment::Center;
        Font2.verticalTextAlignment = CAVerticalTextAlignment::Center;
		Font2.underLine = true;
        
		label2->setText(cc);
		label2->setFont(Font2);
		label2->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 3/8.f)));
        view->addSubview(label2);
        

		CALabel* label3 = CALabel::create();
		CAFont Font3;
		Font3.fontSize = 36;
		Font3.color = CAColor4B::RED;
        Font3.textAlignment = CATextAlignment::Center;
        Font3.verticalTextAlignment = CAVerticalTextAlignment::Center;
        Font3.deleteLine = true;
        
		label3->setText(cc);
		label3->setFont(Font3);
		label3->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 4/8.f)));
        view->addSubview(label3);
        

		CALabel* label4 = CALabel::create();
		CAFont Font4;
		Font4.fontSize = 36;
		Font4.color = CAColor4B::RED;
        Font4.textAlignment = CATextAlignment::Center;
        Font4.verticalTextAlignment = CAVerticalTextAlignment::Center;
        Font4.italics = true;
        
		label4->setText(cc);
		label4->setFont(Font4);
		label4->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 5/8.f)));
        view->addSubview(label4);
        
        CALabel* label5 = CALabel::create();
        CAFont Font5;
        Font5.fontSize = 36;
        Font5.color = CAColor4B::RED;
        Font5.textAlignment = CATextAlignment::Center;
        Font5.verticalTextAlignment = CAVerticalTextAlignment::Center;
        Font5.shadow.shadowEnabled = true;
        Font5.shadow.shadowOffset = DSize(3, -3);
        Font5.shadow.shadowBlur = 2.0f;
        Font5.shadow.shadowColor = CAColor4B(0, 0, 0, 127);
        
        label5->setText(cc);
        label5->setFont(Font5);
        label5->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 6/8.f)));
        view->addSubview(label5);
        
        CALabel* label6 = CALabel::create();
        CAFont Font6;
        Font6.fontSize = 36;
        Font6.color = CAColor4B::CLEAR;
        Font6.textAlignment = CATextAlignment::Center;
        Font6.verticalTextAlignment = CAVerticalTextAlignment::Center;
        Font6.stroke.strokeEnabled = true;
        Font6.stroke.strokeSize = 3;
        Font6.stroke.strokeColor = CAColor4B::RED;
        
        label6->setText(cc);
        label6->setFont(Font6);
        label6->setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 7/8.f)));
        view->addSubview(label6);
	}
	else if (LabelNum == 1)
	{
		CALabel* label5 = CALabel::create();
		CAFont Font5;
		Font5.fontSize = 36;
		Font5.color = CAColor4B::RED;
        Font5.textAlignment = CATextAlignment::Center;
        Font5.verticalTextAlignment = CAVerticalTextAlignment::Center;
		Font5.fontName = "c:/x.ttf";
		Font5.bold = true;
		Font5.italics = true;
		Font5.underLine = true;
		label5->setText("Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World");
		label5->setFont(Font5);
		label5->setLineSpacing(20);
		label5->setLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_H(300, 300)));

		CAView* view1 = CAView::createWithLayout(DLayoutFill);
		view1->addSubview(label5);
		view1->setColor(CAColor4B::GRAY);

		this->getView()->addSubview(view1);
	}
	else
	{

		CARichLabel* RichLabel = CARichLabel::createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_B(200, 200)));
		CAFont RichLabelFont;
		RichLabelFont.bold = true;
		RichLabelFont.fontSize = 42;
		RichLabelFont.color = CAColor4B::RED;
		RichLabel->appendText("Hello World Hello World Hello World Hello World Hello World Hello World ", RichLabelFont);

		CAFont RichLabelFont1;
		RichLabelFont1.italics = true;
		RichLabelFont1.fontSize = 42;
		RichLabelFont1.color = CAColor4B::RED;
		RichLabel->appendText("Hello World Hello World Hello World Hello World Hello World Hello World ", RichLabelFont1);

		CAFont RichLabelFont2;
		RichLabelFont2.underLine = true;
		RichLabelFont2.fontSize = 42;
		RichLabelFont2.color = CAColor4B::RED;
		RichLabel->appendText("Hello World Hello World Hello World Hello World Hello World Hello World ", RichLabelFont2);

		CAView* view2 = CAView::createWithLayout(DLayoutFill);
		view2->addSubview(RichLabel);
		view2->setColor(CAColor4B::GRAY);

		this->getView()->addSubview(view2);
	}
}

void LabelTest::viewDidUnload()
{
}
