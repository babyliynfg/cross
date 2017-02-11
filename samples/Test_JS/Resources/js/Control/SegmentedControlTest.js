/**
 * Created by zhanglei on 16/8/3.
 */
var SegmentedControlTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
        this.initSegmentedControl();
    },
    initSegmentedControl:function(){

        this.getView().setColor(ca.color._getGray());

        var segment1 = ca.CASegmentedControl.createWithLayout(DLayout(DHorizontalLayout_W_C(300, 0.5), DVerticalLayout_H_C(54, 0.25)), 3);

        for (var i = 0; i < 3; i++)
        {
            var  temstr = "Page" + (i + 1);
            segment1.setTitleForSegmentAtIndex(temstr, i);
        }
        segment1.setTitleColor(ca.BLACK);
        segment1.setTitleSelectedColor(ca.WHITE);
        segment1.addTarget(this, this.segmentCallback);
        segment1.setSelectedAtIndex(0);
        this.getView().addSubview(segment1);

        var segment2 = ca.CASegmentedControl.createWithLayout(DLayout(DHorizontalLayout_W_C(300, 0.5), DVerticalLayout_H_C(54, 0.55)), 3);
        //char temstr2[20];
        for (var i = 0; i < 3; i++)
        {
            var  temstr2 = "Page" + (i + 1);
            //sprintf(temstr2, "Page%d", i + 1);
            segment2.setTitleForSegmentAtIndex(temstr2, i);
        }
        segment2.setTitleColor(ca.BLACK);
        segment2.setTitleSelectedColor(ca.WHITE);

        segment2.addTarget(this, this.segmentCallback);
        segment2.setBackgroundImage(ca.CAImage.create("image/seg1.png"));
        segment2.setSegmentItemBackgroundImage(ca.CAImage.create("image/seg2.png"));
        segment2.setTintColor(ca.color(44, 178, 93, 255));
        segment2.setSelectedAtIndex(0);
        this.getView().addSubview(segment2);
    },
    segmentCallback: function ( btn, index) {

        log("segmentCallback-->");
    }
});