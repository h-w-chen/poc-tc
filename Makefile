INC=-I/home/howell/work/linux/include -I/home/howell/work/linux/tools/lib -I/usr/include/x86_64-linux-gnu 

.PHONY: clean all
all: hwtc.o

hwtc.o: hwtc.c
	clang -O2 -g -Wall -Werror -target bpf ${INC} -c $< -o $@ 

clean:
	rm -f hwtc.o

