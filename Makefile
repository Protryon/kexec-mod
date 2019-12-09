CC := gcc-4.8
ARCH := i386
obj-m += kexec.o
kexec-y += hardcode.o
kexec-y += crash.o
kexec-y += machine_kexec_32.o
kexec-y += relocate_kernel_32.o
kexec-y += kexec_ext.o

all:
	make CC=gcc-4.8 ARCH=i386 -C ../linux M=$(PWD) modules

clean:
	make CC=gcc-4.8 ARCH=i386 -C ../linux M=$(PWD) clean
