#ifndef __MY__C2GO__WIN__HEADER__
#define __MY__C2GO__WIN__HEADER__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "c2go.h"

int mLoadLibrary(char* libraryName) ;
int mUnLoadLibrary() ;

// golang export function
void FnCallBackLibGO(char* method, int32_t methodLen, uintptr_t handle, char* data, int32_t len);

int32_t call_Go4CInit_C(char* data, int32_t len, FnCallBackLib_C callback);
int32_t call_Go4CRelease_C();
int32_t call_Go4CInitCommand_C(char* data, int32_t len, uintptr_t handle);


#if defined(CGO_OS_WINDOWS)
	static const char* os() { return "windowns"; }
#elif defined(CGO_OS_DARWIN)
	static const char* os() { return "darwin"; }
#elif defined(CGO_OS_LINUX)
	static const char* os() { return "linux"; }
#else
	static const char* os() { return "unknown"; }
#endif

#endif  // __MY__C2GO__WIN__HEADER__
