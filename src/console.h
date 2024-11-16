#include "uv.h"
#include <random>
#include <string>
#include <fstream>
#include "v8.h"
#include "include/libplatform/libplatform.h"
#include "include/v8-context.h"
#include "include/v8-initialization.h"
#include "include/v8-isolate.h"
#include "include/v8-local-handle.h"
#include "include/v8-primitive.h"
#include "include/v8-script.h"
#include "util.h"
#include <iostream>

using namespace std;
using namespace v8;

namespace Console1 {
    void Log(const FunctionCallbackInfo<Value> &args);
    void Initialize(Isolate * isolate, Local<Object> global, Local<Context> context);
}