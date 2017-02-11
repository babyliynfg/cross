/**
 * Created by zhanglei on 16/8/3.
 */
var SliderTest = ca.CAViewController.extend({
    sliderNum : 1,
    sliderValue1: null,
    maxNum:1,
    ctor: function (num) {
        this._super();
        if(num != null){
            this.sliderNum = num;
        }
        this.initSliderTest();
    },
    initSliderTest:function(){


        this.sliderValue =  ca.CALabel.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(300, 50)));
        this.sliderValue.setColor(ca.color(51,204,255,255));
        this.sliderValue.setText("0");
        this.sliderValue.setFontSize(30);
        this.sliderValue.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
        this.sliderValue.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);

        if (this.sliderNum == 0)
        {
            var view1 = ca.CAView.createWithLayout(DLayoutFill);
            view1.setColor(ca.color._getGray());

            view1.addSubview(this.sliderValue);
            var slider1 = ca.CASlider.createWithLayout(DLayout(DHorizontalLayout_L_R(120, 120), DVerticalLayout_T_H(500, 56)));
            slider1.addTarget(this, this.sliderValueChange);
            slider1.setTag(100);
            view1.addSubview(slider1);
            this.getView().addSubview(view1);
        }
        else if (this.sliderNum == 1)
        {
            var view2 =  ca.CAView.createWithLayout(DLayoutFill);
            view2.setColor(ca.color._getGray());

            view2.addSubview(this.sliderValue);

            var slider2 =  ca.CASlider.createWithLayout(DLayout(DHorizontalLayout_L_R(120, 120), DVerticalLayout_T_H(500, 56)));
            slider2.setTag(101);
            slider2.setMaxTrackTintImage( ca.CAImage.create("source_material/ex1.png"));
            slider2.setMinTrackTintImage( ca.CAImage.create("source_material/ex3.png"));
            slider2.setThumbTintImage( ca.CAImage.create("source_material/btn_square_highlighted.png"));
            slider2.addTarget(this, this.sliderValueChange);
            view2.addSubview(slider2);

            this.getView().addSubview(view2);
        }
    },
    sliderValueChange: function (btn, point) {
        var value =  btn.getValue() * 100;
        this.sliderValue.setText(Math.round(value));
    }
});