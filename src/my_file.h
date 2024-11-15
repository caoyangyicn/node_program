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

using namespace std;
using namespace v8;

#define V8_CONTEXT Local<Context> context = args.GetIsolate()->GetCurrentContext();
namespace Example {
    void WriteFile(const FunctionCallbackInfo<Value> &args);
    void Print(const FunctionCallbackInfo<Value> &args);
}
