#include "my_file.h"
#include <iostream>

using namespace std;

void MyFile::writeFile(const FunctionCallbackInfo<Value> &args) {
    V8_ISOLATE
    string ss = formatOut(args);
    string filename = generateRandomFilename();
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << ss;
        outFile.close();
    }
}

string MyFile::generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += charset[dist(rng)];
    }
    return random_string;
}

string MyFile::generateRandomFilename() {
    string random_string = generateRandomString(10); // Generate a random string of length 10
    return random_string + ".txt";
}

void MyFile::say(V8_ARGS) {
    V8_ISOLATE
    string ss = formatOut(args);
    cout << ss << endl;
}

string MyFile::formatOut(V8_ARGS) {
    Isolate* isolate = args.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();
    std::string str = "";
    for(int i = 0;  i < args.Length(); i++) {
        Local<Value> arg = args[i];
        if(arg.IsEmpty()) {
            str += "undefined";
        } else if(arg->IsNull()) {
            str += "null";
        } else if(arg->IsTrue()) {
            str += "true";
        } else if(arg->IsFalse()) {
            str += "false";
        } else if(arg->IsInt32()) {
            str += std::to_string(arg->Int32Value(context).ToChecked());
        } else if(arg->IsNumber()) {
            str += std::to_string(arg->NumberValue(context).ToChecked());
        } else if(arg->IsString()) {
            String::Utf8Value value(isolate, arg);
            str += *value;
        } else if(arg->IsArray()) {
            Local<Array> array = Local<Array>::Cast(arg);
            str += "[";
            for(int i = 0; i < array->Length(); i++) {
                if(i > 0) {
                    str += ", ";
                }
                Local<Value> element = array->Get(context, i).ToLocalChecked();
                if(element->IsInt32()) {
                    str += std::to_string(element->Int32Value(context).ToChecked());
                } else if(element->IsNumber()) {
                    str += std::to_string(element->NumberValue(context).ToChecked());
                } else if(element->IsString()) {
                    String::Utf8Value value(isolate, element);
                    str += *value;
                }
            }
            str += "]";
        } else if(arg->IsObject()) {
            v8::Local<v8::String> tmp = v8::JSON::Stringify(context, arg).ToLocalChecked();
            v8::String::Utf8Value value(isolate, tmp);
            str += *value;
        }
    }

    return str;
}