/**
 * Created by zhanglei on 16/8/8.
 */
var AutoCollectionViewVerticalTest = ca.CAViewController.extend({
        HorizontalcolorArr:null,
        AutoCollectionViewHorizontalNum:null,
        footerRefreshView:null,
        headerRefreshView:null,
        p_AutoCollection:null,
        ctor: function () {
            this._super();

            this.HorizontalcolorArr = new Array();

            for (var i = 0; i < 60; i++)
            {
                var r = Math.floor(Math.random()*255);
                var g = Math.floor(Math.random()*255);
                var b = Math.floor(Math.random()*255);

                this.HorizontalcolorArr.push(ca.color(r, g, b, 255));
            }

            this.AutoCollectionViewHorizontalNum = 0;

            this.headerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Header);
            this.footerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Footer);

            if (this.AutoCollectionViewHorizontalNum == 0)
            {
                this.p_AutoCollection = ca.CAAutoCollectionView.createWithLayout(DLayoutFill);
                this.p_AutoCollection.setAllowsSelection(true);
                this.p_AutoCollection.setAllowsMultipleSelection(true);
                this.p_AutoCollection.setCollectionViewDelegate(this);
                this.p_AutoCollection.setCollectionViewDataSource(this);
                this.p_AutoCollection.setOrientation(1);
                // this.p_AutoCollection.setHeaderRefreshView(this.headerRefreshView);
                // this.p_AutoCollection.setFooterRefreshView(this.footerRefreshView);
                // this.p_AutoCollection.setScrollViewDelegate(this);
                this.p_AutoCollection.setHoriCellInterval(20);
                this.p_AutoCollection.setVertCellInterval(20);
                this.getView().addSubview(this.p_AutoCollection);
            }
            else
            {
                //EAutoCollectionViewHorizontal* p_AutoCollection1 = EAutoCollectionViewHorizontal.createWithLayout(DLayoutFill);
                //p_AutoCollection1.init();
                //p_AutoCollection1.setEAutoCollectionViewHorizontalDelegate(this);
                //this.getView().addSubview(p_AutoCollection1);
            }

        },
        refreshData1: function( interval){
            this.colorArr = [];
            for (var i = 0; i < 40; i++)
            {
                var r = Math.floor(Math.random()*255);
                var g = Math.floor(Math.random()*255);
                var b = Math.floor(Math.random()*255);
                this.HorizontalcolorArr.push(ca.color(r, g, b, 255));
            }
            this.p_AutoCollection.reloadData();
        },
        refreshData2: function(interval){
            for (var i = 0; i < 40; i++)
            {
                var r = Math.floor(Math.random()*255);
                var g = Math.floor(Math.random()*255);
                var b = Math.floor(Math.random()*255);
                this.HorizontalcolorArr.push(ca.color(r, g, b, 255));
            }
            this.p_AutoCollection.reloadData();
        },
        scrollViewHeaderBeginRefreshing: function( view)
        {
            ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this, this.refreshData1, 0.5, 0, 0);
        },
        scrollViewFooterBeginRefreshing: function( view)
        {
            ca.CAScheduler.getScheduler().scheduleCallbackForTarget(this, this.refreshData2, 0.5, 0, 0);
        },
        collectionViewDidSelectCellAtIndexPath: function(collectionView, section, item)
        {
            var cell = collectionView.cellForRowAtIndexPath(section, item);
            cell.getContentView().setRotation(-360);
            cell.getContentView().setScale(0.5);
            ca.CAViewAnimation.beginAnimations("");
            cell.getContentView().setRotation(0);
            cell.getContentView().setScale(1.0);
            ca.CAViewAnimation.commitAnimations();
        },

        collectionViewDidDeselectCellAtIndexPath: function (collectionView, section, item)
        {
        },

        collectionCellAtIndex: function(collectionView,  cellSize, section, item)
        {
            var p_Cell = collectionView.dequeueReusableCellWithIdentifier("CrossApp");

            if (p_Cell == null)
            {
                p_Cell = ca.CACollectionViewCell.create("CrossApp");

                var itemImage = ca.CAView.createWithLayout(DLayoutFill);
                itemImage.setTag(99);
                p_Cell.getContentView().addSubview(itemImage);

                var itemText = ca.CALabel.createWithLayout(DLayoutFill);
                itemText.setTag(100);
                itemText.setFontSize(29);
                itemText.setTextAlignment(ca.CATextAlignment.Center);
                itemText.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
                p_Cell.getContentView().addSubview(itemText);
            }

            var itemImageView = p_Cell.getContentView().getSubviewByTag(99);
            itemImageView.setColor(this.HorizontalcolorArr[item]);
            log("row = "+ item);


            var itemText = p_Cell.getContentView().getSubviewByTag(100);
            itemText.setText("(%"+section+","+item+")");
            return  p_Cell;

        },

        collectionViewSizeForItemAtIndexPath: function( collectionView, section, item)
        {
            return ca.dsize(230, 230);
        },

        numberOfItemsInSection: function(collectionView, section)
        {
            return this.HorizontalcolorArr.length;
        },
        numberOfSections: function(collectionView)
        {
            return 1;
        }

    });
