.PHONY: app
app: build
	./app

build: clean
	clang++ -std=c++17 main.cpp -O0 -o app

clean:
	rm -f app
