package main

import (
	"log"
	"runtime/cgo"
	"time"

	"github.com/general252/c2go"
)

func init() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
}

func main() {
	if err := c2go.LoadLibrary("libcbd.dll"); err != nil {
		log.Println(err)
		return
	}

	c2go.Init()

	h := cgo.NewHandle(func(data []byte) {
		log.Println(string(data))
	})
	defer h.Delete()

	var instances = []int64{1, 2, 3}
	c2go.Method("my method hello", []cgo.Handle{h}, [][]byte{
		[]byte("aaa"),
		[]byte("bbb"),
		[]byte("ccc"),
		[]byte("ddd"),
	}, instances)

	log.Println(instances)

	time.Sleep(time.Second)
}
