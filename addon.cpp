#include <node.h>
#include "hash.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Function;
using v8::Value;
using v8::Exception;

void Hash(const FunctionCallbackInfo<Value>& args) {
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

void Sum(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsNumber() || !args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

   double value = args[0]->NumberValue() + args[1]->NumberValue();
   Local<Number> sum = Number::New(isolate, value);

  args.GetReturnValue().Set(sum);
}

void GetNameAsync(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  Local<Function> cb = Local<Function>::Cast(args[0]);
  const unsigned argc = 1;
  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "Brian R. Bondy") };
  cb->Call(Null(isolate), argc, argv);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hash", Hash);
  NODE_SET_METHOD(exports, "sum", Sum);
  NODE_SET_METHOD(exports, "getNameAsync", GetNameAsync);
}

NODE_MODULE(hasher, init)
