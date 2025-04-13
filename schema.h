#if !defined(__SCHEMA_H__)
#define __SCHEMA_H__

#include "cjson.h"

typedef struct {
    cjson_header_t _header;
    cjson_property_t(char[128]) address_text;
    cjson_property_t(unsigned short) postal_code;
    cjson_property_t(int) address_id;
    cjson_footer_t _footer;
} Address;

typedef struct {
    cjson_header_t _header;
    cjson_property_t(char[56]) firstname;
    cjson_property_t(char[128]) lastname;
    cjson_property_t(Address*) address;
    cjson_property_t(unsigned short) age;
    cjson_property_t(char*) honorific;
    cjson_footer_t _footer;
} Person;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
Address* newAddress();
Person* newPerson();
#ifdef __cplusplus
}
#endif // __cplusplus

#define CJSONSchema__Address(_ST) { \
    CJSONHeaderDef(_ST, _header), \
    CJSONSchemaDef(_ST, address_text), \
    CJSONSchemaDef(_ST, postal_code), \
    CJSONSchemaDef(_ST, address_id), \
    CJSONFooterDef(_ST, _footer) \
}

#define CJSONSchema__Person(_ST) { \
    CJSONHeaderDef(_ST, _header), \
    CJSONSchemaDef(_ST, firstname, "FirstName", "Antarip"), \
    CJSONSchemaDef(_ST, lastname), \
    CJSONSchemaDef(_ST, age), \
    CJSONSchemaDef(_ST, address, "address", newAddress()), \
    CJSONSchemaDef(_ST, honorific, "Prefix", "Mr."), \
    CJSONFooterDef(_ST, _footer) \
}

#endif // __SCHEMA_H__
