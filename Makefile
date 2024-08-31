clean:
	rm -f cipher
all: cipher

cipher: cipher.cc
	g++ -o cipher cipher.cc -I.
