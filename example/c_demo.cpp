/*

#include "libcbd.h"
#include <stdio.h>

FnCallBack_C m_callback = 0;

LIBCBD_API int32_t C2Go_Init(FnCallBack_C callback)
{
    printf("abc\n");

    m_callback = callback;
    return  888;
}

LIBCBD_API int32_t C2Go_Finish()
{
    return  int32_t();
}

LIBCBD_API int32_t C2Go_Method(struct MethodParam* param)
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
