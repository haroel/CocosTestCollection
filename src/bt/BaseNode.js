/**
 * Created by howe on 16/2/2.
 */
var bt = bt || {};
bt.BaseNode = bt.Class.extend({

    name:"",
    parames:null,

    ctor: function () {
        this._super();
        this.parames = {};
    },
    _enter: function (target,blackBoard) {

        this.enter();
    },
    _excute: function (target,blackBoard) {
        
        this._enter(target,blackBoard);

        var status = this.tick(target,blackBoard);
        this._exit(target,blackBoard);
        return status;
    },
    _exit: function (target,blackBoard) {

        this.exit();
    },
    
    
    
    enter: function (target,blackBoard) {
        
    },
    tick: function (target,blackBoard) {
        
    },
    exit: function (target,blackBoard) {
        
    }

});