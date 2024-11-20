#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include "example.h"

using namespace v8;
using namespace Example;

void register_builtins(Isolate* isolate, Local<Object> global) {
    
    Local<ObjectTemplate> Example = ObjectTemplate::New(isolate);                                                         // 创建 Example 对象模板
    
    Example->Set(
      String::NewFromUtf8(isolate, "print", NewStringType::kNormal).ToLocalChecked(),
      FunctionTemplate::New(isolate, Example::Print)
    );                                                                                                                    // 设置 Example 对象的方法
    Example->Set(
      String::NewFromUtf8(isolate, "writeFile", NewStringType::kNormal).ToLocalChecked(),
      FunctionTemplate::New(isolate, Example::WriteFile)                                                                  // 设置 Example 对象的方法
    );

    
    Local<Object> exampleInstance = Example->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();                  // 将 Example 对象挂到 global 对象上
    global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "example", NewStringType::kNormal).ToLocalChecked(), exampleInstance).FromJust();
}

int main(int argc, char* argv[]) {
  V8::InitializeICUDefaultLocation(argv[0]);
  V8::InitializeExternalStartupData(argv[0]);
  std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();                                                    // V8 的一些通用初始化逻辑
  V8::InitializePlatform(platform.get());
  V8::Initialize();
  Isolate::CreateParams create_params;                                                                                    // 创建 Isolate 时传入的参数
  create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
  Isolate* isolate = Isolate::New(create_params);                                                                         // 创建一个 Isolate，V8 的对象
  {
    Isolate::Scope isolate_scope(isolate);
    HandleScope handle_scope(isolate);                                                                                    // 创建一个 HandleScope，用于下面分配 Handle
    Local<ObjectTemplate> global = ObjectTemplate::New(isolate);                                                          // 创建一个对象模版，用于创建全局对象
    Local<Context> context = Context::New(isolate, nullptr, global);                                                      // 创建一个上下文
    Context::Scope context_scope(context);
    Local<Object> globalInstance = context->Global();                                                                     // 获取 JS 全局对象
    register_builtins(isolate, globalInstance);                                                                           // 注册 C++ 模块
    {
      if(argc < 2) {
        fprintf(stdout, "Usage: %s filename\n", argv[0]);
        return 1;
      }
      char* filename = argv[1];                                                                                           // 打开 JS 文件,将 JS 文件内容读取到内存
      int fd = open(filename, 0, O_RDONLY);
      struct stat info;
      fstat(fd, &info);
      char *ptr = (char *)malloc(info.st_size + 1);
      read(fd, (void *)ptr, info.st_size);
      ptr[info.st_size] = '\0';

      Local<String> source = String::NewFromUtf8(isolate, ptr, NewStringType::kNormal, info.st_size).ToLocalChecked();    // 要执行的 JS 代码
      Local<Script> script = Script::Compile(context, source).ToLocalChecked();                                           // 将 JS 代码编译成字节码
      free(ptr);                                                                                                          // 内存中的 JS 代码已经用不上了，释放掉这部分内存
      script->Run(context).ToLocalChecked();                                                                              // 执行 JS
    }
  }

  isolate->Dispose();
  v8::V8::Dispose();
  delete create_params.array_buffer_allocator;
  return 0;
}


