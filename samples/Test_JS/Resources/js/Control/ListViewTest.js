/**
 * Created by zhanglei on 16/8/8.
 */
//事件代理
var listViewDategate = {
    listViewDidSelectCellAtIndex: function (listView, index) {
    },
    listViewDidDeselectCellAtIndex: function (listView, index) {
    }
};

//数据代理
var listViewDataSource = {
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

            var test = ca.CALabel.createWithLayout(DLayout(DHorizontalLayout_L_W(0, 200), DVerticalLayoutFill));
            test.setColor(ca.color(51, 204, 255, 255));
            test.setTextAlignment(ca.CATextAlignment.Center);
            test.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
            test.setFontSize(28);
            test.setTag(100);
            cell.addSubview(test);

            var btn = ca.CAButton.createWithLayout(DLayout(DHorizontalLayout_W_C(100, 0.85), DVerticalLayout_H_C(50, 0.5)), ca.CAButton.Type.SquareRect);
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


//事件代理
var CDlistViewDategate = {
    listViewDidSelectCellAtIndex: function (listView, index) {
    },
    listViewDidDeselectCellAtIndex: function (listView, index) {
    }
};

//数据代理
var CDlistViewDataSource = {
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

            var test = ca.CALabel.createWithLayout(DLayoutFill);
            test.setColor(ca.color(51, 204, 255, 255));
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

        var cdListView = ca.CAListView.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H(0, 120)));
        cdListView.setListViewDelegate(CDlistViewDategate);
        cdListView.setListViewDataSource(CDlistViewDataSource);
        cdListView.setAllowsSelection(true);
        cdListView.setAllowsMultipleSelection(false);
        cdListView.setOrientation(2); //(ca.CAListView.orientation.horizontal);
        // cdListView.setShowsScrollIndicators(false);
        cdListView.setShowsHorizontalScrollIndicator(false);
        cdListView.setSeparatorColor(ca.CAColor4F.CLEAR);
        this.getView().addSubview(cdListView);


        // var cdListView = ca.CAListView.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H(0, 120)));
        // cdListView.setListViewDelegate(CDlistViewDategate);
        // cdListView.setListViewDataSource(CDlistViewDataSource);
        // cdListView.setAllowsSelection(true);
        // cdListView.setAllowsMultipleSelection(false);
        // cdListView.setOrientation(ca.CAListView.Orientation.Horizontal);
        // //cdListView.setShowsHorizontalScrollIndicator(false);
        // cdListView.setShowsScrollIndicators(false);
        // // cdListView.setSeparatorColor(ca.color.clear);
        // this.getView().addSubview(cdListView);

        this.getView().addSubview(ca.CAView.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H(120, 5)), ca.color._getGreen()));

        var ListView = ca.CAListView.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_B(130, 0)));
        ListView.setListViewDelegate(listViewDategate);
        ListView.setListViewDataSource(listViewDataSource);
        ListView.setAllowsSelection(true);
        ListView.setAllowsMultipleSelection(false);
        // ListView.setOrientation(ca.CAListView.Vertical);
        ListView.setShowsScrollIndicators(true);
        ListView.setSeparatorViewHeight(30);
        ListView.setSeparatorColor(ca.color._getGray());
        this.getView().addSubview(ListView);
    },
});