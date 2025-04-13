#include "cjson-parser.h"
#include <stdio.h>

/*
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
*/

#define CHUNK_SIZE 128

void* cjson_load_field_pointer_map(cjson_header_t* header, cjson_property_base_t* first_field_ptr, const char* schema) {
    cjson_property_base_t* field_ptr = first_field_ptr;
    header->schema = schema;
    char stop_loop = '\0';
    size_t capacity = 0;

    while (field_ptr->key && !stop_loop) {
        void* _data_ptr = (char*) field_ptr + sizeof(cjson_property_base_t);

        // Allocate or grow buffer when needed
        if (header->count == capacity) {
            capacity += CHUNK_SIZE;
            void* new_ptr = realloc(header->pointers, capacity * sizeof(struct cjson_field_pointer_pair_t));
            if (!new_ptr) {
                free(header->pointers);
                header->pointers = NULL;
                header->schema = NULL;
                header->count = 0ULL;
                stop_loop = '\1';
                break;
            }
            header->pointers = new_ptr;
        }

        // Fill entry
        header->pointers[header->count].key = field_ptr->key;
        header->pointers[header->count].address = _data_ptr;
        header->count++;

        // Advance
        field_ptr = (cjson_property_base_t*)((char*)_data_ptr + DISTANCE(field_ptr->size));
    }

    // Shrink-to-fit
    if (header->pointers && header->count < capacity) {
        void* final_ptr = realloc(header->pointers, header->count * sizeof(struct cjson_field_pointer_pair_t));
        if (final_ptr) {
            header->pointers = final_ptr;
        }
    }

    return header->pointers;
}

void* cjson_new(size_t type_size, const char *type_name, void *temp_struct) {
    void *_self = malloc(type_size);
    if (_self) {
        _self = memmove(_self, temp_struct, type_size);
        if (!cjson_load_field_pointer_map(
                (cjson_header_t*) _self,
                (cjson_property_base_t*) (((char*) _self) + sizeof(cjson_header_t)), type_name)) {
            free(_self);
            _self = NULL;
        }
    }
    return _self;
}
