/**
 * Created by crossApp on 16/8/8.
 */

var AutoCollectionViewHorizontalTest = ca.CAViewController.extend({

    ctor: function () {
        this._super();
    },

    viewDidLoad: function() {

        this.HorizontalcolorArr = new Array();
        for (var i = 0; i < 60; i++)
        {
            var r = Math.floor(Math.random()*255);
            var g = Math.floor(Math.random()*255);
            var b = Math.floor(Math.random()*255);

            this.HorizontalcolorArr.push(ca.CAColor4B.set(r, g, b, 255));
        }
        this.AutoCollectionViewHorizontalNum = 0;
        if (this.AutoCollectionViewHorizontalNum == 0)
        {
            this.autoCollection = ca.CAAutoCollectionView.createWithLayout(ca.DLayoutFill);
            this.autoCollection.setAllowsSelection(true);
            this.autoCollection.setAllowsMultipleSelection(true);
            this.autoCollection.setOrientation(ca.CAAutoCollectionView.Orientation.Horizontal);
            this.autoCollection.setHoriCellInterval(20);
            this.autoCollection.setVertCellInterval(20);
            this.autoCollection.setDidSelectCellAtIndexPathCallback(this.collectionViewDidSelectCellAtIndexPath.bind(this));
            this.autoCollection.setCellAtIndexPathCallback(this.collectionCellAtIndex.bind(this));
            this.autoCollection.setCellSizeAtIndexPathCallback(this.collectionViewSizeForItemAtIndexPath.bind(this));
            this.autoCollection.setNumberOfItemsAtIndexPathCallback(this.numberOfItemsInSection.bind(this));
            this.autoCollection.setNumberOfSectionsCallback(this.numberOfSections.bind(this));

            this.getView().addSubview(this.autoCollection);

        }
    },

    collectionViewDidSelectCellAtIndexPath: function(section, item)
    {
        var cell = this.autoCollection.cellForRowAtIndexPath(section, item);
        cell.getContentView().setRotation(-360);
        cell.getContentView().setScale(0.5);
        ca.CAViewAnimation.beginAnimations("");
        cell.getContentView().setRotation(0);
        cell.getContentView().setScale(1.0);
        ca.CAViewAnimation.commitAnimations();
    },
    collectionCellAtIndex: function(cellSize, section, item)
    {
        var p_Cell = this.autoCollection.dequeueReusableCellWithIdentifier("cell");

        if (p_Cell == null)
        {
            p_Cell = ca.CACollectionViewCell.create("cell");

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
        ca.log("row = "+ item);


        var itemText = p_Cell.getContentView().getSubviewByTag(100);
        itemText.setText("("+section+","+item+")");
        return  p_Cell;

    },

    collectionViewSizeForItemAtIndexPath: function( collectionView, section, item)
    {
        return ca.DSize.set(230, 230);
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
