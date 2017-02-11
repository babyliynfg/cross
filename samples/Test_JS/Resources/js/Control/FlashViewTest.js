/**
 * Created by zhanglei on 16/8/3.
 */
var FlashViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
        this.getView().setColor(ca.color._getGray());
        var swfBg = ca.CAFlashView.createWithFlash(ca.CAFlash.createWithFilePath("image/swfWK.swf"));

        swfBg.setLayout(DLayout(DHorizontalLayout_L_R(150, 150), DVerticalLayout_T_B(200, 200)));
        swfBg.runAnimation();
        swfBg.setRepeatForever(true);
        this.getView().addSubview(swfBg);
    },
});