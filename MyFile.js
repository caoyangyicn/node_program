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
    console.say("This is My Function!");
}
MyFunc();
console.say("sum=" + sum);
let a = new A();
console.say(a.sum(1, 2));
console.say({TEXT: 'Hello World!'});
console.write([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
