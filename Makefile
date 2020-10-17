INC=-I/home/howell/work/linux/include -I/home/howell/work/linux/tools/perf/include

.PHONY: clean all
all: hwtc.o

hwtc.o: hwtc.c
	clang -O2 -g -Wall -target bpf ${INC} -c $< -o $@ 

clean:
	rm -f hwtc.o

