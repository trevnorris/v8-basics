#include <node.h>
#include <v8.h>

#include "njsutil.h"

namespace basics {

using v8::Array;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Handle;
using v8::HandleScope;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

Persistent<Array> p_array;
Persistent<Function> p_function;
Persistent<Object> p_object;
Persistent<String> p_string;


void Setup(const FunctionCallbackInfo<Value>& args) {
  Local<Function> fn = args[0].As<Function>();
  Local<Object> obj = args[1].As<Object>();
  Local<Array> array = args[2].As<Array>();

  if (!fn->IsFunction() || !obj->IsObject() || !array->IsArray())
    njsutil::ThrowTypeError("Arguments are incorrect types");

  Isolate* isolate = args.GetIsolate();

  p_function.Reset(isolate, fn);
  p_object.Reset(isolate, obj);
  p_array.Reset(isolate, array);
}

void Run(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Local<Array> array = njsutil::PersistentToLocal(isolate, p_array);
  array->Set(array->Length(), njsutil::PersistentToLocal(isolate, p_function));
  array->Set(array->Length(), njsutil::PersistentToLocal(isolate, p_function));
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<FunctionTemplate> t;

  t = FunctionTemplate::New(Setup);
  t->SetClassName(String::NewFromUtf8(isolate, "Setup"));
  target->Set(String::NewFromUtf8(isolate, "setup"), t->GetFunction());

  t = FunctionTemplate::New(Run);
  t->SetClassName(String::NewFromUtf8(isolate, "run"));
  target->Set(String::NewFromUtf8(isolate, "run"), t->GetFunction());
}


}  // namespace basics

NODE_MODULE(basics, basics::Initialize)
