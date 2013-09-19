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

Persistent<Function> p_function;


void Setup(const FunctionCallbackInfo<Value>& args) {
  Local<Function> fn = args[0].As<Function>();

  if (!fn->IsFunction())
    njsutil::ThrowTypeError("Arguments are incorrect types");

  Isolate* isolate = args.GetIsolate();

  p_function.Reset(isolate, fn);
}

void Run(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(
      njsutil::PersistentToLocal(args.GetIsolate(), p_function));
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<FunctionTemplate> t;

  t = FunctionTemplate::New(Setup);
  t->SetClassName(String::NewFromUtf8(isolate, "setup"));
  target->Set(String::NewFromUtf8(isolate, "setup"), t->GetFunction());

  t = FunctionTemplate::New(Run);
  t->SetClassName(String::NewFromUtf8(isolate, "run"));
  target->Set(String::NewFromUtf8(isolate, "run"), t->GetFunction());
}


}  // namespace basics

NODE_MODULE(basics, basics::Initialize)
