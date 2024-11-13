
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

void SetMethod(Local<v8::Context> context,
               Local<v8::Object> that,
               const char* name,
               v8::FunctionCallback callback) {
  Isolate* isolate = context->GetIsolate();
  Local<v8::Function> function =
      NewFunctionTemplate(isolate,
                          callback,
                          Local<v8::Signature>(),
                          v8::ConstructorBehavior::kThrow,
                          v8::SideEffectType::kHasSideEffect)
          ->GetFunction(context)
          .ToLocalChecked();
  // kInternalized strings are created in the old space.
  const v8::NewStringType type = v8::NewStringType::kInternalized;
  Local<v8::String> name_string =
      v8::String::NewFromUtf8(isolate, name, type).ToLocalChecked();
  that->Set(context, name_string, function).Check();
  function->SetName(name_string);  // NODE_SET_METHOD() compatibility.
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

Local<String> newStringToLcal(Isolate * isolate, const char * str, NewStringType type) {
    return String::NewFromUtf8(isolate, str, type, strlen(str)).ToLocalChecked();
}

void Compile(const FunctionCallbackInfo<Value> &args) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = args.GetIsolate()->GetCurrentContext();
    String::Utf8Value filename(isolate, args[0].As<String>());
    int fd = open(*filename, 0 , O_RDONLY);
    std::string content;
    char buffer[4096];
    while (1)
    {
      memset(buffer, 0, 4096);
      int ret = read(fd, buffer, 4096);
      if (ret == -1) {
        return args.GetReturnValue().Set(newStringToLcal(isolate, "read file error"));
      }
      if (ret == 0) {
        break;
      }
      content.append(buffer, ret);
    }
    close(fd);
    ScriptCompiler::Source script_source(newStringToLcal(isolate, content.c_str()));
    Local<String> params[] = {
      newStringToLcal(isolate, "require"),
      newStringToLcal(isolate, "exports"),
      newStringToLcal(isolate, "module"),
    };
    MaybeLocal<Function> fun =
    ScriptCompiler::CompileFunction(context, &script_source, 3, params, 0, nullptr);
    if (fun.IsEmpty()) {
      args.GetReturnValue().Set(Undefined(isolate));
    } else {
      args.GetReturnValue().Set(fun.ToLocalChecked());
    }
}

void Init(Isolate* isolate, Local<Object> target) {
  Local<ObjectTemplate> Example = ObjectTemplate::New(isolate);
  setMethod(isolate, Example, "say", Example::say);
  setMethod(isolate, Example, "write", Example::writeFile);
  setObjectValue(isolate, target, "myFunc", Example->NewInstance(isolate->GetCurrentContext()).ToLocalChecked());

}

void register_builtins(Isolate * isolate, Local<Object> Example) {
    Local<Object> target = Object::New(isolate);
    Init(isolate, target);
    setObjectValue(isolate, Example, "buildin", target);
}