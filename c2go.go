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
	"runtime/cgo"
	"unsafe"
)

//export GoFnCallback
func GoFnCallback(method *C.char, handle C.uintptr_t, data *C.char, length C.int32_t) {
	var methodName = C.GoString(method)
	_ = methodName

	var s []byte = C.GoBytes(unsafe.Pointer(data), length)

	defer func() {
		if err := recover(); err != nil {
		}
	}()

	h := cgo.Handle(handle)
	val := h.Value()

	if dataCallback, ok := val.(func([]byte)); ok {
		dataCallback(s)
	}
}

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

func Init() {
	var r = C.call_C2Go_Init()
	log.Println(r)
}

func Finish() {
	C.call_C2Go_Finish()
}

func Method(method string, handles []cgo.Handle, dataList [][]byte, instances []int64) int {
	dataMethod := []byte(method)
	inDataMethod := (*C.char)(unsafe.Pointer((*reflect.StringHeader)(unsafe.Pointer(&dataMethod)).Data))
	inDataMethodLen := C.int32_t(len(dataMethod))

	// malloc
	var param = C.MethodParamNew(inDataMethod, inDataMethodLen)

	// instance
	for i := 0; i < len(instances) && i < 4; i++ {
		h := C.int64_t(instances[i])
		C.MethodParamSetInstance(param, C.int32_t(i), h)
	}

	// handle
	for i := 0; i < len(handles) && i < 16; i++ {
		h := C.int64_t(handles[i])
		C.MethodParamSetHandle(param, C.int32_t(i), h)
	}

	// data && dataSize
	for i := 0; i < len(dataList) && i < 16; i++ {
		data := dataList[i]
		inData := (*C.char)(unsafe.Pointer((*reflect.StringHeader)(unsafe.Pointer(&data)).Data))
		inDataLen := C.int32_t(len(data))

		C.MethodParamSetData(param, C.int32_t(i), inData, inDataLen)
	}

	// call
	var rc = C.call_C2Go_Method(param)

	for i := 0; i < len(instances); i++ {
		v := C.MethodParamGetInstance(param, C.int32_t(i))
		instances[i] = int64(v)
	}

	// free
	C.MethodParamDelete(param)

	return int(rc)
}
