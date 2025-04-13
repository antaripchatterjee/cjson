#include "cjson-parser.h"
#include <stdio.h>


void* cjson_load_field_pointer_map(cjson_header_t* header, cjson_property_base_t* first_field_ptr, const char* schema) {
    cjson_property_base_t* field_ptr = first_field_ptr;
    header->schema = schema;
    char stop_loop = '\0';
    while(field_ptr->key && !stop_loop) {
        void* _data_ptr = (char*) field_ptr + sizeof(cjson_property_base_t) ;
        if(header->pointers) {
            header->pointers = (struct cjson_field_pointer_pair_t*) realloc(
                header->pointers,
                sizeof(struct cjson_field_pointer_pair_t) * (header->count + 1)
            );
        } else {
            header->pointers = (struct cjson_field_pointer_pair_t*) malloc(
                sizeof(struct cjson_field_pointer_pair_t)
            );
        }
        if(header->pointers) {
            header->count++;
            header->pointers[header->count-1].key = field_ptr->key;
            header->pointers[header->count-1].address = _data_ptr;
            field_ptr = (cjson_property_base_t*) ((char*) _data_ptr + DISTANCE(field_ptr->size));
        } else {
            header->schema = NULL;
            header->count = 0ULL;
            stop_loop = '\1';
        }
    }
    return header->pointers;
}
