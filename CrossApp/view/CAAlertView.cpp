
#include "CAAlertView.h"
#include "view/CAScale9ImageView.h"
#include "basics/CAApplication.h"
#include "basics/CASTLContainer.h"
#include "control/CAButton.h"
#include "dispatcher/CATouch.h"
#include "view/CAWindow.h"
#include "view/CARenderImage.h"
#include "animation/CAViewAnimation.h"
#include "platform/CADensityDpi.h"
#include "support/CAThemeManager.h"
#include "support/ccUtils.h"
NS_CC_BEGIN

static CAVector<CAAlertView*> s_vAlertViewCaches;

CAAlertView::CAAlertView()
: m_pContentLabel(NULL)
, m_pTitleLabel(NULL)
, m_pCAlertBtnEvent(NULL)
, m_pCAlertTarget(NULL)
, m_pBtnTableView(NULL)
, m_sMsgFontName("")
, m_fAlertViewHeight(0.0f)
, m_fAlertViewTitleHeight(0.0f)
, m_fAlertViewMessageHeight(0.0f)
{
    
}


CAAlertView::~CAAlertView()
{
    CC_SAFE_RELEASE_NULL(m_pTitleLabel);
    CC_SAFE_RELEASE_NULL(m_pContentLabel);
    CC_SAFE_RELEASE_NULL(m_pBtnTableView);
}

bool CAAlertView::init()
{
    if (!CAView::init())
    {
        return false;
    }
    
    this->setColor(ccc4(0, 0, 0, 66));
    this->setLayout(DLayoutFill);
    
    return true;
}

CAAlertView *CAAlertView::create()
{
    CAAlertView *pAlert = new CAAlertView();
    if (pAlert && pAlert->init())
    {
        pAlert->autorelease();
        return pAlert;
    }
    CC_SAFE_DELETE(pAlert);
    return pAlert;
}

bool CAAlertView::initWithText(const char* szTitle, const char* szAlertMsg, const char* pszBtnText, ...)
{
    if (!this->init())
    {
        return false;
    }
    
    va_list args;
    va_start(args, pszBtnText);
    
    addButton(pszBtnText);
    const char* pszText = va_arg(args, const char*);
    while (pszText)
    {
        addButton(pszText);
        pszText = va_arg(args, const char*);
    }
    va_end(args);
    
    setTitle(szTitle, CAColor_black);
    setAlertMessage(szAlertMsg);
    return true;
}


CAAlertView *CAAlertView::createWithText(const char* pszTitle, const char* pszAlertMsg, const char* pszBtnText, ...)
{
    va_list args;
    va_start(args, pszBtnText);
    
    CAAlertView *pAlert = new CAAlertView();
    if (pAlert && pAlert->init())
    {
        pAlert->addButton(pszBtnText);
        const char* pszText = va_arg(args, const char*);
        while (pszText)
        {
            pAlert->addButton(pszText);
            pszText = va_arg(args, const char*);
        }
        va_end(args);
        
        pAlert->setTitle(pszTitle, CAColor_black);
        pAlert->setAlertMessage(pszAlertMsg);
        
        pAlert->autorelease();
        return pAlert;
    }
    CC_SAFE_DELETE(pAlert);
    return NULL;
}

bool CAAlertView::hideWithDisplayed()
{
    if (!s_vAlertViewCaches.empty())
    {
        s_vAlertViewCaches.back()->hide();
        return true;
    }
    return false;
}

void CAAlertView::setMessageFontName(std::string &var)
{
    CC_RETURN_IF(m_pContentLabel == NULL);
    if (m_sMsgFontName.compare(var))
    {
        m_sMsgFontName = var;
        m_pContentLabel->setFontName(m_sMsgFontName.c_str());
    }
}

void CAAlertView::setTitle(std::string var, CAColor4B col)
{
    CC_RETURN_IF(var.compare("") == 0);
    setLabel(m_pTitleLabel, var.c_str(),"", col);
}

void CAAlertView::setAlertMessage(std::string var, CAColor4B col)
{
    CC_RETURN_IF(var.compare("") == 0);
    setLabel(m_pContentLabel, var.c_str(), m_sMsgFontName.c_str(), col);
    m_pContentLabel->setTextAlignment(CATextAlignmentCenter);
}

void CAAlertView::addButton(const std::string& btnText, CAColor4B col, CAImage* pNormalImage, CAImage* pHighlightedImage)
{
    CAButton* btn = CAButton::create(CAButton::Type::Custom);
    CCAssert(btn, "");
    btn->setTitleForState(CAControl::State::Normal, btnText.c_str());
    btn->setTitleColorForState(CAControl::State::Normal, col);
    if (pNormalImage == NULL)
    {
        btn->setBackgroundViewForState(CAControl::State::Normal, CAView::createWithColor(CAColor_clear));
        
    } else {
        
        btn->setBackgroundViewForState(CAControl::State::Normal, CAScale9ImageView::createWithImage(pNormalImage));
    }
    
    if (pHighlightedImage == NULL)
    {
        btn->setBackgroundViewForState(CAControl::State::Highlighted, CAView::createWithColor(ccc4(206, 206, 211, 255)));
        
    } else {
        
        btn->setBackgroundViewForState(CAControl::State::Highlighted, CAScale9ImageView::createWithImage(pHighlightedImage));
    }
    
    addButton(btn);
}

void CAAlertView::addButton(CAButton* pBtn)
{
    CCAssert(pBtn , "");
    m_vAllBtn.pushBack(pBtn);
    pBtn->setTextTag("btn");
    pBtn->setTag((int)m_vAllBtn.size() - 1);
    pBtn->addTarget([=](CAButton* btn){
    
        CC_RETURN_IF(m_bRunning == false);
        if (m_pCAlertBtnEvent && m_pCAlertTarget)
        {
            ((CAObject*)m_pCAlertTarget->*m_pCAlertBtnEvent)(btn->getTag());
        }
        
        this->hide();
        
    }, CAButton::Event::TouchUpInSide);
}


void CAAlertView::setLabel(CALabel*& pLabel, const char* szTitle, const char* fontName, const CAColor4B& col)
{
    if (pLabel == NULL)
    {
        pLabel = new CALabel();
        CC_RETURN_IF(pLabel == NULL);
        pLabel->init();
        pLabel->setTextAlignment(CATextAlignmentCenter);
        pLabel->setVerticalTextAlignmet(CAVerticalTextAlignmentTop);
        pLabel->setFontName(fontName);
        pLabel->setFontSize(ALERT_VIEW_MESG_FONT);
    }
    pLabel->setText(szTitle);
    pLabel->setColor(col);
}

void CAAlertView::showAlertView() {
    
    calcuAlerViewSize();
    
    DSize winSize = this->getBounds().size;
    
    m_pScale9BackView = CAScale9ImageView::createWithLayout(DLayout(DHorizontalLayout_W_C(ALERT_VIEW_WIDTH, 0.5f), DVerticalLayout_H_C(m_fAlertViewHeight, 0.5f)));
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CAAlertView");
    m_pScale9BackView->setImage(CAImage::create(map.at("backgroundView")));
    this->addSubview(m_pScale9BackView);
    
    m_pBackView = CAClippingView::create();
    m_pBackView->setLayout(DLayoutFill);
    m_pScale9BackView->addSubview(m_pBackView);
    m_pBackView->setAlphaThreshold(0.1f);
    m_pBackView->setInverted(true);
    
    m_pBackView->setStencil(m_pScale9BackView->copy());
    
    float alertViewSpaceHeight = 36;
    
    if (m_pTitleLabel && !m_pTitleLabel->getText().empty())
    {
        
        m_pTitleLabel->setFrame(DRect(0, alertViewSpaceHeight , ALERT_VIEW_WIDTH, m_fAlertViewTitleHeight));
        m_pTitleLabel->setFontSize(ALERT_VIEW_TITLE_FONT);
        m_pTitleLabel->setBold(true);
        m_pBackView->addSubview(m_pTitleLabel);
    }
    
    float alertViewMessageHeight = 140;
    
    if (m_fAlertViewMessageHeight > alertViewMessageHeight)
    {
        
        CAScrollView *scrollView = CAScrollView::createWithFrame(DRect(
                                                                       0 , 0, ALERT_VIEW_WIDTH, m_fAlertViewLineHeight - alertViewSpaceHeight ));
        scrollView->setBackgroundColor(CAColor_clear);
        scrollView->setShowsHorizontalScrollIndicator(false);
        scrollView->setShowsVerticalScrollIndicator(true);
        scrollView->setBounceHorizontal(false);
        scrollView->setViewSize(DSize(ALERT_VIEW_MESG_WIDTH, alertViewSpaceHeight + m_fAlertViewMessageHeight + m_fAlertViewTitleHeight));
        m_pBackView->addSubview(scrollView);
        
        CCAssert(m_pTitleLabel, "");
        if (m_pTitleLabel && !m_pTitleLabel->getText().empty())
        {
            m_pTitleLabel->removeFromSuperview();
            m_pTitleLabel->setFontSize(ALERT_VIEW_TITLE_FONT);
            m_pTitleLabel->setFrame(DRect(0, alertViewSpaceHeight, ALERT_VIEW_WIDTH, m_fAlertViewTitleHeight));
            scrollView->addSubview(m_pTitleLabel);
        }
        
        CCAssert(m_pContentLabel, "");
        m_pContentLabel->setFrame(DRect((ALERT_VIEW_WIDTH - ALERT_VIEW_MESG_WIDTH) / 2, alertViewSpaceHeight + 10 + m_fAlertViewTitleHeight, ALERT_VIEW_MESG_WIDTH, m_fAlertViewMessageHeight));
        scrollView->addSubview(m_pContentLabel);
        
    }
    else if (m_pContentLabel)
    {
        alertViewMessageHeight = m_fAlertViewMessageHeight;
        m_pContentLabel->setFrame(DRect((ALERT_VIEW_WIDTH - ALERT_VIEW_MESG_WIDTH) / 2, alertViewSpaceHeight + 10 + m_fAlertViewTitleHeight, ALERT_VIEW_MESG_WIDTH, m_fAlertViewMessageHeight));
        m_pBackView->addSubview(m_pContentLabel);
    }
    
    addGrayLine(m_fAlertViewLineHeight);
    
    adjustButtonView();
}

void CAAlertView::adjustButtonView() {
    
    float alertViewButtonHeight = 88;
    
    size_t btnCount = m_vAllBtn.size();
    
    CC_RETURN_IF(btnCount <= 0);
    
    if (btnCount == 1) {
        
        m_vAllBtn.at(0)->setFrame(DRect(0, m_fAlertViewLineHeight, ALERT_VIEW_WIDTH, alertViewButtonHeight));
        
        m_pBackView->addSubview(m_vAllBtn.at(0));
        
    } else if (btnCount == 2) {
        
        CAView *line = createWithFrame(DRect(ALERT_VIEW_WIDTH / 2, m_fAlertViewLineHeight, LINE_WIDTH, alertViewButtonHeight));
        line->setColor(ccc4(206, 206, 211, 255));
        m_pBackView->addSubview(line);
        
        for (int i = 0; i < btnCount; i++) {
            m_vAllBtn.at(i)->setFrame(DRect(ALERT_VIEW_WIDTH / 2 * i, m_fAlertViewLineHeight, ALERT_VIEW_WIDTH / 2, alertViewButtonHeight));
            m_pBackView->addSubview(m_vAllBtn.at(i));
        }
        
    } else if (btnCount == 3) {
        
        for (int i = 0; i < btnCount; i++) {
            addGrayLine(m_fAlertViewLineHeight + alertViewButtonHeight * i);
            
            m_vAllBtn.at(i)->setFrame(DRect(0, m_fAlertViewLineHeight + alertViewButtonHeight * i, ALERT_VIEW_WIDTH, alertViewButtonHeight));
            m_pBackView->addSubview(m_vAllBtn.at(i));
        }
        
    } else {
        
        m_pBtnTableView = new CATableView();
        CCAssert(m_pBtnTableView != NULL, "");
        m_pBtnTableView->init();
        m_pBtnTableView->setFrame(DRect(0,m_fAlertViewLineHeight,ALERT_VIEW_WIDTH,alertViewButtonHeight * 3));
        m_pBtnTableView->setBackgroundColor(CAColor_clear);
        m_pBtnTableView->setTableViewDataSource(this);
        m_pBtnTableView->setTableViewDelegate(this);
        m_pBtnTableView->setAllowsSelection(true);
        m_pBtnTableView->setSeparatorColor(ccc4(206, 206, 211, 255));
        m_pBackView->addSubview(m_pBtnTableView);
        
    }
}

void CAAlertView::addGrayLine(int y) {
    
    CCAssert(y, "");
    CAView *line = createWithFrame(DRect(0, y, ALERT_VIEW_WIDTH, LINE_WIDTH));
    line->setColor(ccc4(206, 206, 211, 255));
    m_pBackView->addSubview(line);
}

void CAAlertView::calcuAlerViewSize()
{
    float alertViewSpaceHeight = 36;
    
    float alertViewButtonHeight = 88;
    
    float alertViewMessageHeight = 140;
    
    m_fAlertViewHeight += alertViewSpaceHeight;
    
    if (m_pTitleLabel && !m_pTitleLabel->getText().empty())
    {
        
        m_fAlertViewTitleHeight = CAImage::getFontHeight("", ALERT_VIEW_TITLE_FONT);
        
        m_fAlertViewHeight += m_fAlertViewTitleHeight;
    }
    
    m_fAlertViewHeight += alertViewSpaceHeight / 2;
    
    if (m_pContentLabel && !m_pContentLabel->getText().empty())
    {
        
        m_fAlertViewMessageHeight = CAImage::getStringHeight(m_sMsgFontName.c_str(), ALERT_VIEW_MESG_FONT, m_pContentLabel->getText(), ALERT_VIEW_MESG_WIDTH, 0, false);
        
        m_fAlertViewHeight += MIN(m_fAlertViewMessageHeight, alertViewMessageHeight);
    }
    
    m_fAlertViewHeight += alertViewSpaceHeight;
    
    
    size_t btnCount = m_vAllBtn.size();
    CCAssert(btnCount,"");
    
    if (btnCount == 1 || btnCount == 2)
    {
        
        m_fAlertViewHeight += alertViewButtonHeight;
    }
    else
    {
        
        m_fAlertViewHeight += alertViewButtonHeight * 3;
    }
    
    if (m_fAlertViewMessageHeight > alertViewMessageHeight)
    {
        m_fAlertViewLineHeight = alertViewSpaceHeight * 2.5 + m_fAlertViewTitleHeight + alertViewMessageHeight;
    }
    else
    {
        m_fAlertViewLineHeight = alertViewSpaceHeight * 2.5 + m_fAlertViewTitleHeight + m_fAlertViewMessageHeight;
    }
    
}

void CAAlertView::setTarget(CAObject* target, SEL_CAAlertBtnEvent selector)
{
    m_pCAlertTarget = target;
    m_pCAlertBtnEvent = selector;
}

void CAAlertView::show()
{
    CC_RETURN_IF(this->isRunning());
    
    if (CAWindow *rootWindow = CAApplication::getApplication()->getRootWindow())
    {
        rootWindow->insertSubview(this, CAWindowZOrderTop);
        s_vAlertViewCaches.pushBack(this);
    }
    
    showAlertView();
    
    this->setAlpha(0);
    m_pScale9BackView->setScale(0.5f);
    CAViewAnimation::beginAnimations("", NULL);
    CAViewAnimation::setAnimationDuration(0.2f);
    CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseOut);
    this->setAlpha(1.0f);
    m_pScale9BackView->setScale(1.0f);
    CAViewAnimation::commitAnimations();
}

void CAAlertView::hide()
{
    s_vAlertViewCaches.eraseObject(this);
    
    CAViewAnimation::beginAnimations("", NULL);
    CAViewAnimation::setAnimationDuration(0.2f);
    CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseIn);
    CAViewAnimation::setAnimationDidStopSelector(this, CAViewAnimation0_selector(CAAlertView::removeFromSuperview));
    this->setAlpha(0.0f);
    m_pScale9BackView->setScale(0.5f);
    CAViewAnimation::commitAnimations();
}

void CAAlertView::setContentSize(const DSize& var)
{
    CAView::setContentSize(var);
    if (this->isRunning())
    {
        this->removeAllSubviews();
        m_fAlertViewHeight = 0;
        this->showAlertView();
    }
}

CATableViewCell* CAAlertView::tableCellAtIndex(CATableView* table, const DSize& cellSize, unsigned int section, unsigned int row)
{
    CATableViewCell* cell = table->dequeueReusableCellWithIdentifier("cellID");
    if (cell == NULL)
    {
        cell = CATableViewCell::create("cellID");
    }
    cell->removeSubviewByTextTag("btn");
    m_vAllBtn.at(row)->removeFromSuperview();
    m_vAllBtn.at(row)->setFrame(DRect(0, 0, cellSize.width, cellSize.height));
    cell->addSubview(m_vAllBtn.at(row));
    return cell;
}

unsigned int CAAlertView::numberOfRowsInSection(CATableView *table, unsigned int section)
{
    return (unsigned int)m_vAllBtn.size();
}

unsigned int CAAlertView::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
    return 88;
}

NS_CC_END
