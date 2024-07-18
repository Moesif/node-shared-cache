#ifndef MEMCACHE_H_
#define MEMCACHE_H_

#ifndef _WIN32
typedef int HANDLE;
#else
#include <Windows.h>
#endif

#define HEADER_SIZE 262144

namespace cache {
    // Initialization (no changes typically needed)
    bool init(void* ptr, uint32_t blocks, uint32_t block_size_shift, bool forced);

    // Key-Value Operations
    int set(void* ptr, HANDLE fd, const uint16_t* key, size_t keyLen, const uint8_t* val, size_t valLen, uint8_t** oldval = nullptr, size_t* oldvalLen = nullptr);

    // Enumeration and Dump (C++11 nullptr for consistency)
    void _enumerate(void* ptr, HANDLE fd, void* enumerator, void(* callback)(void*,uint16_t*,size_t));
    void _dump(void* ptr, HANDLE fd, void* dumper, void(* callback)(void*,uint16_t*,size_t,uint8_t*));

    // Template Methods (Modernized Syntax)
    template <typename T>
    inline void enumerate(void* ptr, HANDLE fd, T* enumerator, void(*callback)(T*, uint16_t*, size_t)) {
        _enumerate(ptr, fd, enumerator, reinterpret_cast<void(*)(void*,uint16_t*,size_t)>(callback)); // Explicit cast
    }

    template <typename T>
    inline void dump(void* ptr, HANDLE fd, T* dumper, void(*callback)(T*, uint16_t*, size_t, uint8_t*)) {
        _dump(ptr, fd, dumper, reinterpret_cast<void(*)(void*,uint16_t*,size_t,uint8_t*)>(callback)); // Explicit cast
    }

    // Retrieval (Consider Error Handling Improvements)
    void get(void* ptr, HANDLE fd, const uint16_t* key, size_t keyLen, uint8_t*& val, size_t& valLen);
    void fast_get(void* ptr, HANDLE fd, const uint16_t* key, size_t keyLen, uint8_t*& val, size_t& valLen);

    // Existence Checks
    bool contains(void* ptr, HANDLE fd, const uint16_t* key, size_t keyLen);

    // Deletion
    bool unset(void* ptr, HANDLE fd, const uint16_t* key, size_t keyLen);

    // Clearing
    void clear(void* ptr, HANDLE fd);

    // Atomic Increments
    int32_t increase(void* ptr, HANDLE fd, const uint16_t* key, size_t keyLen, int32_t increase_by);
}

#endif
