obj-m += nothing.o

directories:
	mkdir -p obj

all:
	make directories
	make src/nothing.c -o obj/nothing.o
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

