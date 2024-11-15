// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include "my_file.h"
#include "util.h"
#include <iostream>

using namespace v8;
using namespace Example;

void register_builtins(Isolate* isolate, Local<Object> global) {
    // 创建 Example 对象模板
    Local<ObjectTemplate> Example = ObjectTemplate::New(isolate);
    setMethod(isolate, Example, "print", Example::Print);
    setMethod(isolate, Example, "writeFile", Example::WriteFile);

    // 将 Example 对象挂到 global 对象上
    Local<Object> exampleInstance = Example->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
    global->Set(isolate->GetCurrentContext(), String::NewFromUtf8(isolate, "example", NewStringType::kNormal).ToLocalChecked(), exampleInstance).FromJust();
}

int main(int argc, char* argv[]) {
  // V8 的一些通用初始化逻辑
  V8::InitializeICUDefaultLocation(argv[0]);
  V8::InitializeExternalStartupData(argv[0]);
  std::unique_ptr<Platform> platform = platform::NewDefaultPlatform();
  V8::InitializePlatform(platform.get());
  V8::Initialize();
  // 创建 Isolate 时传入的参数
  Isolate::CreateParams create_params;
  create_params.array_buffer_allocator = ArrayBuffer::Allocator::NewDefaultAllocator();
  // 创建一个 Isolate，V8 的对象
  Isolate* isolate = Isolate::New(create_params);
  {
    Isolate::Scope isolate_scope(isolate);
    // 创建一个 HandleScope，用于下面分配 Handle
    HandleScope handle_scope(isolate);
    // 创建一个对象模版，用于创建全局对象
    Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
    // 创建一个上下文
    Local<Context> context = Context::New(isolate, nullptr, global);

    Context::Scope context_scope(context);

    
    // 获取 JS 全局对象
    Local<Object> globalInstance = context->Global();
    // 注册 C++ 模块
    register_builtins(isolate, globalInstance);
    
    {
      // 打开 JS 文件,将 JS 文件内容读取到内存
      if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
      }
      char* filename = argv[1];
      int fd = open(filename, 0, O_RDONLY);
      struct stat info;
      fstat(fd, &info);
      char *ptr = (char *)malloc(info.st_size + 1);
      read(fd, (void *)ptr, info.st_size);
      ptr[info.st_size] = '\0';
      // 要执行的 JS 代码
      Local<String> source = String::NewFromUtf8(isolate, ptr, NewStringType::kNormal, info.st_size).ToLocalChecked();
      // 编译
      Local<Script> script = Script::Compile(context, source).ToLocalChecked();
      // 解析完应该没用了，释放内存
      free(ptr);
      // 执行 JS
      Local<Value> result = script->Run(context).ToLocalChecked();
      String::Utf8Value utf8(isolate, result);
      std::string result_str = *utf8;
    }
  }

  isolate->Dispose();
  v8::V8::Dispose();
  delete create_params.array_buffer_allocator;
  return 0;
}


