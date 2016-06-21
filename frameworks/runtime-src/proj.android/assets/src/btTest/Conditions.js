/**
 * Created by howe on 16/2/2.
 */
var tl = tl || {};
tl.IF = bt.BaseNode.extend({

    ctor: function (checkBoxName) {
        this._super();
        this.parames.checkBoxName = checkBoxName;
    },

    enter: function (target,blackBoard) {

    },
    tick: function (target,blackBoard) {
        var checkBox = blackBoard[this.parames.checkBoxName];
        if (checkBox)
        {
            return bt.SUCCESS;
        }
        return bt.FAIRURE;
    },
    exit: function (target,blackBoard) {

    }
});

tl.IFNot = bt.BaseNode.extend({

    ctor: function (checkBoxName) {
        this._super();
        this.parames.checkBoxName = checkBoxName;
    },

    enter: function (target,blackBoard) {

    },
    tick: function (target,blackBoard) {
        var checkBox = blackBoard[this.parames.checkBoxName];
        if (!checkBox)
        {
            return bt.SUCCESS;
        }
        return bt.FAIRURE;
    },
    exit: function (target,blackBoard) {

    }
});

tl.GO = bt.BaseNode.extend({

    ctor: function (panelName) {
        this._super();
        this.parames.panelName = panelName;
        this.SPEED = 10;
    },
    tick: function (target,blackBoard) {
        var panel = blackBoard[this.parames.panelName];
        if (panel)
        {
            var pos = target.getPosition();
            var panelPos = panel.getPosition();

            var _dis = cc.pDistance(pos,panelPos);
            if ( _dis > this.SPEED)
            {
                //cc.log("执行" + this.parames.panelName)

                var angle = cc.pToAngle(cc.pSub(panelPos,pos));
               // cc.log(this.parames.panelName + "  dis " + _dis + " angle " + angle);

                var DX = Math.cos(angle) * this.SPEED;
                var DY = Math.sin(angle) * this.SPEED;
                target.setPosition(cc.p(pos.x +DX,pos.y+DY));
                return bt.RUNNING;
            }else
            {
                target.setPosition(panelPos);
            }
        }
        return bt.SUCCESS;
    }
});


tl.Do = bt.BaseNode.extend({
    ctor: function (log,key,checkName) {
        this._super();
        this.name = log;
        this.parames.key = key;
        this.parames.checkName = checkName;
    },
    tick: function (target,blackBoard) {
        cc.log("执行节点" + this.name);
        if (this.parames.key)
        {
            blackBoard[this.parames.checkName].setSelected(true);
            blackBoard[ this.parames.key] = true;
        }
        return bt.SUCCESS;
    }
});