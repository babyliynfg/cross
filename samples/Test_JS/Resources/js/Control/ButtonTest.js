/**
 * Created by zhanglei on 16/8/2.
 */
var ButtonTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());

        var btn1 = ca.CAButton.create(ca.CAButtonType.Custom);
        btn1.setTag(1);
        btn1.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.16)));
        //设置Button标题的显示文本和字体大小
        btn1.setTitleForState(ca.CAControlState.Normal, "Noborder");
        btn1.setTitleFontSize(40);
        //设置Button的标题颜色和状态
        btn1.setTitleColorForState(ca.CAControlState.Normal, ca.color(51,204,255,255));
        //添加回调事件
        btn1.addTarget(this, this.buttonCallback, ca.CAControlEvents.TouchUpInSide);
        this.getView().addSubview(btn1);

        var btn2 = ca.CAButton.create(ca.CAButtonType.SquareRect);
        btn2.setTag(2);
        btn2.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.32)));
        //设置Button标题的显示文本
        btn2.setTitleForState(ca.CAControlState.Normal, "SquareRect");
        //添加回调事件
        btn2.addTarget(this, this.buttonCallback, ca.CAControlEvents.TouchUpInSide);
        this.getView().addSubview(btn2);

        var btn3 = ca.CAButton.create(ca.CAButtonType.RoundedRect);
        btn3.setTag(3);
        btn3.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.48)));
        //设置Button标题的显示文本
        btn3.setTitleForState(ca.CAControlState.Normal, "RoundedRect");
        //添加回调事件
        btn3.addTarget(this, this.buttonCallback, ca.CAControlEvents.TouchUpInSide);
        this.getView().addSubview(btn3);


        var btn4 = ca.CAButton.create(ca.CAButtonType.SquareRect);
        btn4.setTag(4);
        btn4.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.64)));
        //设置Button的标题颜色和状态
        btn4.setTitleColorForState(ca.CAControlState.Normal,ca.WHITE);
        //设置Button的背景View
        btn4.setBackgroundViewForState(ca.CAControlState.Normal, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("image/button_normal.png")));
        //设置Button的背景View
        btn4.setBackgroundViewForState(ca.CAControlState.Highlighted,  ca.CAScale9ImageView.createWithImage( ca.CAImage.create("image/button_down.png")));
        //添加回调事件
        btn4.addTarget(this, this.buttonCallback, ca.CAControlEvents.TouchDown);
        this.getView().addSubview(btn4);

        var btn5 = ca.CAButton.create(ca.CAButtonType.SquareRect);
        btn5.setTag(5);
        btn5.setAllowsSelected(true);
        btn5.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.8)));
        btn5.setTitleForState(ca.CAControlState.Normal, "Normal");
        btn5.setTitleColorForState(ca.CAControlState.Normal, ca.WHITE);
        btn5.setTitleForState(ca.CAControlState.Selected, "Selected");
        btn5.setTitleForState(ca.CAControlState.Highlighted, "Highlighted");
        btn5.setBackgroundViewForState(ca.CAControlState.Normal, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("source_material/btn_rounded3D_normal.png")));
        btn5.setBackgroundViewForState(ca.CAControlState.Highlighted, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("source_material/btn_rounded3D_highlighted.png")));
        btn5.setBackgroundViewForState(ca.CAControlState.Selected, ca.CAScale9ImageView.createWithImage(ca.CAImage.create("source_material/btn_rounded3D_selected.png")));
        btn5.addTarget(this, this.buttonCallback, ca.CAControlEvents.TouchDown);
        this.getView().addSubview(btn5);


    },
    buttonCallback: function ( btn ,point) {
        var tag = btn.getTag();
        switch (tag) {
            case 1:
                log("Button Noborder");
                break;
            case 2:
                log("Button SquareRect");
                break;
            case 3:
                log("Button RoundedRect");
                break;
            case 4:
                log("Button Custom");
                break;
            case 5:
                log("Button AllowsSelected");
                break;
            default:
                break;
        }

    }
});