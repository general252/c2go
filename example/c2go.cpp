#define GO_C_LIB_EXPORTS

#include "../c2go.h"
#include <stdio.h>

FnCallBackLib_C g_callback = 0;

GO_C_LIB_API int32_t Go4CInit_C(char* data, int32_t len, FnCallBackLib_C callback)
{
    printf("Go4CInit_C [%s][%d]\n", data, len);
    g_callback = callback;

    g_callback((char*)"method name", 11, 0, data, len);

    return 0;
}

GO_C_LIB_API int32_t Go4CRelease_C()
{
    printf("Go4CRelease_C\n");
    return 0;
}

GO_C_LIB_API int32_t Go4CInitCommand_C(char* data, int32_t len, uintptr_t handle)
{
    printf("hello cmd: %s\n", data);
    if (g_callback) {
        g_callback((char*)"method name", 11, handle, data, len);
    }
    return 0;
}
