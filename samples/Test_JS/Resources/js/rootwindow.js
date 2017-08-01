

var RootWindow = ca.CAWindow.extend(
    {
        m_pRootNavigationController:null,
        ctor: function () {
            this._super();

            var viewController = new FirstViewController();

            var navItem = ca.CANavigationBarItem.create("控件展示");
            var item = ca.CABarButtonItem.create("", ca.CAImage.create("image/ic_category_list.png"), null);
            item.setCallbackFunction(function (){});
            navItem.addLeftButtonItem(item);
            viewController.setNavigationBarItem(navItem);

            this.m_pRootNavigationController = new ca.CANavigationController();
            this.m_pRootNavigationController.initWithRootViewController(viewController);
            this.setRootViewController(this.m_pRootNavigationController);
        },
        getRootNavigationController:function(){
            return this.m_pRootNavigationController;
        }
    }
);
