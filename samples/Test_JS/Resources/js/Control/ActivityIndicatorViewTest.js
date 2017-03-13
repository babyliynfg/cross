/**
 * Created by zhanglei on 16/8/15.
 */
var ActivityIndicatorViewTest = ca.CAViewController.extend({
    myView:null,
    ActivityIndicatorNum:0,
    maxNum:4,
    ctor: function (num) {
        this._super();
        log('ActivityIndicatorViewTest-->num:'+num);
        this.ActivityIndicatorNum = num;
        if (this.ActivityIndicatorNum == 0)
        {
            var idc1 = ca.CAActivityIndicatorView.createWithLayout(DLayoutFill);
            idc1.setStyle(ca.CAActivityIndicatorView.Style.WhiteLarge);
            idc1.startAnimating();

            var view1 = ca.CAView.createWithLayout(DLayoutFill);
            view1.addSubview(idc1);
            view1.setColor(ca.color._getGray());
            this.getView().addSubview(view1);
        }
        else if (this.ActivityIndicatorNum == 1)
        {
            var idc2 = ca.CAActivityIndicatorView.createWithLayout(DLayoutFill);
            idc2.setStyle(ca.CAActivityIndicatorView.Style.GrayLarge);
            idc2.startAnimating();

            var view2 = ca.CAView.createWithLayout(DLayoutFill);
            view2.addSubview(idc2);
            view2.setColor(ca.color._getGray());
            this.getView().addSubview(view2);
        }
        else if (this.ActivityIndicatorNum == 2)
        {
            var idc3 = ca.CAActivityIndicatorView.createWithLayout(DLayoutFill);
            idc3.setStyle(ca.CAActivityIndicatorView.Style.White);
            idc3.setCycleTime(1.0);
            idc3.setTimesOneCycle(12);
            idc3.startAnimating();

            var view3 = ca.CAView.createWithLayout(DLayoutFill);
            view3.addSubview(idc3);
            view3.setColor(ca.color._getGray());
            this.getView().addSubview(view3);
        }
        else if (this.ActivityIndicatorNum == 3)
        {
            var idc4 = ca.CAActivityIndicatorView.createWithLayout(DLayoutFill);
            idc4.setStyle(ca.CAActivityIndicatorView.Style.Gray);
            idc4.setCycleTime(1.0);
            idc4.setTimesOneCycle(12);
            idc4.startAnimating();

            var view4 = ca.CAView.createWithLayout(DLayoutFill);
            view4.addSubview(idc4);
            view4.setColor(ca.color._getGray());
            this.getView().addSubview(view4);
        }
        else if (this.ActivityIndicatorNum == 4)
        {
            var image = ca.CAImage.create("image/indicator2.png");
            var imageView = ca.CAImageView.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_B(100,100)));
            imageView.setFrame(ca.drect(0, 0, 100, 100));
            imageView.setImage(image);

            var idc5 = ca.CAActivityIndicatorView.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_B(100,100)));
            idc5.setStyle(ca.CAActivityIndicatorView.Style.Image);
            idc5.setActivityIndicatorView(imageView);
            //idc5.startAnimating();

            var view5 = ca.CAView.createWithLayout(DLayoutFill);
            view5.addSubview(idc5);
            view5.setColor(ca.color._getGray());
            this.getView().addSubview(view5);
        }


    },

});
