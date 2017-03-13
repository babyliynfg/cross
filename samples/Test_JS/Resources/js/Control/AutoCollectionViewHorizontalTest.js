/**
 * Created by zhanglei on 16/8/8.
 */

var AutoCollectionViewHorizontalTest = ca.CAViewController.extend({
    HorizontalcolorArr:null,
    AutoCollectionViewHorizontalNum:null,
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());
        this.HorizontalcolorArr = new Array();
        for (var i = 0; i < 60; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);

            this.HorizontalcolorArr.push(ca.color(r, g, b, 255));
        }
        this.AutoCollectionViewHorizontalNum = 0;
        if (this.AutoCollectionViewHorizontalNum == 0)
        {
            var p_AutoCollection = ca.CAAutoCollectionView.createWithLayout(DLayoutFill);
            p_AutoCollection.setAllowsSelection(true);
            p_AutoCollection.setAllowsMultipleSelection(true);
            p_AutoCollection.setCollectionViewDelegate(this);
            p_AutoCollection.setCollectionViewDataSource(this);
            p_AutoCollection.setOrientation(0);
            //p_AutoCollection.setScrollViewDelegate(this);
            p_AutoCollection.setHoriCellInterval(20);
            p_AutoCollection.setVertCellInterval(20);
            this.getView().addSubview(p_AutoCollection);
        }
        else
        {
            //EAutoCollectionViewHorizontal* p_AutoCollection1 = EAutoCollectionViewHorizontal.createWithLayout(DLayoutFill);
            //p_AutoCollection1.init();
            //p_AutoCollection1.setEAutoCollectionViewHorizontalDelegate(this);
            //this.getView().addSubview(p_AutoCollection1);
        }

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
