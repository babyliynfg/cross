/**
 * Created by crossApp on 16/8/8.
 */
//事件代理
var listViewDategate = {
    listViewDidSelectCellAtIndex: function (listView, index) {
    },
    listViewDidDeselectCellAtIndex: function (listView, index) {
    }
};

//数据代理
var listView1DataSource = {
    numberOfIndex: function (listView) {
        return 30;
    },
    listViewHeightForIndex: function (listView, index) {
        return 100;
    },
    listViewCellAtIndex: function (listView, cellSize, index) {
        var size = cellSize;

        log(cellSize.width + "listViewCellAtIndex");
        var cell = listView.dequeueReusableCellWithIdentifier("ListViewCell");
        if (cell == null) {
            cell = ca.CAListViewCell.create("ListViewCell");

            var test = ca.CALabel.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_W(0, 200), ca.DVerticalLayoutFill));
            test.setColor(ca.CAColor4B.set(51, 204, 255, 255));
            test.setTextAlignment(ca.CATextAlignment.Center);
            test.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
            test.setFontSize(28);
            test.setTag(100);
            cell.addSubview(test);

            var btn = ca.CAButton.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(100, 0.85), ca.DVerticalLayout_H_C(50, 0.5)), ca.CAButton.Type.SquareRect);
            btn.setTitleForState(ca.CAControl.State.Normal, "btn");
            btn.setTag(200);
            cell.addSubview(btn);
            btn.setTouchEventScrollHandOverToSuperview(false);
        }

        var test = cell.getSubviewByTag(100);
        test.setText("cell-"+index);
        return cell;
    },
    listViewWillDisplayCellAtIndex: function (listView, cell, index) {
        log("listViewWillDisplayCellAtIndex");

        return 0;
    }
};


//数据代理
var listView2DataSource = {
    numberOfIndex: function (listView) {
        return 20;
    },
    listViewHeightForIndex: function (listView, index) {
        return 150;
    },
    listViewCellAtIndex: function (listView, cellSize, index) {
        var size = cellSize;

        log(cellSize.width + "listViewCellAtIndex");
        var cell = listView.dequeueReusableCellWithIdentifier("CDListViewCell");
        if (cell == null) {
            cell = ca.CAListViewCell.create("CDListViewCell");

            var test = ca.CALabel.createWithLayout(ca.DLayoutFill);
            test.setColor(ca.CAColor4B.set(51, 204, 255, 255));
            test.setTextAlignment(ca.CATextAlignment.Center);
            test.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
            test.setFontSize(28);
            test.setTag(100);
            cell.addSubview(test);
        }

        var test = cell.getSubviewByTag(100);
        test.setText("cell-"+index);
        return cell;
    },
    listViewWillDisplayCellAtIndex: function (listView, cell, index) {
        log("listViewWillDisplayCellAtIndex");

        return 0;
    }
};


var ListViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        var listview1 = ca.CAListView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayoutFill, ca.DVerticalLayout_T_H(0, 120)));
        //listview1.setListViewDelegate(listViewDategate);
        //listview1.setListViewDataSource(listView1DataSource);


        listview1.setDidSelectCellAtIndexPathCallback(listViewDategate.listViewDidSelectCellAtIndex.bind(listViewDategate));
        listview1.setDidDeselectCellAtIndexPathCallback(listViewDategate.listViewDidDeselectCellAtIndex.bind(listViewDategate));
        listview1.setNumberOfIndexPathCallback(listView1DataSource.numberOfIndex.bind(listView1DataSource));
        listview1.setHeightForIndexPathCallback(listView1DataSource.listViewHeightForIndex.bind(listView1DataSource));
        listview1.setCellAtIndexPathCallBack(listView1DataSource.listViewCellAtIndex.bind(listView1DataSource))
        listview1.setWillDisplayCellAtIndexPathCallback(listView1DataSource.listViewWillDisplayCellAtIndex.bind(listView1DataSource)) ;



        listview1.setAllowsSelection(true);
        listview1.setAllowsMultipleSelection(false);
        listview1.setOrientation(ca.CAListView.Orientation.Horizontal); //(ca.CAListView.orientation.horizontal);
        listview1.setShowsHorizontalScrollIndicator(false);
        listview1.setSeparatorColor(ca.CAColor4F.CLEAR);
        this.getView().addSubview(listview1);


        //this.getView().addSubview(ca.CAView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayoutFill, ca.DVerticalLayout_T_H(120, 5)), ca.CAColor4B.GRAY));
        //
        //var listview2 = ca.CAListView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayoutFill, ca.DVerticalLayout_T_B(130, 0)));
        //listview2.setListViewDelegate(listViewDategate);
        //listview2.setListViewDataSource(listView2DataSource);
        //listview2.setAllowsSelection(true);
        //listview2.setAllowsMultipleSelection(false);
        //listview2.setOrientation(ca.CAListView.Orientation.Vertical);
        //listview2.setShowsScrollIndicators(true);
        //listview2.setSeparatorViewHeight(30);
        //listview2.setSeparatorColor(ca.CAColor4B.GRAY);
        //this.getView().addSubview(listview2);
    },
    viewDidLoad: function() {
    },
});