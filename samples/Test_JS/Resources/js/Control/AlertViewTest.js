/**
 * Created by zhanglei on 16/8/1.
 */
var AlertViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());
                                               
        var btn1 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
        btn1.setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.25)));
        btn1.setTag(100);
        btn1.setTitleForState(ca.CAControl.State.Normal, "Click-1");
        btn1.setTitleColorForState(ca.CAControl.State.Normal, ca.color(51,204,255,255));
        btn1.addTarget(function () {
            var alertView = ca.CAAlertView.createWithText("Alert","this is a alert!","close",null);
            alertView.show(function (btnIndex)
            {
                log("btnIndex=="+btnIndex);
            });
        }, ca.CAButton.Event.TouchUpInSide);
        this.getView().addSubview(btn1);

        var btn2 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
        btn2.setLayout( DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.5)));
        btn2.setTag(200);
        btn2.setTitleForState(ca.CAControl.State.Normal, "Click-2");
        btn2.setTitleColorForState(ca.CAControl.State.Normal, ca.color(51,204,255,255));
        btn2.addTarget(function () {
            var alertView = ca.CAAlertView.createWithText("Alert", "this is a alert!", "ok","close",null);
            alertView.show(function (btnIndex)
            {
                log("btnIndex=="+btnIndex);
            });
        },ca.CAButton.Event.TouchUpInSide);
        this.getView().addSubview(btn2);

        var btn3 = ca.CAButton.create(ca.CAButton.Type.RoundedRect);
        btn3.setLayout( DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.75)));
        btn3.setTag(300);
        btn3.setTitleForState(ca.CAControl.State.Normal, "Click-3");
        btn3.setTitleColorForState(ca.CAControl.State.Normal, ca.color(51,204,255,255));
        btn3.addTarget(function () {
          var alertView = ca.CAAlertView.createWithText("Alert", "message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,message is so long,!", "ok","close","button3","button4","button5","button6","button7",null);
          alertView.show(function (btnIndex)
          {
              log("btnIndex=="+btnIndex);
          });
        }, ca.CAButton.Event.TouchUpInSide);
        this.getView().addSubview(btn3);

    },
    alerCallback: function (btnIdex) {
        log("btnIndex==" + btnIdex);
    },
});
