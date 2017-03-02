/**
 * Created by zhanglei on 16/8/3.
 */
var TextFieldTest = ca.CAViewController.extend({
    ctor: function () {
        this._super();
        this.getView().setColor(ca.color._getGray());

        var textField1 = ca.CATextField.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(200, 100)));
        textField1.setTag(100);
        //PlaceHolder文本内容
        textField1.setPlaceHolderText("Input");
        //键盘类型
        textField1.setKeyboardType(0);
        //TextField的对齐方式
        textField1.setAlign(ca.CATextField.Align.Left);
        textField1.setDelegate(this);
        this.getView().addSubview(textField1);

        var textField2 = ca.CATextField.createWithLayout(DLayout(DHorizontalLayout_L_R(100, 100), DVerticalLayout_T_H(450, 100)));
        textField2.setTag(101);
        textField2.setPlaceHolderText("Input");
        textField2.setKeyboardType(0);
        textField2.setMarginImageLeft(ca.size(60,60),"source_material/search.png");
        textField2.setClearButtonMode(ca.CATextField.ClearButtonMode.WhileEditing);
        textField2.setAlign(ca.CATextField.Align.Left);
        textField2.setSecureTextEntry(true);
        textField2.setDelegate(this);
        this.getView().addSubview(textField2);
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
