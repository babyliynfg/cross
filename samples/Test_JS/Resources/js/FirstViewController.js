

var FirstViewController = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        this._array =
        [
            //控件名                             //控件icon                          //控件展示
            ["AlertView",                       "image/AlertView.png",              "AlertViewTest()"],
            ["Button",                          "image/button.png",                 "ButtonTest()"],
            ["Checkbox",                        "image/Checkbox.png",               "CheckboxTest()"],
            ["SegmentedControl",                "image/SegmentedControl.png",       "SegmentedControlTest()"],
            ["ImageView",                       "image/ImageView.png",              "ImageViewTest()"],
            ["Scale9ImageView",                 "image/Scale9ImageView.png",        "Scale9ImageViewTest()"],
            ["IndicatorView",                   "image/indicatorView.png",          "ActivityIndicatorViewTest()"],
            ["Progress",                        "image/Progress.png",               "ProgressTest()"],
            ["Slider",                          "image/slider.png",                 "SliderTest()"],
            ["Switch",                          "image/Switch.png",                 "SwitchTest()"],
            ["Stepper",                         "image/Stepper.png",                "StepperTest()"],
            ["Label",                           "image/Label.png",                  "LabelTest()"],
            ["TextField",                       "image/TextField.png",              "TextFieldTest()"],
            ["TextView",                        "image/TextView.png",               "TextViewTest()"],
            ["TabBar",                          "image/TabBar.png",                 "TabBarControllerTest()"],
            ["PageView",                        "image/PageView.png",               "PageViewTest()"],
            ["PageControl",                     "image/PageControl.png",            "PageControlTest()"],
            ["ScrollView",                      "image/ScrollView.png",             "ScrollViewTest()"],
            ["AutoCollectionView (Vertical)",    "image/CollectionView.png",        "AutoCollectionViewVerticalTest()"],
            ["AutoCollectionView (Horizontal)",  "image/CollectionView.png",        "AutoCollectionViewHorizontalTest()"],
            ["CollectionView",                  "image/CollectionView.png",         "CollectionViewTest()"],
            ["WaterfallView",                   "image/CollectionView.png",         "WaterfallViewTest()"],
            ["ListView",                        "image/ListView.png",               "ListViewTest()"],
            ["TableView",                       "image/TableView.png",              "TableViewTest()"],
            ["PickerView",                      "image/PickerView.png",             "PickerViewTest()"],
            ["WebView",                         "image/WebView.png",                "WebViewTest()"],
            ["GifView",                         "image/GifView.png",                "GifViewTest()"],
            ["VideoPlayer",                     "image/Video.png",                  "VideoPlayerControlViewTest()"],
            ["RenderImage",                     "image/RenderImage.png",            "RenderImageTest()"],
            ["Animation",                       "image/Video.png",                  "ViewAnimationTest()"]
        ];
    },
    viewDidLoad: function() {

        this._collectionView = ca.CAAutoCollectionView.createWithLayout(ca.DLayoutFill);
        this._collectionView.setAllowsSelection(true);
        this._collectionView.setHoriCellInterval(3);
        this._collectionView.setVertCellInterval(3);

        this.getView().addSubview(this._collectionView);

        this._collectionView.setDidSelectRowAtIndexPathCallback(this.collectionViewDidSelectCellAtIndexPath.bind(this));
        this._collectionView.setCellAtIndexPathCallback(this.collectionCellAtIndex.bind(this));
        this._collectionView.setSizeForItemAtIndexPath(this.collectionViewSizeForItemAtIndexPath.bind(this));
        this._collectionView.setNumberOfItemsInSectionCallback(this.numberOfItemsInSection.bind(this));
        this._collectionView.setNumberOfSectionsCallback(this.numberOfSections.bind(this));
    },
    collectionViewDidSelectCellAtIndexPath: function (section, item)
    {
        var viewController = eval("new " + this._array[item][2]);
        viewController.init();
        ca.RootWindow.getRootNavigationController().pushViewController(viewController, true);
        viewController.getView().setColor(ca.CAColor4B.GRAY);
        viewController.release();
    },
    collectionCellAtIndex: function (cellSize, section, item)
    {
        var cell = this._collectionView.dequeueReusableCellWithIdentifier("CrossApp");
        if (cell == null)
        {
            cell = ca.CACollectionViewCell.create("CrossApp");
            cell.setAllowsSelected(false);

            var background = ca.CAView.createWithColor(ca.CAColor4B.set(240, 240, 240, 255));
            background.setLayout(ca.DLayoutFill);
            cell.getContentView().addSubview(background);

            var label = ca.CALabel.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(0,0), ca.DVerticalLayout_B_H(5,80)));
            label.setTextTag("label");
            label.setFontSize(24);
            label.setColor(ca.CAColor4B.set(34, 151, 254, 255));
            label.setTextAlignment(ca.CATextAlignment.Center);
            label.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
            cell.getContentView().addSubview(label);

            var imageView = ca.CAImageView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(30,30), ca.DVerticalLayout_T_H(20, 123)));
            imageView.setScaleType(ca.CAImageView.ScaleType.FitImageInside);
            imageView.setTextTag("imageView");
            imageView.setScale(0.6);
            cell.getContentView().addSubview(imageView);
        }

        var label = cell.getContentView().getSubviewByTextTag("label");
        label.setText(this._array[item][0]);

        var imageView = cell.getContentView().getSubviewByTextTag("imageView");
        imageView.setImage(ca.CAImage.create(this._array[item][1]));

        return cell;
    },
    collectionViewSizeForItemAtIndexPath: function (section, item)
    {
        return ca.DSize.set(230, 230);
    },
    numberOfItemsInSection: function (section)
    {
        return this._array.length;
    },
    numberOfSections: function (collectionView)
    {
        return 1;
    },
});
