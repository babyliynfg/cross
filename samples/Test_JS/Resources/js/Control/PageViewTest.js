/**
 * Created by zhanglei on 16/8/3.
 */
var PageViewTest = ca.CAViewController.extend({
    pageViewIndex:0,
    pageControl: null,
    ctor: function () {
        this._super();

        var view1 = ca.CAImageView.createWithImage(ca.CAImage.create("image/1.jpg"));
        var view2 = ca.CAImageView.createWithImage(ca.CAImage.create("image/2.jpg"));
        var view3 = ca.CAImageView.createWithImage(ca.CAImage.create("image/3.jpg"));
        var views = new Array();
        views.push(view1);
        views.push(view2);
        views.push(view3);

        var p_pageView = ca.CAPageView.createWithLayout(DLayoutFill, 0);
        p_pageView.setViews(views);
        p_pageView.setPageViewDelegate(this);
        this.getView().addSubview(p_pageView);

        var pageView = p_pageView;

        this.pageControl = ca.CAPageControl.createWithLayout(DLayout(DHorizontalLayout_W_C(100, 0.5), DVerticalLayout_T_H(30, 50)));
        this.pageControl.setNumberOfPages(views.length);
        this.pageControl.setPageIndicatorTintColor(ca.color._getGray());
        this.pageControl.setCurrentPageIndicatorTintColor(ca.color._getGreen());
        this.getView().addSubview(this.pageControl);

        var page = this.pageControl;

        this.pageControl.setTarget(function ( func)
        {
            log("Button RoundedRect");
            log("btn_tag==="+page.getCurrentPage());
            pageView.setCurrPage(page.getCurrentPage(), true);
        });

    },
    pageViewDidBeginTurning: function (pageView) {

    },
    pageViewDidEndTurning: function (pageView) {
        if (this.pageViewIndex == 0) {
            this.pageControl.setCurrentPage(pageView.getCurrPage());
            this.pageControl.updateCurrentPageDisplay();
        }
        else {

        }
    },
    pageViewDidSelectPageAtIndex: function (pageView, index, point) {

    }


});