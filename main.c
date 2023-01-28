#include <stdio.h>
#include "main.h"


int main() {
    Person person = CJSONSchema(Person);
    cjson_key_set key_set = { .keys = NULL, .count = 0L };
    cjson_read_key_set_from_schema(&person, &key_set);
    for(size_t i = 0; i < key_set.count; i++) {
        puts(key_set.keys[i].name);
    }
    cjson_free_key_set(&key_set);
    puts("Done");
    return 0;
}
