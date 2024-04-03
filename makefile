obj-m += nothing.o

all:
	make directories
	make src/nothing.c -o obj/nothing.o
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

directories:
	mkdir -p obj

.PHONY: clean
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

