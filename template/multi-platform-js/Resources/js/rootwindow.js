require('js/firstviewcontroller.js');

var RootWindow = ca.CAWindow.extend(
    {
        m_pRootNavigationController:null,
        ctor: function () {
            this._super();

            var firstViewController = new FirstViewController();
            firstViewController.init();
            this.setRootViewController(firstViewController);

        }
    }
);
