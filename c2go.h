// g++ -fPIC -shared c2go.cpp -o c2go.so

#ifdef _MSC_VER

#ifdef GO_C_LIB_EXPORTS
#define GO_C_LIB_API __declspec(dllexport)
#else
#define GO_C_LIB_API __declspec(dllimport)
#endif

#else

#define GO_C_LIB_API

#endif // _MSC_VER


#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    typedef void (*FnCallBackLib_C)(char* data, int32_t len);
    typedef void (*FnCallBackCmd_C)(int32_t handle, char* data, int32_t len);

    GO_C_LIB_API int32_t Go4CInit_C(char* data, int32_t len, FnCallBackLib_C callback);

    GO_C_LIB_API int32_t Go4CRelease_C();

    GO_C_LIB_API int32_t Go4CInitCommand_C(char* data, int32_t len, FnCallBackCmd_C cmd_callback, int32_t handle);

#ifdef __cplusplus
};
#endif // __cplusplus

