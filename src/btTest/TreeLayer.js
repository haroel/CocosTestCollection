/**
 * Created by howe on 16/2/2.
 */

function setNodeTarget(node,target)
{
    var childList = node.getChildren();
    for (var i in childList)
    {
        var _cNode = childList[i];
        if (_cNode.getCallbackName() != "" && _cNode.getCallbackType() != "")
        {
            var callBackName = _cNode.getCallbackName();
            if (target[callBackName])
            {
                var callType = _cNode.getCallbackType();
                switch (callType)
                {
                    case "Click":
                    {
                        _cNode.addClickEventListener(target[callBackName],target);
                        break;
                    }
                    case "Touch":
                    {
                        _cNode.addTouchEventListener(target[callBackName],target);
                        break;
                    }
                    case "Event":
                    {
                        _cNode.addEventListener(target[callBackName],target);
                        break;
                    }
                }
            }
        }
        if (_cNode.getName() != "")
        {
            target[_cNode.getName()] = _cNode;
            setNodeTarget(_cNode,target);
        }
    }
}

var TreeLayer = cc.Layer.extend({

    target:null,
    blackBorad:null,
    ctor: function () {
        this._super();
    },
    onEnter:function () {
        this._super();

        var json = ccs.load("res/bt/Layer.json");

        this._layer = json.node;
        this.addChild(this._layer);

        setNodeTarget(this._layer,this);


        this.target = new ccui.Text("AI");
        this.target.setPosition(cc.p(300,222));
        this._layer.addChild(this.target,1000);

        this.blackBorad = this;

        this.btTree = new bt.BehaviorTree();
        //this.btTree.root = new bt.SelectorNode();

        this.blackBorad["is_day"] = this["CheckBox_1_3"].isSelected();
        this.blackBorad["is_gf_get_flower"] = this["CheckBox_1_2"].isSelected();
        this.blackBorad["has_flower"] = this["CheckBox_1_0"].isSelected();
        this.blackBorad["has_money"] = this["CheckBox_1"].isSelected();
        this.blackBorad["is_gf_there"] = this["CheckBox_1_1"].isSelected();
        gui.log("this",this.blackBorad);

        var if1 = new tl.IFNot("is_day"); // 是否是情人节
        var if2 = new tl.IFNot("is_gf_get_flower"); // 女友没花
        var if3 = new tl.IFNot("has_flower"); //   自己没花
        var if4 = new tl.IFNot("has_money"); // 没带钱
        var if5 = new tl.IF("is_gf_there"); // 女友还在

        var go1 = new tl.GO("Panel_play"); // 去操场
        var go2 = new tl.GO("Panel_home"); // 回家
        var go3 = new tl.GO("Panel_shop"); // 去花点
        var go4 = new tl.GO("Panel_gf"); // 去女友那

        var doPlay = new bt.SequenceNode([if1,go1,new tl.Do("打球")]);

        var doGetMoney = new bt.SequenceNode([if2,if3,if4,go2,new tl.Do("拿钱","has_money","CheckBox_1")]);
        var doShopBuy = new bt.SequenceNode([ if2,if3,go3,new tl.Do("买花","has_flower","CheckBox_1_0")]);

        var doBuy = new bt.SelectorNode([doGetMoney,doShopBuy]);

        var doGF = new bt.SequenceNode( [go4,if5, if2,new tl.Do("送花","is_gf_get_flower","CheckBox_1_2")]);

        var doMeet = new bt.SelectorNode( [ doBuy,doGF ]);

        this.btTree.root = new bt.SelectorNode( [doPlay, doMeet ] );

        this.schedule(this.onTick1, 0.1);
        //gui.log("黑板",this.blackBorad);
    },
    onTick1: function () {
        this.btTree.update(this["Text_11"],this.blackBorad);
    },
    onChangeEvent: function (psender, event) {
        //cc.log("onChangeEvent " + psender.getName());
        cc.log("事件发生后，修改黑板的数据，行为树自动完成更新");
        this.blackBorad["is_day"] = this["CheckBox_1_3"].isSelected();
        this.blackBorad["is_gf_get_flower"] = this["CheckBox_1_2"].isSelected();
        this.blackBorad["has_flower"] = this["CheckBox_1_0"].isSelected();
        this.blackBorad["has_money"] = this["CheckBox_1"].isSelected();
        this.blackBorad["is_gf_there"] = this["CheckBox_1_1"].isSelected();
    }

});