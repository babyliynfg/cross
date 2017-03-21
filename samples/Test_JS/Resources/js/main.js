require('js/rootwindow.js');

ca.app.run();

var caapplication = ca.CAApplication.getApplication();
var rootWindow = new RootWindow();
rootWindow.init();
caapplication.runWindow(rootWindow);

ca.RootWindow = rootWindow;