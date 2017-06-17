/**
 * Created by crossApp on 16/8/8.
 */


var TableViewTest = ca.CAViewController.extend({

    ctor: function () {
        this._super();
    },

    viewDidLoad: function() {
        this.sectionTitle = ["A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"];

        this.p_TableView = ca.CATableView.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(0, 0), ca.DVerticalLayoutFill));

        this.p_TableView.setDidSelectCellAtIndexPathCallback(this.tableViewDidSelectRowAtIndexPath.bind(this)) ;
        this.p_TableView.setDidDeselectCellAtIndexPathCallback(this.tableViewDidDeselectRowAtIndexPath.bind(this)) ;
        this.p_TableView.setCellAtIndexPathCallBack(this.tableCellAtIndex.bind(this)) ;
        this.p_TableView.setSectionViewForHeaderInSectionCallback(this.tableViewSectionViewForHeaderInSection.bind(this)) ;
        this.p_TableView.setSectionViewForFooterInSectionCallback(this.tableViewSectionViewForFooterInSection.bind(this)) ;
        this.p_TableView.setNumberOfRowsAtIndexPathCallback(this.numberOfRowsInSection.bind(this));
        this.p_TableView.setNumberOfSectionsCallback(this.numberOfSections.bind(this)) ;
        this.p_TableView.setCellHeightAtIndexPathCallback(this.tableViewHeightForRowAtIndexPath.bind(this));
        this.p_TableView.setHeightForHeaderInSectionCallback(this.tableViewHeightForHeaderInSection.bind(this));
        this.p_TableView.setHeightForFooterInSectionCallback(this.tableViewHeightForFooterInSection.bind(this)) ;

        this.p_TableView.setAllowsSelection(true);
        this.p_TableView.setAllowsMultipleSelection(false);
        this.p_TableView.setShowsScrollIndicators(false);
        this.p_TableView.setSelectRowAtIndexPath(2, 1);

        this.getView().addSubview(this.p_TableView);

    },
    tableViewDidSelectRowAtIndexPath: function(section ,row)
    {

    },
    tableViewDidDeselectRowAtIndexPath: function( section ,row)
    {

    },
    tableCellAtIndex: function( cellSize, section ,row)
    {
        var cell = this.p_TableView.dequeueReusableCellWithIdentifier("CrossApp");
        if (cell == null)
        {
            cell = ca.CATableViewCell.create("CrossApp");
            var image = ca.CAImageView.createWithLayout(ca.DLayoutFill);
            image.setImage(ca.CAImage.create("source_material/second_2.png"));
            cell.addSubview(image);

            var cellText = ca.CALabel.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(150, 10), ca.DVerticalLayout_T_B(10, 10)));
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
    ,tableViewSectionViewForHeaderInSection: function(viewSize ,section)
    {
        var head = this.sectionTitle[section];
        var view = ca.CAView.createWithColor(ca.CAColor4B.GRAY);

        var header = ca.CALabel.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(50, 0), ca.DVerticalLayoutFill));
        header.setText(head);
        header.setFontSize(30);
        header.setColor(ca.CAColor4B.WHITE);
        header.setTextAlignment(ca.CATextAlignment.Left);
        header.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
        view.addSubview(header);

        return view;
    }
    ,tableViewSectionViewForFooterInSection: function(viewSize ,section)
    {
        var view = ca.CAView.createWithColor(ca.CAColor4B.GRAY);
        return view;
    }
    ,numberOfRowsInSection: function(section)
    {
        return 2;
    }
    ,numberOfSections: function()
    {
        return this.sectionTitle.length;
    }
    ,tableViewHeightForRowAtIndexPath: function(section, row)
    {
        return 130;
    }
    ,tableViewHeightForHeaderInSection: function(section)
    {
        return 50;
    }
    ,tableViewHeightForFooterInSection: function(section)
    {
        return 1;
    }

});
