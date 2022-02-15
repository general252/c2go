

all:
	g++ -fPIC -shared c2go.cpp -o c2go.so
	go build -o c2go.exe main.go

debug:
	go build -o c2go.exe -x main.go