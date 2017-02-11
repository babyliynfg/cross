var FirstViewController = ca.CAViewController.extend({
    myView:null,
    ctor: function () {
        this._super();

        this.getView().setColor(ca.color._getGray());
        var img = ca.CAImageView.createWithImage(ca.CAImage.create("r/HelloWorld.png"));
        img.setLayout(DLayoutFill);
        img.setImageViewScaleType(1);
        this.getView().addSubview(img);

        var font = new CAFont();
        font.color = ca.WHITE;
        font.fontSize = 72;

        var labelLayout = DLayout(DHorizontalLayout_L_R(20, 20),DVerticalLayout_T_H(200, 100));
        var lab = ca.CALabel.createWithLayout(labelLayout);
        lab.setTextAlignment(ca.CATextAlignment.CATextAlignmentCenter);
        lab.setVerticalTextAlignmet(ca.CAVerticalTextAlignment.CAVerticalTextAlignmentCenter);
        lab.setText("Hello JavaScript");
        lab.setFont(font);
        this.getView().addSubview(lab);
    },
});
