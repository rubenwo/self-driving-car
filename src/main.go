package main

import (
	"net/http"
	"log"
	"io"
)

func main(){
	for{
	resp, err := http.Get("https://homeautomation.rubenwoldhuis.nl/")
	if err != nil{
		log.Fatal(err)
	}
	_,_=io.ReadAll(resp.Body)
	resp.Body.Close()
}
	// log.Println(string(b))
}