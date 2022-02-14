#include "load.h"

#if defined(CGO_OS_WINDOWS)
#include <windows.h>
static HMODULE libraryHandle = NULL;
#else
#include <dlfcn.h>
static void* libraryHandle = NULL;
#endif

typedef int32_t (*fnC2Go_Init)(FnCallBack_C callback);
typedef int32_t (*fnC2Go_Finish)();
typedef int32_t (*fnC2Go_Method)(struct MethodParam* param);

static fnC2Go_Init f_C2Go_Init = 0;
static fnC2Go_Finish f_C2Go_Finish = 0;
static fnC2Go_Method f_C2Go_Method = 0;

int mLoadLibrary(char* libraryName)
{
#if defined(CGO_OS_WINDOWS)
	libraryHandle = LoadLibraryA(libraryName);
	if (!libraryHandle) {
	    printf("LoadLibrary fail. %d\n", GetLastError());
		return -1;
	}

	f_C2Go_Init = (fnC2Go_Init)GetProcAddress(libraryHandle, "C2Go_Init");
	f_C2Go_Finish = (fnC2Go_Finish)GetProcAddress(libraryHandle, "C2Go_Finish");
	f_C2Go_Method = (fnC2Go_Method)GetProcAddress(libraryHandle, "C2Go_Method");
#else
    libraryHandle = dlopen(libraryName, RTLD_LAZY);
    if (!libraryHandle) {
        return -1;
    }

    f_C2Go_Init = (fnC2Go_Init)dlsym(libraryHandle, "C2Go_Init");
    f_C2Go_Finish = (fnC2Go_Finish)dlsym(libraryHandle, "C2Go_Finish");
    f_C2Go_Method = (fnC2Go_Method)dlsym(libraryHandle, "C2Go_Method");
#endif

	return 0;
}

int mUnLoadLibrary()
{
#if defined(CGO_OS_WINDOWS)
	if (libraryHandle) {
		FreeLibrary(libraryHandle);
		libraryHandle = NULL;
	}
#else
    if (libraryHandle) {
		dlclose(libraryHandle);
		libraryHandle = NULL;
	}
#endif
}


int32_t call_C2Go_Init() {
	if (!f_C2Go_Init) {
		return -1;
	}
	return f_C2Go_Init(GoFnCallback);
}

int32_t call_C2Go_Finish() {
	if (!f_C2Go_Finish) {
		return -1;
	}
	return f_C2Go_Finish();
}

int32_t call_C2Go_Method(struct MethodParam* param) {
	if (!f_C2Go_Method) {
		return -1;
	}

	return f_C2Go_Method(param);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MethodParam* MethodParamNew(char* method, int32_t len) {
    struct MethodParam* obj = (struct MethodParam*)malloc(sizeof(struct MethodParam));
    memset(obj, 0, sizeof(struct MethodParam));

    memcpy(obj->method, method, len);

    return obj;
}

void MethodParamSetData(struct MethodParam* param, int32_t index, char* data, int32_t len) {
    if (param) {
        param->data[index] = data;
        param->dataSize[index] = len;
    }
}

void MethodParamSetHandle(struct MethodParam* param, int32_t index, int64_t handle) {
    if (param) {
        param->handles[index] = handle;
    }
}

void MethodParamSetInstance(struct MethodParam* param, int32_t index, int64_t instance) {
    if (param) {
        param->instance[index] = instance;
    }
}
int64_t MethodParamGetInstance(struct MethodParam* param, int32_t index) {
    if (param) {
        return param->instance[index];
    }
    return -1;
}

void MethodParamDelete(struct MethodParam* param) {
    if (param) {
        free(param);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
