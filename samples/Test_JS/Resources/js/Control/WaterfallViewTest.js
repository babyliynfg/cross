/**
 * Created by zhanglei on 16/8/8.
 */
var WaterfallViewTest = ca.CAViewController.extend({
    colorArr:null,
    Waterfall:null,
    ctor: function () {
        this._super();

        this.colorArr = new Array();
        for (var i = 0; i < 12; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.color(r, g, b, 255));
        }

        //headerRefreshView = CAPullToRefreshView.create(CAPullToRefreshView.CAPullToRefreshTypeHeader);
        //footerRefreshView = CAPullToRefreshView.create(CAPullToRefreshView.CAPullToRefreshTypeFooter);

        this.Waterfall = ca.CAWaterfallView.createWithLayout(DLayoutFill);
        this.Waterfall.setItemMargin(10);
        this.Waterfall.setColumnMargin(10);
        this.Waterfall.setColumnCount(2);
        this.Waterfall.setAllowsSelection(true);
        //this.Waterfall.setScrollViewDelegate(this);
        this.Waterfall.setWaterfallViewDelegate(this);
        this.Waterfall.setWaterfallViewDataSource(this);
        //this.Waterfall.setHeaderRefreshView(headerRefreshView);
        //this.Waterfall.setFooterRefreshView(footerRefreshView);
        this.getView().addSubview(this.Waterfall);
    },
        refreshData1: function ( interval)
    {
        for (var i = 0; i < 12; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.color(r, g, b, 255));
        }
        this.Waterfall.reloadData();
    }
    ,refreshData2: function ( interval)
    {

        for (var i = 0; i < 12; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.color(r, g, b, 255));
        }
        this.Waterfall.reloadData();
    }

    ,scrollViewHeaderBeginRefreshing: function ( view)
    {
        //CAScheduler.schedule(schedule_selector(WaterfallViewTest.refreshData1), this, 0.1, 0, 1.0f + CCRANDOM_0_1() * 2, false);

        ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this,this.refreshData1,0.01);
    }

    ,scrollViewFooterBeginRefreshing: function ( view)
    {
        //CAScheduler.schedule(schedule_selector: function (WaterfallViewTest.refreshData2), this, 0.1, 0, 1.0f + CCRANDOM_0_1() * 2, false);
        ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this,this.refreshData1,0.01);
    }

    ,waterfallViewDidSelectCellAtIndexPath: function (waterfallView, itemIndex)
    {
        //选中
        cell = waterfallView.cellForRowAtIndexPath(itemIndex);
        cell.getContentView().setRotation(-360);
        cell.getContentView().setScale(0.5);
        ca.CAViewAnimation.beginAnimations("", null);
        cell.getContentView().setRotation(0);
        cell.getContentView().setScale(1.0);
        ca.CAViewAnimation.commitAnimations();
        log("选中");
    }

    ,waterfallViewDidDeselectCellAtIndexPath: function (waterfallView, itemIndex)
    {
        log("取消选中");
    },

    //Necessary
   waterfallCellAtIndex: function (waterfallView,  cellSize, itemIndex)
    {
        p_Cell = this.Waterfall.dequeueReusableCellWithIdentifier("CrossApp");
        if (p_Cell == null)
        {
            p_Cell = ca.CAWaterfallViewCell.create("CrossApp");

            var itemImage = ca.CAView.createWithLayout(DLayoutFill);
            itemImage.setTag(99);
            p_Cell.getContentView().addSubview(itemImage);

            var itemText = ca.CALabel.createWithLayout(DLayoutFill);
            itemText.setTag(100);
            itemText.setFontSize(24);
            itemText.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
            itemText.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
            p_Cell.getContentView().addSubview(itemText);
        }

        //设置Item背景颜色
        var itemImageView = p_Cell.getContentView().getSubviewByTag(99);
        itemImageView.setColor(this.colorArr[itemIndex]);


        var itemText = p_Cell.getContentView().getSubviewByTag(100);
        itemText.setText("("+itemIndex+")");

        return  p_Cell;

    }
    //Necessary
    ,waterfallViewHeightForItemAtIndex: function(waterfallView, itemIndex)
    {
        return Math.random() * 300 + 300;
    }
    //Necessary
    ,numberOfItems: function (waterfallView)
    {
        return this.colorArr.length;
    },

   waterfallViewSectionViewForHeader: function (waterfallView,  viewSize)
    {
        return null;
    }

    ,waterfallViewHeightForHeader: function (waterfallView)
    {
        return 0;
    },

    waterfallViewSectionViewForFooter: function (waterfallView,  viewSize)
    {
        return null;
    }

    ,waterfallViewHeightForFooter: function (waterfallView)
    {
        return 0;
    }
    ,waterfallViewWillDisplayCellAtIndex: function ( waterfallView,  cell, itemIndex)
    {

    }
});