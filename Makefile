obj-m += lfprng.o
KVERSION = $(shell uname -r)

all:
	make -C /usr/src/$(KVERSION) M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

