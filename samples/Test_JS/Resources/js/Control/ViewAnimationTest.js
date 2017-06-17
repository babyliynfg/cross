/**
 * Created by crossApp on 16/8/8.
 */
var ViewAnimationTest = ca.CAViewController.extend({
    

    ctor: function () {
        this._super();

        var item  = ca.CANavigationBarItem.create("文本展示") ;
        var buttonItem = ca.CABarButtonItem.create("", ca.CAImage.create("source_material/btn_right_white.png"), null) ;
        buttonItem.setCallbackFunction(this._btnCallback.bind(this)) ;
        item.addRightButtonItem(buttonItem) ;
        this.setNavigationBarItem(item);

    },

    viewDidLoad: function() {
        this.AnimationNum = 0 ;
        this._compileView() ;
    },


    _btnCallback:function(){
        this.AnimationNum = this.AnimationNum < 2 ? this.AnimationNum + 1 : 0 ;
        this.getView().removeAllSubviews() ;
        this._compileView() ;
    },

    _compileView:function(){
        var winSize = this.getView().getBounds().size;
        var winRect = this.getView().getBounds();

        if (this.AnimationNum == 0)
        {
            //Animation 1
            this.heart_index = 0;
            var btn1 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
            btn1.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(56, 0.25)));
            btn1.setTitleForState(ca.CAControl.State.Normal, "Play Animation");
            btn1.setTitleColorForState(ca.CAControl.State.Normal, ca.CAColor4B.set(51,204,255,255));

            this.animation_1_view = ca.CAImageView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(28, 0.5), ca.DVerticalLayout_H_C(24, 0.5)));
            this.animation_1_view.setImage(ca.CAImage.create("image/heart1.png"));

            var view1 = ca.CAView.createWithLayout(ca.DLayoutFill);
            view1.addSubview(btn1);
            view1.addSubview(this.animation_1_view);
            view1.setColor(ca.CAColor4B.GRAY);
            this.getView().addSubview(view1);

            var heart_1 = this.heart_index;
            var animation_1 = this.animation_1_view;
            btn1.addTarget(function(){
                animation_1.setScale(1);
                ca.CAViewAnimation.beginAnimations("");
                ca.CAViewAnimation.setAnimationDuration(0.3);
                ca.CAViewAnimation.setAnimationRepeatAutoreverses(true);
                if (heart_1==0) {
                    animation_1.setImage(ca.CAImage.create("image/heart2.png"));
                    heart_1 = 1;
                }else{
                    animation_1.setImage(ca.CAImage.create("image/heart1.png"));
                    heart_1 = 0;
                }
                animation_1.setScale(2);
                ca.CAViewAnimation.commitAnimations();
            }, ca.CAButton.Event.TouchUpInSide );
        }
        else if (this.AnimationNum == 1)
        {
            //Animation 2
            var bg = ca.CAImageView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(0, 0), ca.DVerticalLayout_H_C(80, 0.5)));
            bg.setImage(ca.CAImage.create("image/navbg.jpg"));

            this.animation_2_textfield = ca.CATextField.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(90, 90), ca.DVerticalLayout_H_C(50, 0.5)));
            this.animation_2_textfield.setFontSize(40);
            this.animation_2_textfield.setKeyboardType(ca.CATextField.KeyboardType.Default);
            this.animation_2_textfield.setVisible(false);

            var animation_2_btn_search = ca.CAButton.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(25, 56), ca.DVerticalLayout_H_C(48, 0.5)), ca.CAButton.Type.Custom);
            animation_2_btn_search.setImageForState(ca.CAControl.State.Normal, ca.CAImage.create("image/search_btn.png"));


            this.animation_2_btn_cancel = ca.CAButton.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_R_W(0, 100), ca.DVerticalLayout_H_C(50, 0.5)), ca.CAButton.Type.Custom);
            this.animation_2_btn_cancel.setTitleForState(ca.CAControl.State.Normal, "Cancel");
            this.animation_2_btn_cancel.setTitleColorForState(ca.CAControl.State.Normal, ca.CAColor4B.WHITE);

            this.animation_2_btn_cancel.setVisible(false);

            var view2 = ca.CAView.createWithLayout(ca.DLayoutFill);
            view2.addSubview(bg);
            view2.addSubview(this.animation_2_textfield);
            view2.addSubview(animation_2_btn_search);
            view2.addSubview(this.animation_2_btn_cancel);
            view2.setColor(ca.CAColor4B.GRAY);
            this.getView().addSubview(view2);


            var animation_2_text = this.animation_2_textfield;
            var animation_2_btn = this.animation_2_btn_cancel;
            animation_2_btn_search.addTarget(function () {
                animation_2_text.setVisible(true);
                animation_2_btn.setVisible(false);
                animation_2_text.setAlpha(0);
                animation_2_text.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(90, 0), ca.DVerticalLayout_H_C(50, 0.5)));

                ca.CAViewAnimation.beginAnimations("");
                ca.CAViewAnimation.setAnimationDuration(0.3);
                animation_2_text.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(90, 90), ca.DVerticalLayout_H_C(50, 0.5)));
                animation_2_text.setAlpha(1);
                ca.CAViewAnimation.setAnimationDidStopSelector(function () {
                    if (animation_2_btn.isVisible()) {
                        animation_2_btn.setVisible(false);
                    }else{
                        animation_2_btn.setVisible(true);
                    }
                });
                ca.CAViewAnimation.commitAnimations();
            }, ca.CAButton.Event.TouchUpInSide );

            this.animation_2_btn_cancel.addTarget(function () {
                ca.CAViewAnimation.beginAnimations("");
                ca.CAViewAnimation.setAnimationDuration(0.3);
                animation_2_text.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(90, 0), ca.DVerticalLayout_H_C(50, 0.5)));
                animation_2_text.setAlpha(0);
                ca.CAViewAnimation.setAnimationDidStopSelector(function()
                {
                    if (animation_2_btn.isVisible()) {
                        animation_2_btn.setVisible(false);
                    }else{
                        animation_2_btn.setVisible(true);
                    }

                });
                ca.CAViewAnimation.commitAnimations();
            }, ca.CAButton.Event.TouchUpInSide );
        }
        else if(this.AnimationNum == 2)
        {
            //Animation 3
            this.animation_3_imageview = ca.CAImageView.createWithLayout(ca.DLayoutFill);
            this.animation_3_imageview.setImage(ca.CAImage.create("image/2.jpg"));

            var btn3 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
            btn3.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(56, 0.25)));
            btn3.setTitleForState(ca.CAControl.State.Normal, "Play Animation");
            btn3.setTitleColorForState(ca.CAControl.State.Normal, ca.CAColor4B.set(51,204,255,255));

            var view3 = ca.CAView.createWithLayout(ca.DLayoutFill);
            view3.addSubview(this.animation_3_imageview);
            view3.addSubview(btn3);
            view3.setColor(ca.CAColor4B.GRAY);
            this.getView().addSubview(view3);

            var animation_3 = this.animation_3_imageview;
            btn3.addTarget(function () {
                var imageSize = ca.CAImage.create("image/2.jpg").getContentSize();
                animation_3.setImageRect(ca.DRect.set(0,0,0,imageSize.height));
                animation_3.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(0, 0), ca.DVerticalLayoutFill));
                ca.CAViewAnimation.beginAnimations("");
                ca.CAViewAnimation.setAnimationDuration(0.8);
                ca.CAViewAnimation.setAnimationRepeatAutoreverses(true);
                animation_3.setImageRect(ca.DRect.set(0,0,imageSize.width,imageSize.height));
                animation_3.setLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(0, 0), ca.DVerticalLayoutFill));
                ca.CAViewAnimation.commitAnimations();
            }, ca.CAButton.Event.TouchUpInSide );
        }
    },


});
