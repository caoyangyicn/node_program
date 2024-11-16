
#include "util.h"
#include "console.h"

using namespace v8;


// 设置对象的属性，属性为函数
void setMethod(Isolate *isolate, 
                Local<ObjectTemplate> 
                recv, const char *name, 
                FunctionCallback callback) {
    recv->Set(String::NewFromUtf8(isolate, name, 
        NewStringType::kNormal).ToLocalChecked(), 
        FunctionTemplate::New(isolate, callback));
}

void register_builtins(Isolate * isolate, Local<Object> global, Local<Context> context) {
  MOLEULES_LIST(MV);
}

 