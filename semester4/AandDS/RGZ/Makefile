.PHONY: app
app: build
	./app

build: clean
	clang++ main.cpp -O0 -o app

clean:
	rm -f app
