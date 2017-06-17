/**
 * Created by crossApp on 16/8/8.
 */
var AutoCollectionViewVerticalTest = ca.CAViewController.extend({

        ctor: function () {
            this._super();

            this.HorizontalcolorArr = new Array();
            this._randomColor() ;

        },

        viewDidLoad: function() {
            this.headerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Header);
            this.footerRefreshView = ca.CAPullToRefreshView.create(ca.CAPullToRefreshView.Type.Footer);

            this.p_AutoCollection = ca.CAAutoCollectionView.createWithLayout(ca.DLayoutFill);
            this.p_AutoCollection.setAllowsSelection(true);
            this.p_AutoCollection.setAllowsMultipleSelection(true);
            this.p_AutoCollection.setHeaderRefreshView(this.headerRefreshView) ;
            this.p_AutoCollection.setFooterRefreshView(this.footerRefreshView) ;

            this.p_AutoCollection.setDidSelectRowAtIndexPathCallback(this.collectionViewDidSelectCellAtIndexPath.bind(this));
            this.p_AutoCollection.setCellAtIndexPathCallback(this.collectionCellAtIndex.bind(this));
            this.p_AutoCollection.setSizeForItemAtIndexPath(this.collectionViewSizeForItemAtIndexPath.bind(this));
            this.p_AutoCollection.setNumberOfItemsInSectionCallback(this.numberOfItemsInSection.bind(this));
            this.p_AutoCollection.setNumberOfSectionsCallback(this.numberOfSections.bind(this));
            this.p_AutoCollection.setHeaderBeginRefreshingCallback(this.scrollViewHeaderBeginRefreshing.bind(this)) ;
            this.p_AutoCollection.setFooterBeginRefreshingCallback(this.scrollViewFooterBeginRefreshing.bind(this)) ;

            this.p_AutoCollection.setHoriCellInterval(20);
            this.p_AutoCollection.setVertCellInterval(20);
            this.getView().addSubview(this.p_AutoCollection);

        },


        _randomColor:function(){
            for (var i = 0; i < 60; i++)
            {
                var r = Math.floor(Math.random()*255);
                var g = Math.floor(Math.random()*255);
                var b = Math.floor(Math.random()*255);

                this.HorizontalcolorArr.push(ca.CAColor4B.set(r, g, b, 255));
            }
        },

        refreshDataHeader: function( interval){
            this._randomColor() ;
            this.p_AutoCollection.reloadData();

            ca.log("refreshDataHeader --> ");

        },
        refreshDataFooter: function(interval){
            this._randomColor() ;
            this.p_AutoCollection.reloadData();
        },

        scrollViewHeaderBeginRefreshing: function()
        {
            ca.log("scrollViewHeaderBeginRefreshing");
            ca.CAScheduler.getScheduler().schedule(this, this.refreshDataHeader, 0.5, 0, 0);
        },
        scrollViewFooterBeginRefreshing: function()
        {
            ca.CAScheduler.getScheduler().schedule(this, this.refreshDataFooter, 0.5, 0, 0);
        },
        collectionViewDidSelectCellAtIndexPath: function( section, item)
        {
            var cell = this.p_AutoCollection.cellForRowAtIndexPath(section, item);
            cell.getContentView().setRotation(-360);
            cell.getContentView().setScale(0.5);
            ca.CAViewAnimation.beginAnimations("");
            cell.getContentView().setRotation(0);
            cell.getContentView().setScale(1.0);
            ca.CAViewAnimation.commitAnimations();
        },

        collectionViewDidDeselectCellAtIndexPath: function ( section, item)
        {
        },

        collectionCellAtIndex: function(cellSize, section, item)
        {
            var p_Cell = this.p_AutoCollection.dequeueReusableCellWithIdentifier("CrossApp");

            if (p_Cell == null)
            {
                p_Cell = ca.CACollectionViewCell.create("CrossApp");

                var itemImage = ca.CAView.createWithLayout(ca.DLayoutFill);
                itemImage.setTag(99);
                p_Cell.getContentView().addSubview(itemImage);

                var itemText = ca.CALabel.createWithLayout(ca.DLayoutFill);
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
            itemText.setText("("+section+","+item+")");
            return  p_Cell;

        },

        collectionViewSizeForItemAtIndexPath: function(  section, item)
        {
            return ca.DSize.set(230, 230);
        },

        numberOfItemsInSection: function( section)
        {
            return this.HorizontalcolorArr.length;
        },
        numberOfSections: function()
        {
            return 1;
        }

    });
