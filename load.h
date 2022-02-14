#ifndef __MY__C2GO__WIN__HEADER__
#define __MY__C2GO__WIN__HEADER__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "c2go.h"

// golang export function
void GoFnCallback(char* method, uintptr_t funcPtr, char* data, int32_t length);

int mLoadLibrary(char* libraryName) ;
int mUnLoadLibrary() ;


int32_t call_C2Go_Init();
int32_t call_C2Go_Finish();
int32_t call_C2Go_Method(struct MethodParam* param);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MethodParam* MethodParamNew(char* method, int32_t len);
void MethodParamSetData(struct MethodParam* param, int32_t index, char* data, int32_t len);
void MethodParamSetHandle(struct MethodParam* param, int32_t index, int64_t handle);
void MethodParamSetInstance(struct MethodParam* param, int32_t index, int64_t instance);
int64_t MethodParamGetInstance(struct MethodParam* param, int32_t index);
void MethodParamDelete(struct MethodParam* param) ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
