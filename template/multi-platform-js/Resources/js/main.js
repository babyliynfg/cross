require('js/rootwindow.js');

ca.app.run();

var caapplication = ca.CAApplication.getApplication();
var window = new RootWindow()
window.init();
caapplication.runWindow(window);

ca.RootWindow = window;