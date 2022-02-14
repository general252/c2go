//  g++ -fPIC -shared bcd.cpp -o c2go.so

/*

#ifndef __C2GO_HEADER__
#define __C2GO_HEADER__

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

    int32_t C2Go_Init(FnCallBack_C callback);

    int32_t C2Go_Finish();

    // 参数结构体
    int32_t C2Go_Method(struct MethodParam* param);

#ifdef __cplusplus
};
#endif // __cplusplus



#endif


*/

/*




#include "bcd.h"
#include <stdio.h>

FnCallBack_C m_callback = 0;

int32_t C2Go_Init(FnCallBack_C callback)
{
    printf("abc\n");

    m_callback = callback;
    return  888;
}

int32_t C2Go_Finish()
{
    return  int32_t();
}

int32_t C2Go_Method(struct MethodParam* param)
{
    printf("method: %s\n", param->method);
    for (int i = 0; i < 16; i++)
    {
        printf("%d %.*s %d\n", i, param->dataSize[i], param->data[i], param->dataSize[i]);
    }


    if (m_callback)
    {
        for (size_t i = 0; i < 16; i++)
        {
            if (param->handles[i]) {
                m_callback((char*)"math", param->handles[i], (char*)"hello", 5);
            }
        }
    }

    param->instance[0] = 1233;

    return  0;
}

*/
