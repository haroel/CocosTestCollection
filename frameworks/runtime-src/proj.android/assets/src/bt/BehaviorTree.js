/**
 * Created by howe on 16/2/2.
 */
var bt = bt || {};
bt.BehaviorTree = bt.Class.extend({
    
    root:null,
    ctor: function () {
        this._super();
        //this.root = null;

    },
    
    update: function (target,blackBoard) {
        var status;
        if (this.root)
        {
            //gui.log(this.root);

            status = this.root._excute(target,blackBoard);
        }

        return status;
    }
    
});