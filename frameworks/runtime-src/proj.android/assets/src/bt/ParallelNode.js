/**
 * Created by howe on 16/2/3.
 */
var bt = bt || {};
bt.ParallelNode = bt.BaseNode.extend({

    children:null,
    ctor: function (nodes) {
        this._super();

        this.children = nodes;
    },
    enter: function (target,blackBoard) {

    },
    tick: function (target,blackBoard) {

        var __status = bt.FAIRURE;
        for (var i in this.children)
        {
            var _node = this.children[i];
            var status = _node._excute(target,blackBoard);
            if (status == bt.SUCCESS) {
                return status;
            }
            if (status != bt.FAIRURE)
            {
                __status = status;
            }
        }
        return __status;
    },
    exit: function (target,blackBoard) {

    }

});