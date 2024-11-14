example.say("Hello World!");
// 创建对象
class A{
    sum(a, b){
        return  a + b;
    }
}
let a = new A();
example.say(a.sum(1, 2));

// 循环语句
let sum = 0;
for(let i = 0; i < 10; i++){
    sum += i;
    example.say("i= " + i);
}
example.say("sum=" + sum);

// 函数
function func(){
    example.say("This is My Function!");
}
func();

//对象输出
example.say(JSON.stringify({TEXT: 'Hello World!'}));
example.write("test.txt", JSON.stringify({TEXT: 'Hello World!'}));