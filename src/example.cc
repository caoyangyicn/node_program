#include "example.h"

using namespace v8;

void Example::WriteFile(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[1]);
    v8::String::Utf8Value path(isolate, args[0]);
    FILE* outFile = fopen(*path, "w");
    if (outFile != nullptr) {
        fputs(*str, outFile);
        fclose(outFile);
    } else {
        fprintf(stderr, "Unable to open file: %s\n", *path);
    }
}

void Example::Print(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(isolate, args[0]);
    printf("%s\n", *str);
}
