/**
 * Created by crossApp on 16/8/4.
 */
var CollectionViewTest = ca.CAViewController.extend({

    ctor: function () {
        this._super();

        this.colorArr = new Array();
        this._randomColor() ;

    },
    viewDidLoad: function() {

        this.headerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Header);
        this.footerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Footer);

        this.p_Conllection = ca.CACollectionView.createWithLayout(ca.DLayoutFill);
        this.p_Conllection.setAllowsSelection(true);

        this.p_Conllection.setHeaderBeginRefreshingCallback(this.scrollViewHeaderBeginRefreshing.bind(this)) ;
        this.p_Conllection.setFooterBeginRefreshingCallback(this.scrollViewFooterBeginRefreshing.bind(this)) ;

        this.p_Conllection.setDidSelectCellAtIndexPathCallback(this.collectionViewDidSelectCellAtIndexPath.bind(this));//<----
        this.p_Conllection.setDidDeselectCellAtIndexPathCallback(this.collectionViewDidDeselectCellAtIndexPath.bind(this));//<----
        this.p_Conllection.setCellAtIndexPathCallBack(this.collectionCellAtIndex.bind(this)) ;//<----

        this.p_Conllection.setNumberOfSectionsCallback(this.numberOfSections.bind(this)) ;
        this.p_Conllection.setNumberOfRowsInSectionCallback(this.numberOfRowsInSection.bind(this));
        this.p_Conllection.setNumberOfItemsInRowsInSectionCallback(this.numberOfItemsInRowsInSection.bind(this)) ;//<----
        this.p_Conllection.setHeightForRowAtIndexPathCallback(ths.collectionViewHeightForRowAtIndexPath.bind(this));

        this.p_Conllection.setHeaderRefreshView(this.headerRefreshView);
        this.p_Conllection.setFooterRefreshView(this.footerRefreshView);
        this.p_Conllection.setHoriInterval(20);
        this.p_Conllection.setVertInterval(20);
        this.getView().addSubview(this.p_Conllection);

        this.p_Conllection.reloadData();
        this.p_Conllection.startPullToHeaderRefreshView();

    },

    refreshData1: function(interval){
        this.colorArr = [];
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.CAColor4B.set(r, g, b, 255));
        }
        this.p_Conllection.reloadData();
    },

    refreshData2: function(interval){
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);
            this.colorArr.push(ca.CAColor4B.set(r, g, b, 255));
        }
        this.p_Conllection.reloadData();
    },


    _randomColor:function(){
        for (var i = 0; i < 40; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);

            this.colorArr.push(ca.CAColor4B.set(r, g, b, 255));
        }
    },

    scrollViewHeaderBeginRefreshing: function()
    {
        ca.CAScheduler.getScheduler().schedule(this, this.refreshData1, 0.5, 0, 0);
    },
    scrollViewFooterBeginRefreshing: function()
    {
        ca.CAScheduler.getScheduler().schedule(this, this.refreshData2, 0.5, 0, 0);
    },
    collectionViewDidSelectCellAtIndexPath: function(section, row, item)
    {
        var cell = this.p_Conllection.cellForRowAtIndexPath(section, row, item);
        cell.getContentView().setRotation(-360);
        cell.getContentView().setScale(0.5);
        ca.CAViewAnimation.beginAnimations("");
        cell.getContentView().setRotation(0);
        cell.getContentView().setScale(1.0);
        ca.CAViewAnimation.commitAnimations();
    },
    collectionViewDidDeselectCellAtIndexPath: function(section, row, item)
    {

    },
    collectionCellAtIndex: function(cellSize, section, row, item)
    {
        if (row * 3 + item >= this.colorArr.length)
        {
            return null;
        }

        var _size = ca.size(0,0);
        var p_Cell = this.p_Conllection.dequeueReusableCellWithIdentifier("cell");
        if (p_Cell == null)
        {
            p_Cell = ca.CACollectionViewCell.create("cell");

            var itemImage = ca.CAView.createWithLayout(ca.DLayoutFill);
            itemImage.setTag(99);
            p_Cell.getContentView().addSubview(itemImage);

            var itemText = ca.CALabel.createWithLayout(ca.DLayout.set(ca.DHorizontalLayoutFill, ca.DVerticalLayout_T_B(50, 50)));
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
    numberOfSections: function()
    {
        return 1;
    },
    numberOfRowsInSection: function(section)
    {
        return (this.colorArr.length % 3 == 0 ? this.colorArr.length / 3 : this.colorArr.length / 3 + 1);
    },
    numberOfItemsInRowsInSection: function( section, row)
    {
        return 3;
    },
    collectionViewHeightForRowAtIndexPath: function(section, row)
    {
        //return (this.getView().getBounds().size.width - 20 * 4) / 3;
        return (ca.winSize.width - 20 * 4) /3;
    },




});
