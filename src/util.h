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

void setObjectValue(Isolate *isolate, 
                Local<Object> 
                recv, const char *name, 
                Local<Value> value);

void setMethod(Isolate *isolate, 
                Local<ObjectTemplate> 
                recv, const char *name, 
                FunctionCallback callback);