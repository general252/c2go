package c2go

import (
	"math"
	"sync"
	"sync/atomic"
)

type (
	Handle     int32
	HandleFunc func(data []byte)
)

var (
	handles   = sync.Map{} // map[Handle]interface{}
	handleIdx int32        // atomic
)

func NewHandle(v HandleFunc) Handle {
	if handleIdx > math.MaxInt16 {
		handleIdx = 0
	}

	var h int32
	for {
		_, ok := handles.Load(handleIdx)
		if !ok {
			break
		}

		h = atomic.AddInt32(&handleIdx, 1)
	}

	handles.Store(h, v)
	return Handle(h)
}

// Value returns the associated Go value for a valid handle.
//
// The method panics if the handle is invalid.
func (h Handle) Value() (HandleFunc, bool) {
	v, ok := handles.Load(int32(h))
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
	_, ok := handles.LoadAndDelete(int32(h))
	if !ok {
	}
}
