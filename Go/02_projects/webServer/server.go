package main

import (
	"fmt"
	"net/http"
)


func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", handleRoot)
	mux.HandleFunc("/test", handleTest)

	fmt.Println("Server listening to 8080")
	http.ListenAndServe(":8080", mux)
}

func handleRoot(
	w http.ResponseWriter,
	r *http.Request,
) {
	http.ServeFile(w, r, "index.html")
}


func handleTest(
	w http.ResponseWriter,
	r *http.Request,
) {
	fmt.Fprintf(w, "Hello my fellow testers")
	http.StatusBadGateway(x);
}

