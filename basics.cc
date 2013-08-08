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


Persistent<Array> p_array;
char* data;



void ArrayGet(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(
      (*reinterpret_cast<Local<Array>*>(&p_array))->Get(0));
}


void BasicNew(const FunctionCallbackInfo<Value>& args) {
  assert(args.IsConstructCall());
}


void ExternalNew(const FunctionCallbackInfo<Value>& args) {
  HandleScope scope(args.GetIsolate());
  Local<Object> obj = args[0].As<Object>();
  assert(!obj->HasIndexedPropertiesInExternalArrayData());
  obj->SetIndexedPropertiesToExternalArrayData(
      data, v8::kExternalUnsignedByteArray, 0);
  obj->GetIndexedPropertiesExternalArrayData();
}


void InternalNew(const FunctionCallbackInfo<Value>& args) {
  assert(args.IsConstructCall());
  HandleScope scope(args.GetIsolate());
  Local<Object> obj = args.This();
  assert(obj->InternalFieldCount() > 0);
  obj->SetAlignedPointerInInternalField(0, data);
  obj->GetAlignedPointerFromInternalField(0);
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  data = new char(8);

  Local<Array> array = Array::New();
  array->Set(0, String::New("hello world"));
  p_array.Reset(isolate, array);

  Local<FunctionTemplate> t = FunctionTemplate::New(ArrayGet);
  t->SetClassName(String::New("ArrayGet"));
  target->Set(String::New("ArrayGet"), t->GetFunction());

  t = FunctionTemplate::New(BasicNew);
  t->SetClassName(String::New("BasicNew"));
  target->Set(String::New("BasicNew"), t->GetFunction());

  t = FunctionTemplate::New(ExternalNew);
  t->SetClassName(String::New("ExternalNew"));
  target->Set(String::New("ExternalNew"), t->GetFunction());

  t = FunctionTemplate::New(InternalNew);
  t->SetClassName(String::New("InternalNew"));
  t->InstanceTemplate()->SetInternalFieldCount(1);
  target->Set(String::New("InternalNew"), t->GetFunction());
}


}  // namespace basics

NODE_MODULE(basics, basics::Initialize)
