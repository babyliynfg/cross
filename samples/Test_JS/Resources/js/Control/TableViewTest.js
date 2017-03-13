/**
 * Created by zhanglei on 16/8/8.
 */

var ETableViewCell = ca.CAView.extend({
    ctor: function () {
        this._super();
    }
});

var ETableView = ca.CATableViewCell.extend({
    ctor: function () {
        this._super();
    }
});


var TableViewTest = ca.CAViewController.extend({
    sectionTitle:null,
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());

        this.sectionTitle = new Array();
        this.sectionTitle.push("A");
        this.sectionTitle.push("B");
        this.sectionTitle.push("C");
        this.sectionTitle.push("D");
        this.sectionTitle.push("E");
        this.sectionTitle.push("F");
        this.sectionTitle.push("G");
        this.sectionTitle.push("H");
        this.sectionTitle.push("I");
        this.sectionTitle.push("J");
        this.sectionTitle.push("K");
        this.sectionTitle.push("L");
        this.sectionTitle.push("M");
        this.sectionTitle.push("N");
        this.sectionTitle.push("O");
        this.sectionTitle.push("P");
        this.sectionTitle.push("Q");
        this.sectionTitle.push("R");
        this.sectionTitle.push("S");
        this.sectionTitle.push("T");
        this.sectionTitle.push("U");
        this.sectionTitle.push("V");
        this.sectionTitle.push("W");
        this.sectionTitle.push("X");
        this.sectionTitle.push("Y");
        this.sectionTitle.push("Z");

        showIndex = 0;

        var p_TableView = ca.CATableView.createWithLayout(DLayout(DHorizontalLayout_L_R(0, 0), DVerticalLayoutFill));
        p_TableView.setTableViewDataSource(this);
        p_TableView.setTableViewDelegate(this);
        p_TableView.setAllowsSelection(true);
        p_TableView.setAllowsMultipleSelection(false);
        p_TableView.setShowsScrollIndicators(false);
        p_TableView.setSelectRowAtIndexPath(2, 1);

        this.getView().addSubview(p_TableView);


    },
    tableViewDidSelectRowAtIndexPath: function(table, section ,row)
    {

    },
    tableViewDidDeselectRowAtIndexPath: function( table, section ,row)
    {

    },
    tableCellAtIndex: function( table, cellSize, section ,row)
    {
        var _size = cellSize;
        var cell = table.dequeueReusableCellWithIdentifier("CrossApp");
        if (cell == null)
        {
            cell = ca.CATableViewCell.create("CrossApp");
            var image = ca.CAImageView.createWithLayout(DLayoutFill);
            image.setImage(ca.CAImage.create("source_material/second_2.png"));
            cell.addSubview(image);

            var cellText = ca.CALabel.createWithLayout(DLayout(DHorizontalLayout_L_R(150, 10), DVerticalLayout_T_B(10, 10)));
            cellText.setTag(100);
            cellText.setFontSize(30);
            cellText.setTextAlignment(ca.CATextAlignment.Left);
            cellText.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
            cell.addSubview(cellText);
        }
        var cellText = cell.getSubviewByTag(100);
        cellText.setText(this.sectionTitle[section]+"-"+row);
        return cell;

    }
    ,tableViewSectionViewForHeaderInSection: function( table, viewSize ,section)
    {
        var head = this.sectionTitle[section];
        var view = ca.CAView.createWithColor(ca.color._getGray());

        var _size = viewSize;
        var header = ca.CALabel.createWithLayout(DLayout(DHorizontalLayout_L_R(50, 0), DVerticalLayoutFill));
        header.setText(head);
        header.setFontSize(30);
        header.setColor(ca.WHITE);
        header.setTextAlignment(ca.CATextAlignment.Left);
        header.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
        view.addSubview(header);

        return view;
    }
    ,tableViewSectionViewForFooterInSection: function( table, viewSize ,section)
    {
        var view = ca.CAView.createWithColor(ca.color._getGray());
        return view;
    }
    ,numberOfRowsInSection: function(table, section)
    {
        return 2;
    }
    ,numberOfSections: function(table)
    {
        return this.sectionTitle.length;
    }
    ,tableViewHeightForRowAtIndexPath: function( table,section, row)
    {
        return 130;
    }
    ,tableViewHeightForHeaderInSection: function( table, section)
    {
        return 50;
    }
    ,tableViewHeightForFooterInSection: function( table, section)
    {
        return 1;
    }

});
