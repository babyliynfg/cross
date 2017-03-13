/**
 * Created by zhanglei on 16/8/4.
 */
var WebViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());

        var web = ca.CAWebView.createWithLayout(DLayoutFill);
        web.loadURL("http://crossapp.9miao.com");
        this.getView().addSubview(web);
    },
    btncallback: function () {
        log("btncallback-->");
    }
});
