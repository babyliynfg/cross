require('js/Control/ActivityIndicatorViewTest.js');
require('js/Control/AlertViewTest.js');
require('js/Control/AutoCollectionViewHorizontalTest.js');
require('js/Control/AutoCollectionViewVerticalTest.js');
require('js/Control/ButtonTest.js');
require('js/Control/CollectionViewTest.js');
require('js/Control/GifViewTest.js');
require('js/Control/ImageViewTest.js');
require('js/Control/LabelTest.js');
require('js/Control/ListViewTest.js');
require('js/Control/PageViewTest.js');
require('js/Control/PickerViewTest.js');
require('js/Control/ProgressTest.js');
require('js/Control/RenderImageTest.js');
require('js/Control/Scale9ImageViewTest.js');
require('js/Control/ScrollViewTest.js');
require('js/Control/SegmentedControlTest.js');
require('js/Control/SliderTest.js');
require('js/Control/StepperTest.js');
require('js/Control/SwitchTest.js');
require('js/Control/TabBarControllerTest.js');
require('js/Control/TableViewTest.js');
require('js/Control/TextFieldTest.js');
require('js/Control/TextViewTest.js');
require('js/Control/VideoPlayerControlViewTest.js');
require('js/Control/ViewAnimationTest.js');
require('js/Control/WebViewTest.js');
require('js/Control/WaterfallViewTest.js');

require('js/CDUIShowAutoCollectionView.js');

var RootWindow = ca.CAWindow.extend(
    {
        m_pRootNavigationController:null,
        ctor: function () {
            this._super();

            this.initUIVIew();

            //var alertViewTest = new AlertViewTest();
            //alertViewTest.init();
            //this.setRootViewController(alertViewTest);


            //var buttonTest = new ButtonTest();
            //buttonTest.init();
            //this.setRootViewController(buttonTest);

            //******
            //var collectionViewTest = new CollectionViewTest();
            //collectionViewTest.init();
            //this.setRootViewController(collectionViewTest);

            //var flashViewTest = new FlashViewTest();
            //flashViewTest.init();
            //this.setRootViewController(flashViewTest);

            //var gifViewTest = new GifViewTest();
            //gifViewTest.init();
            //this.setRootViewController(gifViewTest);


            //var imageView = new ImageViewTest();
            //imageView.init();
            //this.setRootViewController(imageView);

            //var labelTest = new LabelTest();
            //labelTest.init();
            //this.setRootViewController(labelTest);

            //var listViewTest = new ListViewTest();
            //listViewTest.init();
            //this.setRootViewController(listViewTest);

            //var pageViewTest = new PageViewTest();
            //pageViewTest.init();
            //this.setRootViewController(pageViewTest);


            //var pickerViewTest = new PickerViewTest();
            //pickerViewTest.init();
            //this.setRootViewController(pickerViewTest);

            //var progpressTest = new ProgressTest();
            //progpressTest.init();
            //this.setRootViewController(progpressTest);


            //var scale9ImageViewTest = new Scale9ImageViewTest();
            //scale9ImageViewTest.init();
            //this.setRootViewController(scale9ImageViewTest);


            //var scrollViewTest = new ScrollViewTest();
            //scrollViewTest.init();
            //this.setRootViewController(scrollViewTest);

            //var segmentedControlTest = new SegmentedControlTest();
            //segmentedControlTest.init();
            //this.setRootViewController(segmentedControlTest);

            //var sliderTest = new SliderTest();
            //sliderTest.init();
            //this.setRootViewController(sliderTest);

            //var stepperTest = new StepperTest();
            //stepperTest.init();
            //this.setRootViewController(stepperTest);

            //var switchTest = new SwitchTest();
            //switchTest.init();
            //this.setRootViewController(switchTest);

            //var tabBarControllerTest = new TabBarControllerTest();
            //tabBarControllerTest.init();
            //this.setRootViewController(tabBarControllerTest);

            //var tableViewTest = new TableViewTest();
            //tableViewTest.init();
            //this.setRootViewController(tableViewTest);

            //var textFieldTest = new TextFieldTest();
            //textFieldTest.init();
            //this.setRootViewController(textFieldTest);

            //var textViewTest = new TextViewTest();
            //textViewTest.init();
            //this.setRootViewController(textViewTest);

            //var videoPlayerControlViewTest = new VideoPlayerControlViewTest();
            //videoPlayerControlViewTest.init();
            //this.setRootViewController(videoPlayerControlViewTest);

            //var webViewTest = new WebViewTest();
            //webViewTest.init();
            //this.setRootViewController(webViewTest);




        },
        initUIVIew:function(){
            var tabBarController = new CDUIShowAutoCollectionView();
            tabBarController.init();
            //tabBarController.autorelease();


            var temp_nav = ca.CANavigationBarItem.create("控件展示");
            var item = ca.CABarButtonItem.create("", ca.CAImage.create("image/ic_category_list.png"), null);
            item.setCallbackFunction(function () {

            });
            temp_nav.addLeftButtonItem(item);
            tabBarController.setNavigationBarItem(temp_nav);

            if (this.m_pRootNavigationController)
            {
                this.m_pRootNavigationController.replaceViewController(tabBarController, false);
            }
            else
            {
                this.m_pRootNavigationController = new ca.CANavigationController();
                this.m_pRootNavigationController.initWithRootViewController(tabBarController);
                this.m_pRootNavigationController.setNavigationBarBackgroundImage(ca.CAImage.create("image/navbg.jpg"));
            }

            this.setRootViewController(this.m_pRootNavigationController);

        },
        getRootNavigationController:function(){

            return this.m_pRootNavigationController;
        }
    }
);
