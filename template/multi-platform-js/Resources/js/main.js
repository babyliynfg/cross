require('js/rootwindow.js');

var window = new RootWindow();
window.init();
ca.application.runWindow(window);
window.release();
ca.rootWindow = window;
