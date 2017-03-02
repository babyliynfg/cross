var CheckboxTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
        this.getView().setColor(ca.color._getGray());

        var box = ca.CACheckbox.createWithLayout(DLayout(DHorizontalLayout_W_C(54, 0.5), DVerticalLayout_H_C(54, 0.25)));
        this.getView().addSubview(box);
        box.setTarget(function ( isSelect) {
          if (isSelect) {
            log("选中");
          }else {
            log("取消选中");
          }
        });
        var box1 = ca.CACheckbox.createWithLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(54, 0.55)));
        box1.setImageStateNormal(ca.CAImage.create("source_material/checkbox_normal.png"));
        box1.setImageStateSelected(ca.CAImage.create("source_material/checkbox_selected.png"));
        box1.setTitleStateNormal("未选中");
        box1.setTitleStateSelected("选中");
        this.getView().addSubview(box1);
        box1.setTarget(function ( isSelect) {
          if (isSelect) {
            log("选中");
          }else{
            log("取消选中");
          }
        });
    },
});
