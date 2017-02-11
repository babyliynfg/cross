/**
 * Created by zhanglei on 16/8/8.
 */
var ViewAnimationTest = ca.CAViewController.extend({
    AnimationNum:2,
    animation_2_textfield:null,
    animation_2_btn_cancel:null,
    animation_3_imageview:null,
    animation_1_view:null,
    heart_index:0,
    maxNum:2,
    ctor: function (num) {
        this._super();
        if(num != null){
            this.AnimationNum = num;
        }
        this.getView().setColor(ca.color._getGray());

        var winSize = this.getView().getBounds().size;
        var winRect = this.getView().getBounds();

        if (this.AnimationNum == 0)
        {
            //Animation 1
            this.heart_index = 0;
            var btn1 = ca.CAButton.create(ca.CAButtonType.RoundedRect);
            btn1.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(56, 0.25)));
            btn1.setTitleForState(ca.CAControlState.Normal, "Play Animation");
            btn1.setTitleColorForState(ca.CAControlState.Normal, ca.color(51,204,255,255));
            btn1.setTag(100);
            btn1.addTarget(this, this.doAction, ca.CAControlEvents.TouchUpInSide);
            this.animation_1_view = ca.CAImageView.createWithLayout(DLayout(DHorizontalLayout_W_C(28, 0.5), DVerticalLayout_H_C(24, 0.5)));
            this.animation_1_view.setImage(ca.CAImage.create("image/heart1.png"));

            var view1 = ca.CAView.createWithLayout(DLayoutFill);
            view1.addSubview(btn1);
            view1.addSubview(this.animation_1_view);
            view1.setColor(ca.color._getGray());
            this.getView().addSubview(view1);
        }
        else if (this.AnimationNum == 1)
        {
            //Animation 2
            var bg = ca.CAImageView.createWithLayout(DLayout(DHorizontalLayout_L_R(0, 0), DVerticalLayout_H_C(80, 0.5)));
            bg.setImage(ca.CAImage.create("image/navbg.jpg"));

            this.animation_2_textfield = ca.CATextField.createWithLayout(DLayout(DHorizontalLayout_L_R(90, 90), DVerticalLayout_H_C(50, 0.5)));
            this.animation_2_textfield.setFontSize(40);
            this.animation_2_textfield.setKeyboardType(ca.KeyboardType.Default);
            this.animation_2_textfield.setVisible(false);

            var animation_2_btn_search = ca.CAButton.createWithLayout(DLayout(DHorizontalLayout_L_W(25, 56), DVerticalLayout_H_C(48, 0.5)), ca.CAButtonType.Custom);
            animation_2_btn_search.setImageForState(ca.CAControlState.Normal, ca.CAImage.create("image/search_btn.png"));
            animation_2_btn_search.addTarget(this, this.doAction, ca.CAControlEvents.TouchUpInSide);
            animation_2_btn_search.setTag(201);

            this.animation_2_btn_cancel = ca.CAButton.createWithLayout(DLayout(DHorizontalLayout_R_W(0, 100), DVerticalLayout_H_C(50, 0.5)), ca.CAButtonType.Custom);
            this.animation_2_btn_cancel.setTitleForState(ca.CAControlState.Normal, "Cancel");
            this.animation_2_btn_cancel.setTag(202);
            this.animation_2_btn_cancel.setTitleColorForState(ca.CAControlState.Normal, ca.WHITE);
            this.animation_2_btn_cancel.addTarget(this, this.doAction, ca.CAControlEvents.TouchUpInSide);
            this.animation_2_btn_cancel.setVisible(false);

            var view2 = ca.CAView.createWithLayout(DLayoutFill);
            view2.addSubview(bg);
            view2.addSubview(this.animation_2_textfield);
            view2.addSubview(animation_2_btn_search);
            view2.addSubview(this.animation_2_btn_cancel);
            view2.setColor(ca.color._getGray());
            this.getView().addSubview(view2);
        }
        else if(this.AnimationNum == 2)
        {
            //Animation 3
            this.animation_3_imageview = ca.CAImageView.createWithLayout(DLayoutFill);
            this.animation_3_imageview.setImage(ca.CAImage.create("image/2.jpg"));

            var btn3 = ca.CAButton.create(ca.CAButtonType.RoundedRect);
            btn3.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(56, 0.25)));
            btn3.setTitleForState(ca.CAControlState.Normal, "Play Animation");
            btn3.setTitleColorForState(ca.CAControlState.Normal, ca.color(51,204,255,255));
            btn3.setTag(300);
            btn3.addTarget(this, this.doAction, ca.CAControlEvents.TouchUpInSide);

            var view3 = ca.CAView.createWithLayout(DLayoutFill);
            view3.addSubview(this.animation_3_imageview);
            view3.addSubview(btn3);
            view3.setColor(ca.color._getGray());
            this.getView().addSubview(view3);
        }

    },
    doAction: function( btn, point)
    {
        var button = btn;
        var tag = button.getTag();

        if (tag==100) {
            this.animation_1_view.setScale(1);
            ca.CAViewAnimation.beginAnimations("", 1);
            ca.CAViewAnimation.setAnimationDuration(0.3);
            ca.CAViewAnimation.setAnimationRepeatAutoreverses(true);
            if (this.heart_index==0) {
                this.animation_1_view.setImage(ca.CAImage.create("image/heart2.png"));
                this.heart_index = 1;
            }else{
                this.animation_1_view.setImage(ca.CAImage.create("image/heart1.png"));
                this.heart_index = 0;
            }
            this.animation_1_view.setScale(2);
            ca.CAViewAnimation.commitAnimations();
        }else if (tag==201) {
            this.animation_2_textfield.setVisible(true);
            this.animation_2_btn_cancel.setVisible(false);
            this.animation_2_textfield.setAlpha(0);
            this.animation_2_textfield.setLayout(DLayout(DHorizontalLayout_L_W(90, 0), DVerticalLayout_H_C(50, 0.5)));

            ca.CAViewAnimation.beginAnimations("", null);
            ca.CAViewAnimation.setAnimationDuration(0.3);
            this.animation_2_textfield.setLayout(DLayout(DHorizontalLayout_L_R(90, 90), DVerticalLayout_H_C(50, 0.5)));
            this.animation_2_textfield.setAlpha(1);
            ca.CAViewAnimation.setAnimationDidStopSelector(this, this.endAction);
            ca.CAViewAnimation.commitAnimations();
        }else if(tag==202){
            ca.CAViewAnimation.beginAnimations("", null);
            ca.CAViewAnimation.setAnimationDuration(0.3);
            this.animation_2_textfield.setLayout(DLayout(DHorizontalLayout_L_W(90, 0), DVerticalLayout_H_C(50, 0.5)));
            this.animation_2_textfield.setAlpha(0);
            ca.CAViewAnimation.setAnimationDidStopSelector(this, this.endAction);
            ca.CAViewAnimation.commitAnimations();
        }else if(tag==300){
            var imageSize = ca.CAImage.create("image/2.jpg").getContentSize();
            this.animation_3_imageview.setImageRect(ca.drect(0,0,0,imageSize.height));
            this.animation_3_imageview.setLayout(DLayout(DHorizontalLayout_L_W(0, 0), DVerticalLayoutFill));
            ca.CAViewAnimation.beginAnimations("", null);
            ca.CAViewAnimation.setAnimationDuration(0.8);
            ca.CAViewAnimation.setAnimationRepeatAutoreverses(true);
            this.animation_3_imageview.setImageRect(ca.drect(0,0,imageSize.width,imageSize.height));
            this.animation_3_imageview.setLayout(DLayout(DHorizontalLayout_L_R(0, 0), DVerticalLayoutFill));
            ca.CAViewAnimation.commitAnimations();
        }
    },
    endAction: function()
    {
        if (this.animation_2_btn_cancel.isVisible()) {
            this.animation_2_btn_cancel.setVisible(false);
        }else{
            this.animation_2_btn_cancel.setVisible(true);
        }

    }

});