all: cxx11 objc

cxx11: main.cpp
	clang++ -std=c++11 -stdlib=libc++ main.cpp -o maincpp

objc: main.m
	clang -framework Foundation main.m -o main -o mainobjc

