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

#define V8_ARGS const FunctionCallbackInfo<Value> &args
#define V8_ISOLATE Isolate * isolate = args.GetIsolate();
#define V8_CONTEXT Local<Context> context = args.GetIsolate()->GetCurrentContext();
namespace MyFile {
    void writeFile(const FunctionCallbackInfo<Value> &args);
    string generateRandomString(size_t length);
    string generateRandomFilename();
    void log(V8_ARGS);
    string formatOut(V8_ARGS);
}