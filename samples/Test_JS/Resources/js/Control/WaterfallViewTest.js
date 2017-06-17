/**
 * Created by crossApp on 16/8/8.
 */
var WaterfallViewTest = ca.CAViewController.extend({

    ctor: function () {
        this._super();

        this.colorArr = new Array();
        this._randomColor() ;

    },
    viewDidLoad: function() {

        this.headerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Header);
        this.footerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Footer);

        this.Waterfall = ca.CAWaterfallView.createWithLayout(ca.DLayoutFill);

        this.Waterfall.setHeaderRefreshView(this.headerRefreshView) ;
        this.Waterfall.setFooterRefreshView(this.footerRefreshView) ;

        this.Waterfall.setItemMargin(10);
        this.Waterfall.setColumnMargin(10);
        this.Waterfall.setColumnCount(2);
        this.Waterfall.setAllowsSelection(true);

        this.Waterfall.setCellAtIndexPathCallback(this.waterfallCellAtIndex.bind(this)) ;
        this.Waterfall.setCellHeightAtIndexPathCallback(this.waterfallViewHeightForItemAtIndex.bind(this));
        this.Waterfall.setNumberOfItemsAtIndexPathCallback(this.numberOfItems.bind(this)) ;
        this.Waterfall.setWillDisplayCellAtIndexPathCallback(this.waterfallViewWillDisplayCellAtIndex.bind(this)) ;
        this.Waterfall.setDidSelectCellAtIndexPathCallback(this.waterfallViewDidSelectCellAtIndexPath.bind(this)) ;
        this.Waterfall.setDidDeselectCellAtIndexPathCallback(this.waterfallViewDidDeselectCellAtIndexPath.bind(this)) ;
        this.Waterfall.setHeaderBeginRefreshingCallback(this.scrollViewHeaderBeginRefreshing.bind(this)) ;
        this.Waterfall.setFooterBeginRefreshingCallback(this.scrollViewFooterBeginRefreshing.bind(this)) ;



        this.getView().addSubview(this.Waterfall);

    },
    refreshData1: function ( interval)
    {
        this._randomColor() ;
        this.Waterfall.reloadData();
    },
    refreshData2: function ( interval)
    {

        this._randomColor() ;
        this.Waterfall.reloadData();
    }

    ,
    _randomColor:function(){
        for (var i = 0; i < 60; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);

            this.colorArr.push(ca.CAColor4B.set(r, g, b, 255));
        }
    }

    ,scrollViewHeaderBeginRefreshing: function ()
    {
        ca.CAScheduler.getScheduler().scheduleOnce(this.refreshData1.bind(this), "A",this, 0.5);
    }
    ,scrollViewFooterBeginRefreshing: function ()
    {
        ca.CAScheduler.getScheduler().scheduleOnce(this.refreshData2.bind(this), "A",this, 0.5);
    }
    ,waterfallViewDidSelectCellAtIndexPath: function (itemIndex)
    {
        //选中
        cell = this.Waterfall.cellForRowAtIndexPath(itemIndex);
        cell.getContentView().setRotation(-360);
        cell.getContentView().setScale(0.5);
        ca.CAViewAnimation.beginAnimations("");
        cell.getContentView().setRotation(0);
        cell.getContentView().setScale(1.0);
        ca.CAViewAnimation.commitAnimations();
        ca.log("选中");
    }
    ,waterfallViewDidDeselectCellAtIndexPath: function (itemIndex)
    {
        ca.log("取消选中");
    },

    waterfallCellAtIndex: function (cellSize, itemIndex)
    {
        p_Cell = this.Waterfall.dequeueReusableCellWithIdentifier("CrossApp");
        if (p_Cell == null)
        {
            p_Cell = ca.CAWaterfallViewCell.create("CrossApp");

            var itemImage = ca.CAView.createWithLayout(ca.DLayoutFill);
            itemImage.setTag(99);
            p_Cell.getContentView().addSubview(itemImage);

            var itemText = ca.CALabel.createWithLayout(ca.DLayoutFill);
            itemText.setTag(100);
            itemText.setFontSize(24);
            itemText.setTextAlignment(ca.CATextAlignment.Center);
            itemText.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
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
    ,waterfallViewHeightForItemAtIndex: function( itemIndex)
    {
        return Math.random() * 300 + 300;
    }
    //Necessary
    ,numberOfItems: function (waterfallView)
    {
        return this.colorArr.length;
    }

    ,waterfallViewWillDisplayCellAtIndex: function ( cell, itemIndex)
    {

    }
});
