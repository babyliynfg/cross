/**
 * Created by zhanglei on 16/8/3.
 */
var StepperTest = ca.CAViewController.extend({
    StepperNum : 1,
    step_value : null,
    maxNum:1,
    ctor: function (num) {
        this._super();
        if(num != null){
            this.StepperNum = num;
        }
        this.initStepper();
    },
    viewDidLoad: function() {
    },
    initStepper:function(){
        this.getView().setColor(ca.color._getGray());

        this.step_value = ca.CALabel.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(250, 0.5), ca.DVerticalLayout_H_C(100, 0.25)));
        this.step_value.setText("step_value:0");
        this.step_value.setFontSize(28);
        this.step_value.setTextAlignment(ca.CATextAlignment.Center);
        this.step_value.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
        this.getView().addSubview(this.step_value);

        if (this.StepperNum == 0)
        {
            var step = ca.CAStepper.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(360, 0.5), ca.DVerticalLayout_H_C(60, 0.5)), ca.CAStepper.Orientation.Horizontal);
            //step.setWraps(true);//是否循环,默认循环
            step.setMinValue(0);
            step.setMaxValue(50);
            step.setStepValue(1);
            //step.setAutoRepeat(false);
            this.getView().addSubview(step);
            var valueLabel = this.step_value;
            step.setTarget(function (value) {
                log("stepperCallBack-->");
                var str = "step_value:" + value;
                valueLabel.setText(str);
            });
        }
        else
        {
            var step = ca.CAStepper.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_W_C(60, 0.5), ca.DVerticalLayout_H_C(360, 0.5)), ca.CAStepper.Orientation.Vertical);
            //step.setWraps(true);//是否循环,默认循环
            step.setMinValue(0);
            step.setMaxValue(50);
            step.setStepValue(1);
            //step.setAutoRepeat(false);
            this.getView().addSubview(step);
            var valueLabel = this.step_value;
            step.setTarget(function (value) {
                log("stepperCallBack-->");
                var str = "step_value:" + value;
                valueLabel.setText(str);
            });
        }
    },
});
