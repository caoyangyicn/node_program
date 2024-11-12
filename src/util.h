#include <fcntl.h>
#include <unistd.h>
#include "v8.h"
#include "include/libplatform/libplatform.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-isolate.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"
#include "my_file.h"

using namespace v8;



v8::Local<v8::FunctionTemplate> NewFunctionTemplate(
            v8::Isolate* isolate,
            v8::FunctionCallback callback = nullptr,
            v8::Local<v8::Signature> signature = v8::Local<v8::Signature>(),
            v8::ConstructorBehavior behavior = v8::ConstructorBehavior::kAllow,
            v8::SideEffectType side_effect = v8::SideEffectType::kHasSideEffect,
            const v8::CFunction* c_function = nullptr);

void SetMethod(Local<v8::Context> context,
               Local<v8::Object> that,
               const char* name,
               v8::FunctionCallback callback);

void setObjectValue(Isolate *isolate, 
                Local<Object> 
                recv, const char *name, 
                Local<Value> value);

Local<String> newStringToLcal(Isolate * isolate, const char * str, NewStringType type = NewStringType::kNormal);

void register_builtins(Isolate * isolate, Local<Object> MyFile);