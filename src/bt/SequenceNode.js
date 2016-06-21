/**
 * Created by howe on 16/2/2.
 *
 * 顺序节点
 */
var bt = bt || {};
bt.SequenceNode = bt.BaseNode.extend({

    children:null,
    ctor: function (nodes) {
        this._super();
        this.children = nodes;
    },
    enter: function (target,blackBoard) {

    },
    tick: function (target,blackBoard) {
        for (var i in this.children)
        {
            var _node = this.children[i];
            var status = _node._excute(target,blackBoard);
            if (status != bt.SUCCESS) {
                return status;
            }
        }
        return bt.SUCCESS;
    },
    exit: function (target,blackBoard) {

    }
});