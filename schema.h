#if !defined(__SCHEMA_H__)
#define __SCHEMA_H__

#include "cjson.h"

typedef struct {
    cjson_property(char[128]) address_text;
    cjson_property(unsigned short) postal_code;
    cjson_property(size_t) noproperty;
} Address;

typedef struct {
    cjson_property(char[128]) firstname;
    cjson_property(char[128]) lastname;
    cjson_property(unsigned short) age;
    cjson_property(Address) address;
    cjson_property(size_t) noproperty;
} Person;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
Address newAddress();
Person newPerson();
#ifdef __cplusplus
}
#endif // __cplusplus

#define CJSONSchema__Address(_O) { \
    CJSONSchemaDef(_O, address_text), \
    CJSONSchemaDef(_O, postal_code), \
    CJSONSchemaDefEnd(noproperty) \
}

#define CJSONSchema__Person(_O) { \
    CJSONSchemaDef(_O, firstname), \
    CJSONSchemaDef(_O, lastname), \
    CJSONSchemaDef(_O, age), \
    CJSONSchemaDef(_O, address, newAddress()), \
    CJSONSchemaDefEnd(noproperty) \
}

#endif // __SCHEMA_H__
