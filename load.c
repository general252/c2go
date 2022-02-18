#include "load.h"

#if defined(CGO_OS_WINDOWS)
#include <windows.h>
static HMODULE libraryHandle = NULL;
#else
#include <dlfcn.h>
static void* libraryHandle = NULL;
#endif

typedef int32_t (*Fn_Go4CInit_C)(char* data, int32_t len, FnCallBackLib_C callback);
typedef int32_t (*Fn_Go4CRelease_C)();
typedef int32_t (*Fn_Go4CInitCommand_C)(char* data, int32_t len, uintptr_t handle);

static Fn_Go4CInit_C        fn_Go4CInit_C = 0;
static Fn_Go4CRelease_C     fn_Go4CRelease_C = 0;
static Fn_Go4CInitCommand_C fn_Go4CInitCommand_C = 0;

int mLoadLibrary(char* libraryName)
{
#if defined(CGO_OS_WINDOWS)
	libraryHandle = LoadLibraryA(libraryName);
	if (!libraryHandle) {
	    printf("LoadLibrary fail. %d\n", GetLastError());
		return -1;
	}

	fn_Go4CInit_C = (Fn_Go4CInit_C)GetProcAddress(libraryHandle, "Go4CInit_C");
	fn_Go4CRelease_C = (Fn_Go4CRelease_C)GetProcAddress(libraryHandle, "Go4CRelease_C");
	fn_Go4CInitCommand_C = (Fn_Go4CInitCommand_C)GetProcAddress(libraryHandle, "Go4CInitCommand_C");
#else
    libraryHandle = dlopen(libraryName, RTLD_LAZY);
    if (!libraryHandle) {
        return -1;
    }

    fn_Go4CInit_C = (Fn_Go4CInit_C)dlsym(libraryHandle, "Go4CInit_C");
    fn_Go4CRelease_C = (Fn_Go4CRelease_C)dlsym(libraryHandle, "Go4CRelease_C");
    fn_Go4CInitCommand_C = (Fn_Go4CInitCommand_C)dlsym(libraryHandle, "Go4CInitCommand_C");
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


int32_t call_Go4CInit_C(char* data, int32_t len, FnCallBackLib_C callback) {
	if (!fn_Go4CInit_C) {
		return -1;
	}
	return fn_Go4CInit_C(data, len, callback);
}

int32_t call_Go4CRelease_C() {
	if (!fn_Go4CRelease_C) {
		return -1;
	}
	return fn_Go4CRelease_C();
}

int32_t call_Go4CInitCommand_C(char* data, int32_t len, uintptr_t handle) {
	if (!fn_Go4CInitCommand_C) {
		return -1;
	}

	return fn_Go4CInitCommand_C(data, len, handle);
}

