
#include "AVPlayerViewTest.h"

AVPlayerViewTest::AVPlayerViewTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

AVPlayerViewTest::~AVPlayerViewTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
}

void AVPlayerViewTest::viewDidLoad()
{
    CAAVPlayer* avplayer = CAAVPlayer::createWithUrl("http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4");
    //CAAVPlayer* avplayer = CAAVPlayer::createWithUrl("http://download.3g.joy.cn/video/236/60236937/1451280942752_hd.mp4");

    avplayer->onDidPlayToEndTime([=]
    {
        avplayer->stop();
    });
    avplayer->onTimeJumped([=]
    {
        CCLog("进度调整");
    });
    
    CAAVPlayerView* playerView = CAAVPlayerView::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H(0, 640)));
    playerView->setPlayer(avplayer);
    this->getView()->addSubview(playerView);
    
    playerView->insertSubview(CAView::createWithLayout(DLayoutFill, CAColor4B::BLACK), -1);
    

    CASlider* slider = CASlider::createWithLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_B_H(200, 100)));
    slider->setValue(0);
    slider->setZOrder(100);
    this->getView()->addSubview(slider);
    slider->setMaxTrackTintImage(CAImage::CLEAR_IMAGE());
    slider->setTarget([=](float var)
    {
        float current = var * avplayer->getDuration();
        avplayer->setCurrentTime(current);
    });
    avplayer->onPeriodicTime([=](float current, float duration)
    {
        slider->setValue(current / duration);
    });
    
    CAProgress* progress = CAProgress::createWithLayout(DLayout(DHorizontalLayout_L_R(3, 3), DVerticalLayoutFill));
    progress->setProgress(0);
    progress->setZOrder(-1);
    slider->addSubview(progress);
    progress->setProgressTintImage(progress->getProgressTrackImage());
    progress->setProgressTintColor(CAColor4B::RED);
    progress->setProgressTrackColor(CAColor4B::YELLOW);
    avplayer->onLoadedTime([=](float current, float duration)
    {
        progress->setProgress(current / duration);
    });
    

    CAButton* btn0 = CAButton::create(CAButton::Type::RoundedRect);
    btn0->setLayout(DLayout(DHorizontalLayout_L_W(100, 120), DVerticalLayout_B_H(100, 60)));
    btn0->setTitleForState(CAControl::State::Normal, "播放");
    this->getView()->addSubview(btn0);
    btn0->setZOrder(100);
    btn0->addTarget([=]
    {
        const std::string& title = btn0->getTitleForState(CAControl::State::Normal);
        if (title.compare("播放") == 0)
        {
            avplayer->play();
        }
        else if (title.compare("暂停") == 0)
        {
            avplayer->pause();
        }
        
    }, CAButton::Event::TouchUpInSide);
    

    avplayer->onPlayState([=](const CAAVPlayer::PlayState& var)
    {
        if (var == CAAVPlayer::PlayStatePlaying)
        {
            btn0->setTitleForState(CAControl::State::Normal, "暂停");
        }
        else if (var == CAAVPlayer::PlayStatePause)
        {
            btn0->setTitleForState(CAControl::State::Normal, "播放");
        }
    });
    
    CAButton* btn2 = CAButton::create(CAButton::Type::RoundedRect);
    btn2->setLayout(DLayout(DHorizontalLayout_L_W(250, 120), DVerticalLayout_B_H(100, 60)));
    btn2->setTitleForState(CAControl::State::Normal, "停止");
    this->getView()->addSubview(btn2);
    btn2->setZOrder(100);
    btn2->addTarget([=]
    {
        avplayer->stop();
    }, CAButton::Event::TouchUpInSide);
    
    
    CAActivityIndicatorView* activity = CAActivityIndicatorView::createWithLayout(DLayoutFill);
    playerView->addSubview(activity);
    
    avplayer->onPlayBufferLoadingState([=](const CAAVPlayer::PlayBufferLoadingState& var)
    {
        if (var == CAAVPlayer::PlaybackBufferEmpty)
        {
            activity->startAnimating();
        }
        else if (var == CAAVPlayer::PlaybackLikelyToKeepUp)
        {
            activity->stopAnimating();
        }
    });
}

void AVPlayerViewTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

