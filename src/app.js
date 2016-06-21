
var ClassA = cc.Class.extend({

    arr:[1,2],
    property:{name:"howe"},
    ctor: function () {

    }

})

var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();
        //var i1 = new ClassA()
        //i1.arr = [4,5]
        //i1.property.name = "bill"
        //
        //var i2 = new ClassA()
        //i2.arr = [6,7];
        //i2.property.name = "jobs"
        //
        //cc.log(i1.arr.toString());
        //cc.log(i2.arr.toString());
        //
        //cc.log(i1.property.name);
        //cc.log(i2.property.name);
        //
        //gui.log("ClassA: ",ClassA.prototype)
        //gui.log("ClassA: ",i1.__proto__)

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label

        var layer = new TreeLayer();
        this.addChild(layer);

        return true;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

