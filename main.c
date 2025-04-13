#include <stdio.h>
#include "jsondata.h"
#include "schema.h"



int main() {
    Person *person = newPerson();
    if(person) {
        free(person->address.data->_header.pointers);
        free(person->address.data);
        free(person->_header.pointers);
        free(person);
    }
    return 0;
}
