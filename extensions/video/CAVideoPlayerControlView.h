//
//  CAVideoPlayerControlView.h
//  CrossApp
//
//  Created by zhujian on 15-9-16.
//
//  Copyright (c) 2015年 http://www.9miao.com. All rights reserved.
//

#ifndef __CrossApp__CAVideoPlayerControlView__
#define __CrossApp__CAVideoPlayerControlView__

#include "CAVideoPlayerView.h"

NS_CC_EXT_BEGIN


class CAVideoPlayerControlView;
class CAVideoPlayerControlViewDelegate
{
public:
	virtual ~CAVideoPlayerControlViewDelegate(){};

	virtual void onBackButtonClicked(CAVideoPlayerControlView *playerControlView) {};
};

class CC_EXT_DLL CAVideoPlayerControlView: public CAView
{
public:
	CAVideoPlayerControlView();
	virtual ~CAVideoPlayerControlView();

	static CAVideoPlayerControlView* createWithFrame(const DRect& rect);
	static CAVideoPlayerControlView* createWithCenter(const DRect& rect);
    static CAVideoPlayerControlView* createWithLayout(const DLayout& layout);
    
	CC_SYNTHESIZE(std::string, m_szTitle, Title);
	CC_PROPERTY(bool, m_bShowBackButton, ShowBackButton);
	CC_SYNTHESIZE(CAVideoPlayerControlViewDelegate*, m_pPlayerControlViewDelegate, PlayerControlViewDelegate);
	void setPlayerViewDelegate(CAVideoPlayerViewDelegate* var);
	
	void setFullPath(const std::string& szPath);
	void setUrl(const std::string& szUrl);

protected:
	virtual bool init();

	void updatePlayUI(float t);
	void buildCtrlViews();
	void updatePlayButton();
	std::string formatTimeInterval(float seconds, bool isLeft);

private:
	CAVideoPlayerView *m_glView;
	CAButton *m_playButton;
	CAButton *m_backButton;
	CASlider *m_playSlider;
	CALabel *m_playTimeLabel;
    
    bool m_bPlaying;
    bool m_bChanged;
};

NS_CC_EXT_END

#endif /* defined(__CrossApp__CAVideoPlayerControlView__) */
