// g++ -fPIC -shared c2go.cpp -o c2go.so

#ifndef __C2GO_HEADER__
#define __C2GO_HEADER__

#include <stdint.h>

#ifdef _MSC_VER

#ifdef C2GO_LIB_EXPORTS
#define C2GO_LIB_API __declspec(dllexport)
#else
#define C2GO_LIB_API __declspec(dllimport)
#endif

#else

#define C2GO_LIB_API

#endif // _MSC_VER


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    struct MethodParam {
        char method[128]; // c method name
        char* data[16]; // in data list
        int32_t dataSize[16]; // peer in data size
        int64_t handles[16]; // go method pointer
        int64_t instance[4]; // instance handle
    };

    typedef void (*FnCallBack_C)(char* method, uintptr_t cmdId, char* data, int32_t len);

    C2GO_LIB_API int32_t C2Go_Init(FnCallBack_C callback);

    C2GO_LIB_API int32_t C2Go_Finish();

    // 参数结构体
    C2GO_LIB_API int32_t C2Go_Method(struct MethodParam* param);

#ifdef __cplusplus
};
#endif // __cplusplus

#endif
