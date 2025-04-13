#include "schema.h"
#include <stdio.h>

Address *newAddress()
{    
    Address *address = CJSONNew(Address);
    for(size_t i = 0; i < address->_header.count; i++) {
        printf("%s.%s -> %p\n", address->_header.schema, address->_header.pointers[i].key, address->_header.pointers[i].address);
    }
    return address;
}

Person *newPerson()
{
    Person *person = CJSONNew(Person);
    for(size_t i = 0; i < person->_header.count; i++) {
        printf("%s.%s -> %p\n", person->_header.schema, person->_header.pointers[i].key, person->_header.pointers[i].address);
    }
    return person;
}