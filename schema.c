#include "schema.h"

Address newAddress() {
    return CJSONSchema(Address);
}

Person newPerson() {
    return CJSONSchema(Person);
}