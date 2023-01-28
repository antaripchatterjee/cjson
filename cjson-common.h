#if !defined(__CJSON_COMMON_H__)
#define __CJSON_COMMON_H__

#include <stddef.h>

typedef struct { const char* key; const size_t size; } cjson_property_base;

typedef struct { const char* name; void* data_ptr; } cjson_key_to_data_ptr_map;

typedef struct { cjson_key_to_data_ptr_map* keys; size_t count; } cjson_key_set;

#define cjson_property(T) struct { const char* key; const size_t size; typeof(T) data; }

#endif // __CJSON_COMMON_H__
