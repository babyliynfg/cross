/**
 * Created by zhanglei on 16/8/2.
 */
var ButtonTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());

        var btn1 = ca.CAButton.create(ca.CAButton.Type.Custom);
        btn1.setTag(1);
        btn1.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(54, 0.16)));
        //设置Button标题的显示文本和字体大小
        btn1.setTitleForState(ca.CAControl.State.Normal, "Noborder");
        btn1.setTitleFontSize(40);
        //设置Button的标题颜色和状态
        btn1.setTitleColorForState(ca.CAControl.State.Normal, ca.CAColor4B.set(51,204,255,255));
        //添加回调事件
        btn1.addTarget(function(){ log("Button Noborder");}, ca.CAButton.Event.TouchUpInSide );
        this.getView().addSubview(btn1);

        var btn2 = ca.CAButton.create(ca.CAButton.Type.SquareRect);
        btn2.setTag(2);
        btn2.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(54, 0.32)));
        //设置Button标题的显示文本
        btn2.setTitleForState(ca.CAControl.State.Normal, "SquareRect");
        //添加回调事件
        btn2.addTarget(function(){ log("Button SquareRect");}, ca.CAButton.Event.TouchUpInSide );
        this.getView().addSubview(btn2);

        var btn3 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
        btn3.setTag(3);
        btn3.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(54, 0.48)));
        //设置Button标题的显示文本
        btn3.setTitleForState(ca.CAControl.State.Normal, "RoundedRect");
        //添加回调事件
        btn3.addTarget(function(){ log("Button RoundedRect");}, ca.CAButton.Event.TouchUpInSide );
        this.getView().addSubview(btn3);

        var btn4 = ca.CAButton.create(ca.CAButton.Type.SquareRect);
        btn4.setTag(4);
        btn4.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(54, 0.64)));
        //设置Button的标题颜色和状态
        btn4.setTitleColorForState(ca.CAControl.State.Normal,ca.WHITE);
        //设置Button的背景View
        btn4.setBackgroundViewForState(ca.CAControl.State.Normal, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("image/button_normal.png")));
        //设置Button的背景View
        btn4.setBackgroundViewForState(ca.CAControl.State.Highlighted,  ca.CAScale9ImageView.createWithImage( ca.CAImage.create("image/button_down.png")));
        //添加回调事件
        btn4.addTarget(function(){ log("Button Custom");}, ca.CAButton.Event.TouchDown );
        this.getView().addSubview(btn4);

        var btn5 = ca.CAButton.create(ca.CAButton.Type.SquareRect);
        btn5.setTag(5);
        btn5.setLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(240, 0.5), ca.DVerticalLayout_H_C(54, 0.8)));
        btn5.setTitleForState(ca.CAControl.State.Normal, "Normal");
        btn5.setTitleColorForState(ca.CAControl.State.Normal, ca.WHITE);
        btn5.setTitleForState(ca.CAControl.State.Highlighted, "Highlighted");
        btn5.setBackgroundViewForState(ca.CAControl.State.Normal, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("source_material/btn_rounded3D_normal.png")));
        btn5.setBackgroundViewForState(ca.CAControl.State.Highlighted, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("source_material/btn_rounded3D_highlighted.png")));
        btn5.addTarget(function(){ log("Button AllowsSelected");}, ca.CAButton.Event.TouchDown );
        this.getView().addSubview(btn5);


    },
    viewDidLoad: function() {
    },
});
