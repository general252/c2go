package c2go

/*
#cgo windows CFLAGS: -DCGO_OS_WINDOWS=1
#cgo darwin CFLAGS: -DCGO_OS_DARWIN=1
#cgo linux CFLAGS: -DCGO_OS_LINUX=1

#cgo CFLAGS: -I.
#cgo !windows LDFLAGS: -ldl

#include "load.h"

*/
import "C"

import (
	"fmt"
	"log"
	"reflect"
	"unsafe"
)

//export FnCallBackLibGO
func FnCallBackLibGO(method *C.char, methodLen C.int32_t, handle C.uintptr_t, data *C.char, len C.int32_t) {
	//var s = C.GoStringN(method, methodLen)
	var s []byte = C.GoBytes(unsafe.Pointer(data), len)

	if uint64(handle) > 0 {
		v, ok := Handle(handle).Value()
		if ok {
			v(s)
		}
	} else {
		if defaultLibraryCallback != nil {
			methodName := C.GoBytes(unsafe.Pointer(method), methodLen)
			defaultLibraryCallback(methodName, s)
		}
	}
}

var (
	defaultLibraryCallback = func(method []byte, data []byte) {}
)

// LoadLibrary 加载动态库
func LoadLibrary(libraryName string) error {
	log.Println(C.GoString(C.os()))

	name := C.CString(libraryName)
	defer C.free(unsafe.Pointer(name))

	rc := C.mLoadLibrary(name)
	if rc != 0 {
		return fmt.Errorf("load library fail %v", rc)
	}

	return nil
}

// UnLoadLibrary 卸载动态库
func UnLoadLibrary() {
	C.mUnLoadLibrary()
}

func Init(data []byte, fn func(method []byte, data []byte)) {
	in := (*C.char)(unsafe.Pointer((*reflect.StringHeader)(unsafe.Pointer(&data)).Data))
	inLen := C.int32_t(len(data))

	defaultLibraryCallback = fn

	var r = C.call_Go4CInit_C(in, inLen, C.FnCallBackLib_C(C.FnCallBackLibGO))
	log.Println(r)
}

func Finish() {
	C.call_Go4CRelease_C()
}

func Command(data []byte, h Handle) int {
	inData := (*C.char)(unsafe.Pointer((*reflect.StringHeader)(unsafe.Pointer(&data)).Data))
	inDataLen := C.int32_t(len(data))

	var rc = C.call_Go4CInitCommand_C(inData, inDataLen, C.uintptr_t(h))

	return int(rc)
}
