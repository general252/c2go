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

	c2go.Init([]byte("init data"), func(data []byte) {
		log.Println(string(data))
	})
	defer c2go.Finish()

	c2go.Command([]byte("this is command data"), c2go.NewHandle(func(data []byte) {
		log.Println(string(data))
	}))

	time.Sleep(time.Second)
}
