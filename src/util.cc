#include "util.h"

using namespace v8;
Local<v8::FunctionTemplate> NewFunctionTemplate(
            v8::Isolate* isolate,
            v8::FunctionCallback callback,
            Local<v8::Signature> signature,
            v8::ConstructorBehavior behavior,
            v8::SideEffectType side_effect_type,
            const v8::CFunction* c_function) {
        return v8::FunctionTemplate::New(isolate,
                                        callback,
                                        Local<v8::Value>(),
                                        signature,
                                        0,
                                        behavior,
                                        side_effect_type,
                                        c_function);
}

// 设置对象的属性，属性为函数
void setMethod(Isolate *isolate, 
                Local<ObjectTemplate> 
                recv, const char *name, 
                FunctionCallback callback) {
    recv->Set(String::NewFromUtf8(isolate, name, 
        NewStringType::kNormal).ToLocalChecked(), 
        FunctionTemplate::New(isolate, callback));
}

// 设置对象的属性，属性为非函数
void setObjectValue(Isolate *isolate, 
                Local<Object> 
                recv, const char *name, 
                Local<Value> value) {
    recv->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, name, 
        NewStringType::kNormal).ToLocalChecked(), 
        value);
}

void register_builtins(Isolate* isolate, Local<Object> global) {
    // 创建 Example 对象模板
    Local<ObjectTemplate> Example = ObjectTemplate::New(isolate);
    setMethod(isolate, Example, "print", Example::print);
    setMethod(isolate, Example, "prite", Example::WriteFile);

    // 将 Example 对象挂到 global 对象上
    Local<Object> exampleInstance = Example->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
    global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "example", NewStringType::kNormal).ToLocalChecked(), exampleInstance).FromJust();
}
