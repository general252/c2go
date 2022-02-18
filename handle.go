package c2go

import (
	"math"
	"sync"
	"sync/atomic"
)

type (
	Handle     uintptr
	HandleFunc func(data []byte)
)

var (
	handles           = sync.Map{} // map[Handle]interface{}
	handleIdx uintptr = 0
)

func NewHandle(v HandleFunc) Handle {
	if uint64(handleIdx) >= uint64(math.MaxUint32) {
		handleIdx = 0
	}

	var h uintptr
	for {
		h = atomic.AddUintptr(&handleIdx, 1)

		_, ok := handles.Load(h)
		if !ok {
			break
		}
	}

	handles.Store(h, v)
	return Handle(h)
}

// Value returns the associated Go value for a valid handle.
//
// The method panics if the handle is invalid.
func (h Handle) Value() (HandleFunc, bool) {
	v, ok := handles.Load(uintptr(h))
	if !ok || nil == v {
		return nil, false
	}

	f, ok := v.(HandleFunc)
	if !ok || nil == f {
		return nil, false
	}

	return f, true
}

// Delete invalidates a handle. This method should only be called once
// the program no longer needs to pass the handle to C and the C code
// no longer has a copy of the handle value.
//
// The method panics if the handle is invalid.
func (h Handle) Delete() {
	_, ok := handles.LoadAndDelete(uintptr(h))
	if !ok {
	}
}
