/**
 * Created by zhanglei on 16/8/8.
 */

var RenderImageTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());

        var image = ca.CAImage.create("r/HelloWorld.png");

        var dle_ren_index = 0;

        var index = 0;

        var scrollRect = ca.drect(0,0,0,0);
        scrollRect.x = 100;
        scrollRect.y = 100;
        scrollRect.width = ca.winSize.width - 200;
        scrollRect.height = ca.winSize.height - 400;

        var m_clvImage = ca.CAClippingView.create();
        m_clvImage.setStencil(this.getStencil(ca.dsize(scrollRect.width,scrollRect.height), index));
        m_clvImage.setFrame(scrollRect);
        m_clvImage.setInverted(false);
        m_clvImage.setClippingEnabled(false);
        this.getView().addSubview(m_clvImage);

        var temp_mini = 0;
        if (image.getContentSize().width>image.getContentSize().height)
        {
            temp_mini = scrollRect.height/image.getContentSize().height;
        }
        else
        {
            temp_mini = scrollRect.width/image.getContentSize().width;
        }
        var scrollView = ca.CAScrollView.createWithFrame(m_clvImage.getBounds());
        scrollView.setViewSize(ca.dsize(image.getContentSize()));
        scrollView.setContentOffset(ca.DPoint(0,ca.winSize.height/4), false);
        scrollView.setMinimumZoomScale(temp_mini);
        scrollView.setMaximumZoomScale(2.5);
        //scrollView.setBackgroundColor(CAColor_clear);
        scrollView.setShowsScrollIndicators(false);
        scrollView.setBounces(false);
        scrollView.setScrollViewDelegate(this);
        scrollView.setDisplayRange(true);
        m_clvImage.addSubview(scrollView);

        var rect = ca.drect(0,0,0,0);
        rect.height = scrollView.getViewSize().height;
        rect.width = scrollView.getViewSize().width;
        rect.x = 0;
        rect.y = 0;
        var imv = ca.CAImageView.createWithLayout(DLayoutFill);
        imv.setImage(image);
        imv.setScaleType(ca.CAImageView.ScaleType.FitImageInside);
        scrollView.addSubview(imv);


//        var m_clv = ca.CAClippingView.create();
//        m_clv.setStencil(this.getStencil(ca.dsize(scrollRect.width,scrollRect.height), index));
//        m_clv.setFrame(scrollRect);
//        m_clv.setInverted(true);
//        m_clv.setTouchEnabled(false);
//        this.getView().addSubview(m_clv);
//
//        var ivRect = ca.drect(0,0,0,0);
//        ivRect.height = ca.winSize.height;
//        ivRect.width = ca.winSize.width;
//        ivRect.x = scrollRect.x *-1;
//        ivRect.y = scrollRect.y * -1;
//
//        var iv = ca.CAView.createWithColor(ca.color(0,0,0,128));
//        iv.setFrame(ivRect);
//        m_clv.addSubview(iv);
    },
    getStencil: function(size, index)
    {
        if (index == 0)
        {
            var ver = new Array();
            ver[0] = ca.p(0, 0);
            ver[1] = ca.p(0, size.height);
            ver[2] = ca.p(size.width, size.height);
            ver[3] = ca.p(size.width, 0);
            var stencil = ca.CADrawView.create();
            stencil.drawPolygon(ver, 4, ca.color(255, 0, 0, 0), 2, ca.color(255, 0, 0, 0));
            stencil.setFrameOrigin(ca.DPoint(0, size.height));
            return stencil;
        }
        else if (index == 1)
        {
            var cir = new Array(720);
            for (var i=0; i<720; i++)
            {
                var x = Math.cos(i * Math.PI/180) * size.width/2;
                var y = Math.sin(i * Math.PI/180) * size.width/2;
                cir[i] = ca.p(x, y);
            }
            var stencil = ca.CADrawView.create();
            stencil.drawPolygon(cir, 720, ca.color(1, 1, 1, 0.5), 0, ca.color(1, 1, 1, 0));
            stencil.setCenterOrigin(ca.p(size.width/2, size.height/2));
            return stencil;
        }
        return null;
    }
});
