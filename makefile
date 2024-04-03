OBJ_DIR=obj

obj-m += nothing.o

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p modules

all: directories program

program:
	make -C /src/nothing.c -o nothing.o
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
.PHONY: clean
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


