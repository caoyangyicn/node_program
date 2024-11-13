const {
    myFunc
} = Example.buildin;

// 创建对象的语法
class A{
    sum(a, b){
        return  a + b;
    }
}
let a = new A();
myFunc.say(a.sum(1, 2));

// 循环语句
let sum = 0;
for(let i = 0; i < 10; i++){
    sum += i;
}
myFunc.say("sum=" + sum);

// 函数
function func(){
    myFunc.say("This is My Function!");
}
func();

//对象输出
myFunc.say(JSON.stringify({TEXT: 'Hello World!'}));
