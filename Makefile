obj-m += lfprng.o
KVERSION = $(shell uname -r)

all: lfprng.o tester

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

lfprng.o : lfprng.c
	make -C /usr/src/$(KVERSION) M=$(PWD) modules

tester : tester.c
	gcc -o tester -fopenmp tester.c
