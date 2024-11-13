#include "my_file.h"
#include <iostream>

using namespace std;

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

void Example::writeFile(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[0]);
    const char* cstr = ToCString(str);
    string filename = generateRandomFilename();
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << cstr;
        outFile.close();
    }
}

string Example::generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += charset[dist(rng)];
    }
    return random_string;
}

string Example::generateRandomFilename() {
    string random_string = generateRandomString(10); // Generate a random string of length 10
    return random_string + ".txt";
}

void Example::say(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[0]);
    const char* cstr = ToCString(str);
    printf("%s\n", cstr);
}

