#include "v8.h"
#include "libplatform/libplatform.h"
#include "v8-context.h"
#include "v8-initialization.h"
#include "v8-isolate.h"
#include "v8-local-handle.h"
#include "v8-primitive.h"
#include "v8-script.h"

using namespace v8;

namespace Example {
    void WriteFile(const FunctionCallbackInfo<Value> &args);
    void Print(const FunctionCallbackInfo<Value> &args);
}
