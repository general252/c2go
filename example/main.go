package main

import (
	"log"
	"time"

	"github.com/general252/c2go"
)

func init() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
}

func main() {
	if err := c2go.LoadLibrary("c2go.so"); err != nil {
		log.Println(err)
		return
	}
	defer c2go.UnLoadLibrary()

	c2go.Init([]byte("init data"), func(method []byte, data []byte) {
		log.Println(string(method), string(data))
	})
	defer c2go.Finish()

	h := c2go.NewHandle(func(data []byte) {
		log.Println(string(data))
	})
	defer h.Delete()

	c2go.Command([]byte("this is command data"), h)

	time.Sleep(time.Second)
}
