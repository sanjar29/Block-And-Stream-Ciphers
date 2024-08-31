all: cipher

cipher: cipher.cc
	g++ -o cipher cipher.cc -I.

clean:
	rm -f cipher
