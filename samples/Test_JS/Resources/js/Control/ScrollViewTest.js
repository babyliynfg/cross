/**
 * Created by zhanglei on 16/8/8.
 */
var ScrollViewTest = ca.CAViewController.extend({

    ctor: function () {
        this._super();
    },

    viewDidLoad: function() {

        this.colorArr = new Array();

        this.p_ScrollView = ca.CAScrollView.createWithLayout(ca.DLayoutFill);
        this.p_ScrollView.setMinimumZoomScale(0.2);
        this.p_ScrollView.setMaximumZoomScale(5.0);
        this.p_ScrollView.setMultitouchGesture(ca.CAScrollView.MultitouchGesture.ZoomAndRotate);
        this.getView().addSubview(this.p_ScrollView);
        this.p_ScrollView.setViewSize(ca.DSize.set(2160,3840));

        this.p_imageView = ca.CAImageView.createWithImage(ca.CAImage.create("image/h1.png"));
        this.p_imageView.setLayout(ca.DLayoutFill);
        this.p_ScrollView.addSubview(this.p_imageView);
    },
    btncallback: function () {
        log("btncallback-->");
    },

    refreshData: function (interval)
    {
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.CAColor4B.set(r, g, b, 255));
        }
        this.p_Conllection.reloadData();
    },
    scrollViewDidMoved: function (view)
    {
        log("DidMoved-->");
    },
    scrollViewStopMoved: function ( view)
    {
        log("StopMoved-->");
    },
    scrollViewDidScroll: function ( view)
    {
        log("DidMScroll-->");
    },
    scrollViewWillBeginDragging: function ( view)
    {
        log("BeginDragging-->");
    }

    ,scrollViewDidEndDragging: function ( view)
    {
        log("DidEndDragging-->");
    }

    ,scrollViewDidZoom: function ( view)
    {
        log("DidZoom-->");
    }

    ,scrollViewHeaderBeginRefreshing: function (view)
    {
        this.colorArr.clear();
        ca.CAScheduler.getScheduler().schedule(this,this.refreshData,0.01);
    }

    ,scrollViewFooterBeginRefreshing: function ( view)
    {
        ca.CAScheduler.getScheduler().schedule(this,this.refreshData,0.02);
    }



});
