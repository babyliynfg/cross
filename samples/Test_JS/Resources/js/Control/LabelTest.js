/**
 * Created by zhanglei on 16/8/3.
 */
var LabelTest = ca.CAViewController.extend({
    labelNum :3,
    maxNum:2,
    ctor: function (num) {
        this._super();
        if(num != null){
            this.labelNum = num;
        }
        this.initLabelTest();
        //var btn = ca.CAButton.createWithFrame(ca.rect(100, 100, 100, 30), 1);
        //btn.setTitleForState(0, "Button");
        //btn.addTarget(this, this.btncallback, 0);
        //this.getView().addSubview(btn);
    },
    initLabelTest:function(){
        var str = "Hello World";
        if (this.labelNum == 0)
        {
            var Font = new CAFont();
            Font.fontSize = 36;
            Font.color = ca.RED;
            //Font.fontName = "c:/x.ttf";

            var label = ca.CALabel.create();
            label.setText(str);
            label.setFont(Font);
            label.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            label.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            label.setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 0.16)));

            var Font1 = new CAFont();
            Font1.fontSize = 36;
            Font1.color = ca.RED;
            //Font1.fontName = "c:/x.ttf";
            Font1.underLine = true;

            var label1 = ca.CALabel.create();
            label1.setText(str);
            label1.setFont(Font1);
            label1.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            label1.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            label1.setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 0.32)));

            var label2 = ca.CALabel.create();
            var Font2 = new CAFont();
            Font2.fontSize = 36;
            Font2.color = ca.RED;
            //Font2.fontName = "c:/x.ttf";
            Font2.bold = true;
            label2.setText(str);
            label2.setFont(Font2);
            label2.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            label2.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            label2.setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 0.48)));

            var label3 = ca.CALabel.create();
            var Font3 = new CAFont();
            Font3.fontSize = 36;
            Font3.color = ca.RED;
            //Font3.fontName = "c:/x.ttf";
            Font3.italics = true;
            label3.setText(str);
            label3.setFont(Font3);
            label3.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            label3.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            label3.setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 0.64)));

            var label4 = ca.CALabel.create();
            var Font4 = new CAFont();
            Font4.fontSize = 36;
            Font4.color = ca.RED;
            label4.setText("Enable Copy");
            label4.setFont(Font4);
            label4.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            label4.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            label4.setLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_H_C(40, 0.8)));

            var view = ca.CAView.createWithLayout(DLayoutFill);
            view.addSubview(label);
            view.addSubview(label1);
            view.addSubview(label2);
            view.addSubview(label3);
            view.addSubview(label4);
            view.setColor(ca.color._getGray());

            this.getView().addSubview(view);
        }
        else if (this.labelNum == 1)
        {
            var label5 = ca.CALabel.create();
            var Font5 = new CAFont();
            Font5.fontSize = 36;
            Font5.color = ca.RED;
            //Font5.fontName = "c:/x.ttf";
            Font5.bold = true;
            Font5.italics = true;
            Font5.underLine = true;
            label5.setText("Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World");
            label5.setFont(Font5);
            label5.setLineSpacing(20);
            label5.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            label5.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            label5.setLayout(DLayout(DHorizontalLayout_L_R(50, 50), DVerticalLayout_T_H(300, 300)));

            var view1 = ca.CAView.createWithLayout(DLayoutFill);
            view1.addSubview(label5);
            view1.setColor(ca.color._getGray());

            this.getView().addSubview(view1);
        }
        else
        {

            var RichLabel = ca.CARichLabel.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_B(200, 200)));
            var RichLabelFont = new CAFont();
            RichLabelFont.bold = true;
            RichLabelFont.fontSize = 42;
            RichLabelFont.color = ca.RED;
            RichLabel.appendText("Hello World Hello World Hello World Hello World Hello World Hello World ", RichLabelFont);

            var RichLabelFont1 = new CAFont();
            RichLabelFont1.italics = true;
            RichLabelFont1.fontSize = 42;
            RichLabelFont1.color = ca.RED;
            RichLabel.appendText("Hello World Hello World Hello World Hello World Hello World Hello World ", RichLabelFont1);

            var RichLabelFont2 = new CAFont();
            RichLabelFont2.underLine = true;
            RichLabelFont2.fontSize = 42;
            RichLabelFont2.color = ca.RED;
            RichLabel.appendText("Hello World Hello World Hello World Hello World Hello World Hello World ", RichLabelFont2);

            var view2 = ca.CAView.createWithLayout(DLayoutFill);
            view2.addSubview(RichLabel);
            view2.setColor(ca.color._getGray());

            this.getView().addSubview(view2);
        }


    },
    btncallback: function () {
        log("btncallback-.");
    }
});