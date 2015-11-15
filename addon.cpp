#include <node.h>
#include "hash.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Value;
using v8::Exception;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  String::Utf8Value str(args[0]->ToString());
  int len = str.length();
  const char * buffer = *str;

  uint64_t hashValue = hash(19, buffer, len);
  Local<Number> hashNumber = Number::New(isolate, hashValue);

  args.GetReturnValue().Set(hashNumber);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hash", Method);
}

NODE_MODULE(hasher, init)
