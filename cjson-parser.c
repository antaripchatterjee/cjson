#include "cjson-parser.h"
#include <stdlib.h>
#include <string.h>

void cjson_read_key_set_from_schema(void* _schema, cjson_key_set* _set) {
    cjson_property_base* key_ptr = (cjson_property_base*) _schema;
    char* key;
    while((key = (char*) key_ptr->key)) {
        const size_t index = _set->count++;
        _set->keys = (cjson_key_to_data_ptr_map*)(
            _set->keys == NULL ?
            malloc(sizeof(cjson_key_to_data_ptr_map)) :
            realloc(_set->keys, _set->count * sizeof(cjson_key_to_data_ptr_map))
        );
        _set->keys[index].name = key;
        _set->keys[index].data_ptr = ((void*) key_ptr + sizeof(cjson_property_base));
        key_ptr = (cjson_property_base*) ((void*) key_ptr + sizeof(cjson_property_base) + key_ptr->size);
    }
}

void cjson_free_key_set(cjson_key_set* _set) {
    if(_set) {
        if(_set->keys) {
            free(_set->keys);
        }
        _set->count = 0L;
    }
}