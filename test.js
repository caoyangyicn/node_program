const { print, writeFile } = example;

// 简单测试我们实现的 print 函数
print("Hello World!");

// 简单测试我们实现的 writeFile 函数
writeFile("test.txt", "Hello World!");

// 测试 class 关键字
class A{
    sum(a, b){
        return  a + b;
    }
}
let a = new A();
print("1 + 2 = " + a.sum(1, 2));

// 测试 for 关键字
let sum = 0;
for(let i = 0; i < 10; i++){
    sum += i;
}
print("sum = " + sum);

// 测试 function 关键字
function func(){
    print("This is My Function!");
}
func();

// 测试 json 序列化
print(JSON.stringify({text: 'Hello World!'}));
