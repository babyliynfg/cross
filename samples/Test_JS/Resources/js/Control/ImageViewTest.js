/**
 * Created by zhanglei on 16/8/2.
 */
var ImageViewTest = ca.CAViewController.extend({
    imageViewNum:0,
    maxNum:4,
    ctor: function (num) {
        this._super();
        this.imageViewNum = num;
        this.initImageView();
    },
    initImageView:function(){
        this.getView().removeAllSubviews();

        if (this.imageViewNum == 0)
        {
            var image1 = ca.CAImageView.createWithImage(ca.CAImage.create("image/h1.png"));
            image1.setLayout(DLayoutFill);

            var view1 = ca.CAView.createWithLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_B(50, 50)));
            view1.addSubview(image1);
            view1.setColor(ca.color._getGray());
            this.getView().addSubview(view1);
        }
        else if (this.imageViewNum == 1)
        {
            var image2 = ca.CAImageView.createWithLayout(DLayoutFill);

            image2.setImage(ca.CAImage.create("image/h1.png"));
            image2.setScaleType(ca.CAImageViewScaleType.CAImageViewScaleTypeFitImageXY);
            var view2 = ca.CAView.createWithLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_B(50, 50)));
            view2.addSubview(image2);
            view2.setColor(ca.color._getGray());
            this.getView().addSubview(view2);
        }
        else if (this.imageViewNum == 2)
        {
            var image3 = ca.CAImageView.createWithLayout(DLayoutFill);
            image3.setImage(ca.CAImage.create("image/h1.png"));
            image3.setScaleType(ca.CAImageViewScaleType.CAImageViewScaleTypeFitImageCrop);

            var view3 = ca.CAView.createWithLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_B(50, 50)));
            view3.addSubview(image3);
            view3.setColor(ca.color._getGray());
            this.getView().addSubview(view3);
        }
        else if (this.imageViewNum == 3)
        {
            var image4 = ca.CAImageView.createWithLayout(DLayoutFill);
            image4.setImage(ca.CAImage.create("image/h1.png"));
            image4.setScaleType(ca.CAImageViewScaleType.CAImageViewScaleTypeFitImageInside);


            var view4 = ca.CAView.createWithLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_B(50, 50)));
            view4.addSubview(image4);
            view4.setColor(ca.color._getGray());
            this.getView().addSubview(view4);
        }
        else if (this.imageViewNum == 4)
        {
            var img = new Array(3);
            for (var i=0; i<8; i++)
            {

                var str = "animation/npc_382-"+ (i+1) +".png";
                img[i] = ca.CAImage.create(str);
            }
            var image7 = ca.CAImageView.createWithImage(ca.CAImage.create("animation/npc_382-1.png"));
            image7.setLayout(DLayoutFill);
            image7.setAnimationImages(img);
            image7.setAnimationDuration(0.1);
            image7.startAnimating();

            var view7 = ca.CAView.createWithLayout(DLayout(DHorizontalLayout_L_R(350, 350), DVerticalLayout_T_B(650, 650)));
            view7.addSubview(image7);
            view7.setColor(ca.color._getGray());
            this.getView().addSubview(view7);
        }

        var btn = ca.CAButton.createWithFrame(ca.rect(100, 100, 100, 30), 1);
        //btn.setTitleForState(0, "Button");
        //btn.addTarget(this, this.btncallback, 0);
        //this.getView().addSubview(btn);
    },
    btncallback: function (btn, point)
    {
        ++this.imageViewNum;

        if(this.imageViewNum > 4)
        {
            this.imageViewNum=0;
        }
        this.initImageView();
    }
});
