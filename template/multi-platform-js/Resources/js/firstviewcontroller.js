var FirstViewController = ca.CAViewController.extend({
    ctor: function () {
        this._super();
    },
    viewDidLoad: function () {

        this.getView().setColor(ca.CAColor4B.GRAY);
        var img = ca.CAImageView.createWithImage(ca.CAImage.create("r/HelloWorld.png"));
        img.setLayout(DLayoutFill);
        img.setScaleType(1);
        this.getView().addSubview(img);

        var font = new CAFont();
        font.color = ca.CAColor4B.WHITE;
        font.fontSize = 72;

        var labelLayout = DLayout(DHorizontalLayout_L_R(20, 20),DVerticalLayout_T_H(200, 100));
        var lab = ca.CALabel.createWithLayout(labelLayout);
        lab.setTextAlignment(ca.CATextAlignment.Center);
        lab.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.Center);
        lab.setText("CrossApp");
        lab.setFont(font);
        this.getView().addSubview(lab);
    },
    viewDidUnload: function () {
        ca.log("viewDidUnload");
    }
});
