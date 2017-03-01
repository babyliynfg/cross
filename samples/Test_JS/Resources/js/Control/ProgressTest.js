/**
 * Created by zhanglei on 16/8/3.
 */




var ProgressTest = ca.CAViewController.extend({
    progress_value:null,
    progress:null,
    Tview:null,
    ctor: function () {
        this._super();
        this.getView().setColor(ca.color._getGray());

        this.progress_value = ca.CALabel.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(300, 50)));
        this.progress_value.setTag(100);
        this.progress_value.setText("");
        this.progress_value.setFontSize(30);
        this.progress_value.setColor(ca.color(51, 204, 255, 255));
        this.progress_value.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
        this.progress_value.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
        this.getView().addSubview(this.progress_value);

        this.progress = ca.CAProgress.create();
        this.progress.setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(550, 0)));
        //開啟定時函數，一定要做釋放
        ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this,this.progressValueChange,0.01);
        this.getView().addSubview(this.progress);
    },
    viewOnExitTransitionDidStart:function()
    {
        log("viewOnExitTransitionDidStart------>");
        //一定要在這裡手動釋放
        ca.CAScheduler.getScheduler().unscheduleCallbackForTarget(this,this.progressValueChange);
    },
    viewOnSizeTransitionDidChanged:function()
    {
        log("viewOnSizeTransitionDidChanged------>");
    },
    viewOnEnterTransitionDidFinish:function() {
        log("viewOnEnterTransitionDidFinish------>");
    },
    progressValueChange: function (dt) {
        var currentValue = this.progress.getProgress() + 0.001;
        this.progress.setProgress(currentValue);
        var valueText = currentValue*100-0.1;
        this.progress_value.setText(valueText.toFixed(1));
        if(null == this.progress){
            ca.CAScheduler.getScheduler().unscheduleCallbackForTarget(this,this.progressValueChange);
        }
    }
});
