var res = {
    HelloWorld_png : "res/HelloWorld.png",
};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}

var gui = gui || {};

gui.log = function ()
{
    //    if ( syst.__DEBUG() ) {
    if ( arguments.length == 1 ) {
        cc.log(gui._log(arguments[0]));
    } else if ( arguments.length == 2 ) {
        var _title = arguments[0];
        var _msg = _title + "  " + gui._log(arguments[1]);
        cc.log(_msg);
    }
    //    }
};
gui._log = function (msg)
{
    var text;
    switch (typeof msg) {
        case 'string':
            text = msg;
            break;
        case 'object':
        {
            seen = [];
            text = JSON.stringify(msg, function(key, val) {
                if (typeof val == "object") {
                    if (seen.indexOf(val) >= 0) return;
                    seen.push(val)
                }
                return val;
            },2);
            break;
        }
        case 'number':
            text = msg;
            break;
        case 'boolean':
            text = msg ? "true" : "false";
            break;
        default :
            text = "Unknown msg type: " + (typeof msg) + ", msg:" + msg;
            break;
    }
    return text;
};