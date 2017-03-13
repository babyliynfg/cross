/**
 * Created by zhanglei on 16/8/3.
 */
var GifViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
        this.getView().setColor(ca.color._getGray());
        var GifView = ca.CAGifView.createWithGif(ca.CAGif.create("image/gifview1.gif"));
        GifView.setLayout(DLayout(DHorizontalLayout_W_C(400, 0.5), DVerticalLayout_H_C(400, 0.5)));
        //设置Gif永远重复
        GifView.setRepeatForever(true);
        //查看Gif是否永远重复
        log("isRepeatForever =" + GifView.isRepeatForever());

        //设置Frame
        //GifView.setFrame(ca.rect(this.getView().getBounds()));
        //设置Center
        //GifView.setCenter(ca.rect(this.getView().getBounds()));
        //设置Times
        //GifView.setTimes(10.00);
        //初始化
        //GifView.init();
        //初始化指定Gif
        //GifView.initWithGif(ca.CAGif.createWithFilePath("image/gifview1.gif"));
        //设置Gif
        //GifView.setGif(ca.CAGif.createWithFilePath("image/gifview1.gif"));

        this.getView().addSubview(GifView);
    },
});