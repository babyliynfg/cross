/**
 * Created by zhanglei on 16/8/3.
 */
var TextViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
        this.getView().setColor(ca.color._getGray());

        var textView = ca.CATextView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(100, 100), ca.DVerticalLayout_T_B(100, 100)));
        this.getView().addSubview(textView);
    },
    viewDidLoad: function() {
    },
});