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

using namespace v8;

#define MV(module) \
    module::Initialize(isolate, global, context);


#define MOLEULES_LIST(V) \
    V(Console1);       




void setMethod(Isolate *isolate, 
                Local<ObjectTemplate> 
                recv, const char *name, 
                FunctionCallback callback);

void register_builtins(Isolate * isolate, Local<Object> global, Local<Context> context);