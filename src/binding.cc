#ifdef _WIN32
#pragma warning(disable : 4996)
#endif

#include <nan.h>
#include "memcache.h"

class SharedCache : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("SharedCache").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "get", Get);
    Nan::SetPrototypeMethod(tpl, "set", Set);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("SharedCache").ToLocalChecked(),
             Nan::GetFunction(tpl).ToLocalChecked());
  }

private:
  explicit SharedCache() {}
  ~SharedCache() {}

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      SharedCache *obj = new SharedCache();
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static NAN_METHOD(Get) {
    SharedCache* obj = Nan::ObjectWrap::Unwrap<SharedCache>(info.Holder());
    if (info.Length() < 1 || !info[0]->IsString()) {
      Nan::ThrowTypeError("Key must be a string");
      return;
    }

    v8::String::Utf8Value key(info[0]->ToString(Nan::GetCurrentContext()).ToLocalChecked());
    std::string keyStr(*key);

    auto it = obj->cache.find(keyStr);
    if (it != obj->cache.end()) {
      info.GetReturnValue().Set(Nan::New(it->second).ToLocalChecked());
    } else {
      info.GetReturnValue().Set(Nan::Undefined());
    }
  }

  static NAN_METHOD(Set) {
    SharedCache* obj = Nan::ObjectWrap::Unwrap<SharedCache>(info.Holder());
    if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsString()) {
      Nan::ThrowTypeError("Key and value must be strings");
      return;
    }

    v8::String::Utf8Value key(info[0]->ToString(Nan::GetCurrentContext()).ToLocalChecked());
    v8::String::Utf8Value value(info[1]->ToString(Nan::GetCurrentContext()).ToLocalChecked());
    std::string keyStr(*key);
    std::string valueStr(*value);

    obj->cache[keyStr] = valueStr;
  }

  static inline Nan::Persistent<v8::Function> &constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  std::unordered_map<std::string, std::string> cache;
};

NODE_MODULE(sharedcache, SharedCache::Init)
