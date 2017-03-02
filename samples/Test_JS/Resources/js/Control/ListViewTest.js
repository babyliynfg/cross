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


var ListViewTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();

        //this.getView().setColor(ca.color._getGray());
        var p_ListView = ca.CAListView.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_B(130, 0)));
        p_ListView.setListViewDelegate(listViewDategate);
        p_ListView.setListViewDataSource(listViewDataSource);
        p_ListView.setAllowsSelection(true);
        p_ListView.setAllowsMultipleSelection(false);
        //p_ListView.setOrientation(ca.CAListView.Vertical);
        p_ListView.setShowsScrollIndicators(true);
        p_ListView.setSeparatorViewHeight(30);

        p_ListView.setSeparatorColor(ca.color._getGray());
        this.getView().addSubview(p_ListView);
    },
});