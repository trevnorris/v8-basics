#include <node.h>
#include <v8.h>

#include <openssl/md5.h>


using namespace v8;

Isolate* isolate;


Handle<Value> NodeMD5(const Arguments& args) {
  HandleScope scope(isolate);

  String::AsciiValue str(args[0]);
  const unsigned char* in = reinterpret_cast<const unsigned char*>(*str);
  unsigned char* out = new unsigned char[MD5_DIGEST_LENGTH];
  MD5(in, sizeof(in), out);

  Local<String> ret = String::New(reinterpret_cast<const char*>(out));

  return scope.Close(ret);
}


void Initialize(Handle<Object> target) {
  isolate = Isolate::GetCurrent();

  HandleScope scope(isolate);

  target->Set(String::New("md5"),
      FunctionTemplate::New(NodeMD5)->GetFunction());
}


NODE_MODULE(basics, Initialize)
