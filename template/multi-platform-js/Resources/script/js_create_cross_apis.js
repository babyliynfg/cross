ca.CAAlertView.createWithText = function(tests){
    if((arguments.length > 0) && (arguments[arguments.length-1] == null))
        ca.log("parameters should not be ending with null in Javascript");
    
    var alertView = ca.CAAlertView.create();
    
    alertView.setTitle(arguments[0]);
    alertView.setAlertMessage(arguments[1]);
    
    var argc = arguments.length;
    for (var i = 2; i < argc; i++) {
        if (arguments[i])
            alertView.addButton(arguments[i]);
    }
    
    return alertView ;
}