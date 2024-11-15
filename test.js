const { print, writeFile } = example;

print("Hello World!");
writeFile("test.txt", JSON.stringify({TEXT: 'Hello World!'}));
// 创建对象
class A{
    sum(a, b){
        return  a + b;
    }
}
let a = new A();
print(a.sum(1, 2));

// 循环语句
let sum = 0;
for(let i = 0; i < 10; i++){
    sum += i;
}
print("sum=" + sum);

// 函数
function func(){
    print("This is My Function!");
}
func();

//对象输出
print(JSON.stringify({TEXT: 'Hello World!'}));