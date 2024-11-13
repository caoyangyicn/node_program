#include "my_file.h"
#include <iostream>

using namespace std;

void Example::writeFile(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[0]);
    v8::String::Utf8Value path(isolate, args[1]);
    ofstream outFile(*path);
    if (outFile.is_open()) {
        outFile << *str;
        outFile.close();
    }
}

void Example::say(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[0]);
    printf("%s\n", *str);
}