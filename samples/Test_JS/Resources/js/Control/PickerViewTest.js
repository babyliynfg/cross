/**
 * Created by zhanglei on 16/8/3.
 */
var adressTag = new Array(
    "北京市",
    "天津市",
    "上海市",
    "重庆市",
    "河北省",
    "山西省",
    "辽宁省",
    "吉林省",
    "黑龙江省",
    "江苏省",
    "浙江省",
    "安徽省",
    "福建省",
    "江西省",
    "山东省",
    "河南省",
    "湖北省",
    "湖南省",
    "广东省",
    "海南省",
    "四川省",
    "贵州省",
    "云南省",
    "陕西省",
    "甘肃省",
    "青海省",
    "台湾省",
    "广西壮族自治区",
    "内蒙古自治区",
    "西藏自治区",
    "宁夏回族自治区",
    "新疆维吾尔自治区",
    "香港特别行政区",
    "澳门特别行政区"
);


var PickerViewTest = ca.CAViewController.extend({
    city_value: null,
    p_pickerView:null,
    ctor: function () {
        this._super();

        //this.getView().setColor(ca.color._getGray());

        this.p_pickerView = ca.CAPickerView.createWithLayout(DLayout(DHorizontalLayout_L_R(10, 10), DVerticalLayout_T_H(200, 400)));
        this.p_pickerView.setPickerViewDelegate(this);
        this.p_pickerView.setPickerViewDataSource(this);
        this.p_pickerView.setFontSizeNormal(40);
        this.p_pickerView.setFontSizeSelected(40);
        this.p_pickerView.setFontColorNormal(ca.BLACK);
        this.p_pickerView.setFontColorSelected(ca.BLACK);
        this.p_pickerView.reloadAllComponents();

        this.city_value = ca.CALabel.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_T_H(100, 40)));
        this.city_value.setText("天津");
        this.city_value.setColor(ca.BLACK);
        this.city_value.setFontSize(28);
        this.city_value.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
        this.city_value.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);

        var view1 = ca.CAView.createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayoutFill));
        view1.addSubview(this.p_pickerView);
        view1.addSubview(this.city_value);
        view1.setColor(ca.WHITE);
        this.getView().addSubview(view1);
    },
    didSelectRow: function (pickerView, row, component) {
        this.city_value.setText(adressTag[row]);
    },
    numberOfComponentsInPickerView: function (pickerView) {
        return 1;
    },

    numberOfRowsInComponent: function (pickerView, component) {
        //log("numberOfRowsInComponent");
        return 34;
    },
    widthForComponent: function (pickerView, component) {
        return 400;
    },

    rowHeightForComponent: function (pickerView, component) {
        return 80;
    },
    titleForRow: function (pickerView, row, component) {
        var str = adressTag[row];
        return str;
    }
});
