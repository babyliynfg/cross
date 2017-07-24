/**
 * Created by crossApp on 16/8/4.
 */
var AVPlayerViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
    },
    viewDidLoad: function() {
        var avplayer = ca.CAAVPlayer.createWithUrl("http://download.3g.joy.cn/video/236/60236937/1451280942752_hd.mp4");
        //var avplayer = ca.CAAVPlayer.createWithFilePath("/sdcard/abc.mp4");

        avplayer.onDidPlayToEndTime(function ()
        {
            avplayer.stop();
        });

        //avplayer.onTimeJumped(function ()
        //{
        //    ca.log("进度调整");
        //});

        var playerView = ca.CAAVPlayerView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayoutFill, ca.DVerticalLayout_T_H(0, 640)));
        playerView.setPlayer(avplayer);
        this.getView().addSubview(playerView);

        playerView.insertSubview(ca.CAView.createWithLayout(ca.DLayoutFill, ca.CAColor4B.BLACK), -1);


        var slider = ca.CASlider.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(50, 50), ca.DVerticalLayout_B_H(200, 100)));
        slider.setValue(0);
        slider.setZOrder(100);
        this.getView().addSubview(slider);
        slider.setMaxTrackTintImage(ca.CAImage.CLEAR_IMAGE());
        slider.setTargetForTouchUpSide(function (value)
        {
            var current = value * avplayer.getDuration();
            avplayer.setCurrentTime(current);
        });
         //avplayer.onPeriodicTime(function (current, duration)
         //{
         //    slider.setValue(current / duration);
         //});

        var progress = ca.CAProgress.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(3, 3), ca.DVerticalLayoutFill));
        progress.setProgress(0);
        progress.setZOrder(-1);
        slider.addSubview(progress);
        progress.setProgressTintImage(progress.getProgressTrackImage());
        progress.setProgressTintColor(ca.CAColor4B.RED);
        progress.setProgressTrackColor(ca.CAColor4B.YELLOW);
         //avplayer.onLoadedTime(function( current, duration)
         //{
         //    progress.setProgress(current / duration);
         //});


        var btn0 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
        btn0.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(100, 120), ca.DVerticalLayout_B_H(100, 60)));
        btn0.setTitleForState(ca.CAControl.State.Normal, "播放");
        this.getView().addSubview(btn0);
        btn0.setZOrder(100);
        btn0.addTarget(function()
        {
            var title = btn0.getTitleForState(ca.CAControl.State.Normal);
            if (title == "播放")
            {
                avplayer.play();
            }
            else if (title == "暂停")
            {
                avplayer.pause();
            }

        }, ca.CAButton.Event.TouchUpInSide);


        avplayer.onPlayState(function(state)
        {
            if (state == ca.CAAVPlayer.PlayStatePlaying)
            {
                btn0.setTitleForState(ca.CAControl.State.Normal, "暂停");
            }
        else if (state == ca.CAAVPlayer.PlayStatePause)
            {
                btn0.setTitleForState(ca.CAControl.State.Normal, "播放");
            }
        });

        var btn2 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
        btn2.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(250, 120), ca.DVerticalLayout_B_H(100, 60)));
        btn2.setTitleForState(ca.CAControl.State.Normal, "停止");
        this.getView().addSubview(btn2);
        btn2.setZOrder(100);
        btn2.addTarget(function()
        {
            avplayer.stop();
        }, ca.CAButton.Event.TouchUpInSide);

        var activity = ca.CAActivityIndicatorView.createWithLayout(ca.DLayoutFill);
        playerView.addSubview(activity);
         avplayer.onPlayBufferLoadingState(function(state)
         {
             if (state == ca.CAAVPlayer.PlaybackBufferEmpty)
             {
                 activity.startAnimating();
             }
         else if (state == ca.CAAVPlayer.PlaybackLikelyToKeepUp)
             {
                 activity.stopAnimating();
             }
         });

    },

});