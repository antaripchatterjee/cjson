#if !defined(__MAIN_H__)
#define __MAIN_H__

#include "cjson.h"

#define JSONData "{\n\t" \
    "\"firstname\" : \"Robin\",\n\t" \
    "\"lastname\" : \"Roy\",\n\t" \
    "\"age\" : 30,\n\t" \
    "\"address\" : {\n\t\t" \
    "\"address_text\" : \"Gujrat\",\n\t\t" \
    "\"postal_code\" : 396215\n\t" \
    "}\n"\
"}" \

typedef struct {
    cjson_property(char[128]) address_text;
    cjson_property(unsigned short) postal_code;
    cjson_property(size_t) noproperty;
} Address;

typedef struct {
    cjson_property(char[128]) firstname;
    cjson_property(char[128]) lastname;
    cjson_property(unsigned short) age;
    // cjson_property(struct Address) address;
    cjson_property(size_t) noproperty;
} Person;

#define CJSONSchema__Address(_O) { \
    CJSONSchemaDef(_O, address_text), \
    CJSONSchemaDef(_O, postal_code), \
    CJSONSchemaDefEnd(noproperty) \
}

#define CJSONSchema__Person(_O) { \
    CJSONSchemaDef(_O, firstname), \
    CJSONSchemaDef(_O, lastname), \
    CJSONSchemaDef(_O, age), \
    CJSONSchemaDefEnd(noproperty) \
}

#endif // __MAIN_H__
