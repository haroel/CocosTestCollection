/**
 * Created by howe on 16/2/2.
 *
 * 选择节点
 */
var bt = bt || {};
bt.SelectorNode = bt.BaseNode.extend({

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
            if (status != bt.FAIRURE) {
                return status;
            }
        }
        return bt.FAIRURE;
    },
    exit: function (target,blackBoard) {

    }
});