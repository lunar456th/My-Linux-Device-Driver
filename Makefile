NAME := mydev

obj-m := $(NAME).o
#ccflags-y := -DIS_DEV_MISC

VERSION := $(shell uname -r)
LOCAL := $(shell pwd)

all:
	make -C /lib/modules/$(VERSION)/build M=$(LOCAL) modules

test:
	gcc -o test_$(NAME) test_$(NAME).c

testclean:
	rm test_$(NAME)

clean:
	rm -f $(NAME).o
	rm -f $(NAME).ko
	rm -f $(NAME).mod.*
	rm -f .$(NAME).ko.cmd
	rm -f .$(NAME).mod.o.cmd
	rm -f .$(NAME).o.cmd
	rm -fr .tmp_versions
	rm -f modules.order
	rm -f Module.symvers

