#if !defined(__CJSON_PARSER_H__)
#define __CJSON_PARSER_H__

#include <stdlib.h>
#include <string.h>

#define DISTANCE(SIZE) (SIZE % 8ULL == 0ULL ? SIZE : (SIZE + 8ULL - SIZE % 8ULL))

#define CJSONSchemaDefWithDefaultKeyNameAndNoValue(_O, _F) \
    ._F = { .key = #_F, .size = sizeof(_O._F.data) }
#define CJSONSchemaDefWithCustomKeyNameAndNoValue(_O, _F, _K) \
    ._F = { .key = _K, .size = sizeof(_O._F.data) }
#define CJSONSchemaDefWithCustomKeyNameAndCustomValue(_O, _F, _K, _V) \
    ._F = { .key = _K, .size = sizeof(_O._F.data), .data = _V }

#define CJSONSchemaDefMacroSelectFifthArg(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define CJSONSchemaDefMacroSelector(...) CJSONSchemaDefMacroSelectFifthArg( \
    __VA_ARGS__, \
    CJSONSchemaDefWithCustomKeyNameAndCustomValue, \
    CJSONSchemaDefWithCustomKeyNameAndNoValue, \
    CJSONSchemaDefWithDefaultKeyNameAndNoValue, \
)
#define CJSONSchemaDef(...) CJSONSchemaDefMacroSelector(__VA_ARGS__)(__VA_ARGS__)

#define CJSONHeaderDef(_O, _F) ._F = { .count = 0L, .pointers = (struct cjson_field_pointer_pair_t*) NULL }
#define CJSONFooterDef(_O, _F) ._F = { .key = ((char*) 0), .schema = #_O }

struct cjson_field_pointer_pair_t { const char* key; const void* address; };


typedef struct { const char* schema; size_t count;  struct cjson_field_pointer_pair_t* pointers; } cjson_header_t;
typedef struct { const char* key; const char* schema; } cjson_footer_t;
typedef struct { const char* key; const size_t size; } cjson_property_base_t;

#define cjson_property_t(T) struct { const char* key; const size_t size; __typeof__(T) data; }
/*
#define CJSONNew(_T) ({ \
    _T* _self = (_T*) malloc(sizeof(_T)); \
    if(_self) { \
        _T _temp = CJSONSchema(_T); \
        _self = (_T*) memmove(_self, &_temp, sizeof(_T)); \
        if(!cjson_load_field_pointer_map( \
            (cjson_header_t*) _self, \
            (cjson_property_base_t*) (((void*) _self) + sizeof(cjson_header_t)), \
            #_T \
        )) { \
            free(_self); \
            _self = ((_T*) 0); \
        } \
    } \
    _self; \
})
*/

#define CJSONNew(_T) ((_T*) cjson_new(sizeof(_T), #_T, &(CJSONSchema(_T))))

#ifdef __cplusplus // __cplusplus
extern "C" {
#endif
void* cjson_load_field_pointer_map(cjson_header_t* header, cjson_property_base_t* first_field_ptr, const char* schema);
void* cjson_new(size_t type_size, const char *type_name, void *temp_struct);
#ifdef __cplusplus // __cplusplus
}
#endif

#endif // __CJSON_PARSER_H__
