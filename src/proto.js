/**
 * Created by howe on 16/1/18.
 */

cc.log("测试js 原型链 BEGIN");
function Person(_name)
{
    this.name = _name;
}
Person.prototype.name = "howe";

var p1 = new Person("hehao");
console.log(p1.name + "----" + Person.prototype.name);

var p2 = new Person("zhangli");
console.log(p2.name + "----" + p2.__proto__.name);

// 声明 Animal 对象构造器
function Animal() {
}
// 将 Animal 的 prototype 属性指向一个对象，
// 亦可直接理解为指定 Animal 对象的原型
Animal.prototype = {
    name: "animal",
    weight: 0,
    eat: function() {
        console.log( "Animal is eating!" );
    }
}
// 声明 Mammal 对象构造器
function Mammal() {
    this.name = "mammal";
}
// 指定 Mammal 对象的原型为一个 Animal 对象。
// 实际上此处便是在创建 Mammal 对象和 Animal 对象之间的原型链
Mammal.prototype = new Animal();

// 声明 Horse 对象构造器
function Horse( height, weight ) {
    this.name = "horse";
    this.height = height;
    this.weight = weight;
}
// 将 Horse 对象的原型指定为一个 Mamal 对象，继续构建 Horse 与 Mammal 之间的原型链
Horse.prototype = new Mammal();

// 重新指定 eat 方法 , 此方法将覆盖从 Animal 原型继承过来的 eat 方法
Horse.prototype.eat = function() {
    console.log( "Horse is eating grass!" );
}
// 验证并理解原型链
var horse = new Horse( 100, 300 );
if ( horse.__proto__ === Horse.prototype ) // true
{
    console.log("horse.__proto__ === Horse.prototype")
}
if ( Horse.prototype.__proto__ === Mammal.prototype ) // true
{
    console.log("Horse.prototype.__proto__ === Mammal.prototype")
}
if ( Mammal.prototype.__proto__ === Animal.prototype )// true
{
    console.log("Mammal.prototype.__proto__ === Animal.prototype")
}

cc.log("测试js 原型链 END");
