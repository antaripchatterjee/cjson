#if !defined(__CJSON_H__)
#define __CJSON_H__
#include "cjson-parser.h"

#define CJSONSchema(_T) ((_T) CJSONSchema__##_T((_T){0}))

#endif // __CJSON_H__
