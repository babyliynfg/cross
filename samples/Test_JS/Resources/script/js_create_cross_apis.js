ca.CAAlertView.createWithText = function(tests){
    if((arguments.length > 0) && (arguments[arguments.length-1] == null))
        ca.log("parameters should not be ending with null in Javascript");
    
    var argc = arguments.length;
    var btnStrArray = new Array();
    for (var i = 2; i < argc; i++) {
        if (arguments[i])
        btnStrArray.push(arguments[i]);
    }
    
    
    var alertView = ca.CAAlertView.create(arguments[0],arguments[1],btnStrArray);
    
    return alertView ;
}