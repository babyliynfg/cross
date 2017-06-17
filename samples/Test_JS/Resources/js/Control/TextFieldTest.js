/**
 * Created by crossApp on 16/8/3.
 */
var TextFieldTest = ca.CAViewController.extend({

    ctor: function () {
        this._super();
    },

    viewDidLoad: function() {

        var textField1 = ca.CATextField.createWithLayout(ca.DLayout.set(ca.DHorizontalLayout_L_R(100, 100), ca.DVerticalLayout_T_H(200, 100)));
        //PlaceHolder文本内容
        textField1.setPlaceHolderText("Input");
        //键盘类型
        textField1.setKeyboardType(ca.CATextField.KeyboardType.Default);
        //TextField的对齐方式
        textField1.setAlign(ca.CATextField.Align.Left);
        textField1.setDelegate(this);
        this.getView().addSubview(textField1);


    },

    textFieldShouldBeginEditing: function(sender){
        log("textFieldShouldBeginEditing-->");
        return true;
    },
    textFieldShouldEndEditing: function(sender){
        log("textFieldShouldEndEditing-->");
        return true;
    },
    textFieldShouldReturn: function(sender){
        log("textFieldShouldReturn-->");
    },
    keyBoardHeight: function(sender, height){
        log("keyBoardHeight-->");
    },
    textFieldShouldChangeCharacters: function(sender,location,lenght,changedText){
        log("textFieldShouldChangeCharacters-->");
        return true;
    }
});
