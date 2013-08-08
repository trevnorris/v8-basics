#include <node.h>
#include <v8.h>

#include <njsutil.h>

namespace basics {

using v8::Array;
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


Persistent<String> p_string;


void GetPropIndex(const FunctionCallbackInfo<Value>& args) {
  args[0].As<Object>()->Get(0);
}


void GetPropName(const FunctionCallbackInfo<Value>& args) {
  args[0].As<Object>()->Get(
      *reinterpret_cast<Local<String>*>(&p_string));
}


void SetPropIndex(const FunctionCallbackInfo<Value>& args) {
  args[0].As<Object>()->Set(0, True(args.GetIsolate()));
}


void SetPropName(const FunctionCallbackInfo<Value>& args) {
  args[0].As<Object>()->Set(
      *reinterpret_cast<Local<String>*>(&p_string),
      True(args.GetIsolate()));
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  p_string.Reset(isolate, String::New("sym"));

  Local<FunctionTemplate> t = FunctionTemplate::New(GetPropIndex);
  t->SetClassName(String::New("getPropIndex"));
  target->Set(String::New("getPropIndex"), t->GetFunction());

  t = FunctionTemplate::New(GetPropName);
  t->SetClassName(String::New("getPropName"));
  target->Set(String::New("getPropName"), t->GetFunction());

  t = FunctionTemplate::New(SetPropIndex);
  t->SetClassName(String::New("setPropIndex"));
  target->Set(String::New("setPropIndex"), t->GetFunction());

  t = FunctionTemplate::New(SetPropName);
  t->SetClassName(String::New("setPropName"));
  target->Set(String::New("setPropName"), t->GetFunction());
}


}  // namespace basics

NODE_MODULE(basics, basics::Initialize)
