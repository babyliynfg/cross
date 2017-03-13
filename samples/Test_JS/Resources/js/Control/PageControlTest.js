/**
 * Created by liangyuan on 2017/3/3.
 */

var PageControlTest = ca.CAViewController.extend({
    ctor: function ()
    {
        this._super();
        this.getView().setColor(ca.color._getGray());

        var pageControl = ca.CAPageControl.createWithLayout(DLayout(DHorizontalLayout_W_C(150, 0.5), DVerticalLayout_H_C(54, 0.25)));
        pageControl.setNumberOfPages(5);
        pageControl.setStyle(ca.CAPageControl.Style.Dot);
        pageControl.setPageIndicatorTintColor(ca.color._getWhite());
        pageControl.setCurrentPageIndicatorTintColor(ca.color._getGreen());
        pageControl.setTarget(function ( func)
        {
            log("btn_tag==="+pageControl.getCurrentPage());
        });
        this.getView().addSubview(pageControl);

        var pageControl2 = ca.CAPageControl.createWithLayout(DLayout(DHorizontalLayout_W_C(150, 0.5), DVerticalLayout_H_C(54, 0.4)));
        pageControl2.setNumberOfPages(5);
        pageControl2.setStyle(ca.CAPageControl.Style.Round);
        pageControl2.setPageIndicatorTintColor(ca.color._getWhite());
        pageControl2.setCurrentPageIndicatorTintColor(ca.color._getGreen());
        pageControl2.setTarget(function ( func)
        {
            log("btn_tag==="+pageControl2.getCurrentPage());
        });
        this.getView().addSubview(pageControl2);

        var pageControl3 = ca.CAPageControl.createWithLayout(DLayout(DHorizontalLayout_W_C(150, 0.5), DVerticalLayout_H_C(54, 0.55)));
        pageControl3.setNumberOfPages(5);
        pageControl3.setStyle(ca.CAPageControl.Style.Rectangle);
        pageControl3.setPageIndicatorTintColor(ca.color._getWhite());
        pageControl3.setCurrentPageIndicatorTintColor(ca.color._getGreen());
        pageControl3.setTarget(function ( func)
        {
            log("btn_tag==="+pageControl3.getCurrentPage());
        });
        this.getView().addSubview(pageControl3);
    },
});