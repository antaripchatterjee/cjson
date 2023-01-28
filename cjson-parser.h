#if !defined(__CJSON_PARSER_H__)
#define __CJSON_PARSER_H__

#include "cjson-common.h"

#define CJSONSchemaDefWithDefaultValue(_O, _K) ._K = { .key = #_K, .size = sizeof(_O._K.data) }
#define CJSONSchemaDefWithCustomValue(_O, _K, _V) ._K = { .key = #_K, .size = sizeof(_O._K.data), .data = _V }
#define CJSONSchemaDefMacroIsFourthArg(arg1, arg2, arg3, arg4, ...) arg4
#define CJSONSchemaDefMacroSelector(...) CJSONSchemaDefMacroIsFourthArg( \
    __VA_ARGS__, \
    CJSONSchemaDefWithCustomValue, \
    CJSONSchemaDefWithDefaultValue, \
)
#define CJSONSchemaDef(...) CJSONSchemaDefMacroSelector(__VA_ARGS__)(__VA_ARGS__)

#define CJSONSchemaDefEnd(_K) ._K = { .key = NULL, .size = 0L, .data = 0L }

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void cjson_read_key_set_from_schema(void* _schema, cjson_key_set* _set);
void cjson_free_key_set(cjson_key_set* _set);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __CJSON_PARSER_H__
