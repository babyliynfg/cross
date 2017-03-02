/**
 * Created by zhanglei on 16/8/4.
 */
var CollectionViewTest = ca.CAViewController.extend({
    colorArr : null,
    footerRefreshView:null,
    headerRefreshView:null,
    p_Conllection:null,
    ctor: function () {
        this._super();
        this.colorArr = new Array();
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.color(r, g, b, 255));
        }

        this.headerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Header);
        this.footerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Footer);

        this.p_Conllection = ca.CACollectionView.createWithLayout(DLayoutFill);
        this.p_Conllection.setAllowsSelection(true);
//    this.p_Conllection.setAllowsMultipleSelection(true);
        this.p_Conllection.setCollectionViewDelegate(this);
        this.p_Conllection.setCollectionViewDataSource(this);
        // this.p_Conllection.setScrollViewDelegate(this);
        this.p_Conllection.setHeaderRefreshView(this.headerRefreshView);
        this.p_Conllection.setFooterRefreshView(this.footerRefreshView);
        this.p_Conllection.setHoriInterval(20);
        this.p_Conllection.setVertInterval(20);
        this.getView().addSubview(this.p_Conllection);

        this.p_Conllection.reloadData();
        this.p_Conllection.startPullToHeaderRefreshView();

    },
    refreshData1: function( interval){
        this.colorArr.clear();
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.color(r, g, b, 255));
        }
        this.p_Conllection.reloadData();
    },
    refreshData2: function(interval){
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.color(r, g, b, 255));
        }
        this.p_Conllection.reloadData();
    },
    scrollViewHeaderBeginRefreshing: function(view)
    {
        //CAScheduler.schedule(schedule_selector(CollectionViewTest.refreshData1), this, 0.1, 0, 1.0f + CCRANDOM_0_1() * 2);
        ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this.refreshData1,this,0.01);
    },
    scrollViewFooterBeginRefreshing: function( view)
    {
        //CAScheduler.schedule(schedule_selector(CollectionViewTest.refreshData2), this, 0.1, 0, 1.0f + CCRANDOM_0_1() * 2);
        ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this.refreshData2,this,0.01);
    },
    collectionViewDidSelectCellAtIndexPath: function(collectionView, section, row, item)
    {
        var cell = collectionView.cellForRowAtIndexPath(section, row, item);
        cell.getContentView().setRotation(-360);
        cell.getContentView().setScale(0.5);
        ca.CAViewAnimation.beginAnimations("");
        cell.getContentView().setRotation(0);
        cell.getContentView().setScale(1.0);
        ca.CAViewAnimation.commitAnimations();
    },
    collectionViewDidDeselectCellAtIndexPath: function(collectionView, section, row, item)
    {

    },
    collectionCellAtIndex: function(collectionView, cellSize, section, row, item)
    {
        if (row * 3 + item >= this.colorArr.length)
        {
            return null;
        }

        var _size = ca.size(0,0);
        var p_Cell = collectionView.dequeueReusableCellWithIdentifier("CrossApp");
        if (p_Cell == null)
        {
            p_Cell = ca.CACollectionViewCell.create("CrossApp");

            var itemImage = ca.CAView.createWithLayout(DLayoutFill);
            itemImage.setTag(99);
            p_Cell.getContentView().addSubview(itemImage);

            var itemText = ca.CALabel.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_B(50, 50)));
            itemText.setTag(100);
            itemText.setFontSize(29);
            itemText.setTextAlignment(ca.CATextAlignment.Center);
            itemText.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
            p_Cell.getContentView().addSubview(itemText);
        }

        var itemImageView = p_Cell.getContentView().getSubviewByTag(99);
        itemImageView.setColor(this.colorArr[row * 3 + item]);
        log("row = "+item);


        var pos= section+""+row+""+item;
        var itemText = p_Cell.getContentView().getSubviewByTag(100);
        itemText.setText(pos);

        return p_Cell;
    },
    numberOfSections: function(collectionView)
    {
        return 1;
    },
    numberOfRowsInSection: function(collectionView,section)
    {
        return (this.colorArr.length % 3 == 0 ? this.colorArr.length / 3 : this.colorArr.length / 3 + 1);
    },
    numberOfItemsInRowsInSection: function(collectionView, section, row)
    {
        return 3;
    },
    collectionViewHeightForRowAtIndexPath: function(collectionView, section, row)
    {
        //return (this.getView().getBounds().size.width - 20 * 4) / 3;
        return (ca.winSize.width - 20 * 4) /3;
    },




});
