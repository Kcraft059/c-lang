obj-m += testkernelobj.o

all:
	make -C /nix/store/2x9v98c9ldzrzjy8rhki0w8gyxrbgbnb-linux-6.12.63-dev/lib/modules/6.12.63/build M=$(PWD) modules

clean:
	make -C /nix/store/2x9v98c9ldzrzjy8rhki0w8gyxrbgbnb-linux-6.12.63-dev/lib/modules/6.12.63/build M=$(PWD) clean
	