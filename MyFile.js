const {
    console
} = MyFile.buildin;

class A{
    sum(a, b){
        return  a + b;
    }
}
let sum = 0;
for(let i = 0; i < 10; i++){
    sum += i;
}
function MyFunc(){
    console.log("This is My Function!");
}
MyFunc();
console.log("sum=" + sum);
let a = new A();
console.log(a.sum(1, 2));
console.log({TEXT: 'Hello World!'});
console.write([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
