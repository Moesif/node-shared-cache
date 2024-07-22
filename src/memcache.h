#ifndef MEMCACHE_H
#define MEMCACHE_H

#include <nan.h>
#include <unordered_map>
#include <string>

class MemCache {
public:
  MemCache();
  ~MemCache();

  std::string get(const std::string& key);
  void set(const std::string& key, const std::string& value);

private:
  std::unordered_map<std::string, std::string> cache;
};

#endif // MEMCACHE_H
