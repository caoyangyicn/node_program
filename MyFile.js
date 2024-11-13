const {
    myFunc
} = Example.buildin;

class A{
    sum(a, b){
        return  a + b;
    }
}
let sum = 0;
for(let i = 0; i < 10; i++){
    sum += i;
}
function func(){
    myFunc.say("This is My Function!");
}
func();
myFunc.say("sum=" + sum);
let a = new A();
myFunc.say(a.sum(1, 2));
myFunc.say(JSON.stringify({TEXT: 'Hello World!'}));
myFunc.write([1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
