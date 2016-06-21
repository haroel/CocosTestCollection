/**
 * Created by howe on 16/2/2.
 */
var bt = bt || {};
bt.SUCCESS = 0;
bt.FAIRURE = 1;
bt.RUNNING = 2;
bt.ERROR = -1;

bt._createUUID = function() {
    var s = [];
    var hexDigits = "0123456789abcdef";
    for (var i = 0; i < 36; i++) {
        s[i] = hexDigits.substr(Math.floor(Math.random() * 0x10), 1);
    }
    // bits 12-15 of the time_hi_and_version field to 0010
    s[14] = "4";

    // bits 6-7 of the clock_seq_hi_and_reserved to 01
    s[19] = hexDigits.substr((s[19] & 0x3) | 0x8, 1);

    s[8] = s[13] = s[18] = s[23] = "-";

    var uuid = s.join("");
    return uuid;
}

bt.Class = cc.Class.extend({
    uuid :0,
    ctor: function () {
        this.uuid = bt._createUUID();
    }
});


require("src/bt/BaseNode.js");
require("src/bt/BehaviorTree.js");
require("src/bt/SelectorNode.js");
require("src/bt/SequenceNode.js");
