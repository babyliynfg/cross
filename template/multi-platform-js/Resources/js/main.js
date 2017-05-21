require('js/rootwindow.js');

ca.app.run();

var application = ca.CAApplication.getApplication();
var window = new RootWindow();
window.init();
application.runWindow(window);
window.release();
ca.RootWindow = window;