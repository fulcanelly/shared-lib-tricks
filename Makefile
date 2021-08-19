CC = g++ 
SAN_ARG = -fsanitize=address

 
ALL_ARGC = $$(ruby -e "puts '${s}'.size")

ARGC = -rdynamic $(SAN_ARG)
make: test lib.so another.so prelib.so



lib.so:	lib.cc
	$(CC) $(ARGC) lib.cc -shared -fPIC -o lib.so 

another.so: another.cc
	$(CC) $(ARGC) another.cc -shared -fPIC -o another.so


test: test.cpp 
	$(CC) $(ARGC)  test.cpp  -ldl -o test -O3
	
prelib.so: prelib.cc
	$(CC) $(ARGC)    prelib.cc -shared -fPIC -o prelib.so

clean:
	rm test *.so  

