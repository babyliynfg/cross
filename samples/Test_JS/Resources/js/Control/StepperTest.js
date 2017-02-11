/**
 * Created by zhanglei on 16/8/3.
 */
var StepperTest = ca.CAViewController.extend({
    step_value : null,
    ctor: function () {
        this._super();
        this.initStepper();
    },
    initStepper:function(){
        this.getView().setColor(ca.color._getGray());

        this.step_value = ca.CALabel.createWithLayout(DLayout(DHorizontalLayout_W_C(250, 0.5), DVerticalLayout_H_C(100, 0.25)));
        this.step_value.setText("step_value:0");
        this.step_value.setFontSize(28);
        this.step_value.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
        this.step_value.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
        this.getView().addSubview(this.step_value);


        var step = ca.CAStepper.createWithLayout(DLayout(DHorizontalLayout_W_C(360, 0.5), DVerticalLayout_H_C(60, 0.5)), ca.CAStepperOrientation.Horizontal);
        //step.setWraps(true);//是否循环,默认循环
        step.setMinValue(0);
        step.setMaxValue(50);
        step.setStepValue(1);
        //step.setAutoRepeat(false);
        this.getView().addSubview(step);
        step.addTarget(this, this.stepperCallBack);

    },
    stepperCallBack: function (btn, point) {
        log("stepperCallBack-->");
        var str = "step_value:" + btn.getValue();
        this.step_value.setText(str);
    }
});