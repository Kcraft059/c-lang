TARGET = rpireg

SRCDIR := $(PWD)/src
SRC	:= $(shell find $(SRCDIR) -type f -name '*.c')
OBJ	:= $(patsubst $(PWD)/%.c, %.o, $(SRC))

obj-m += $(TARGET).o
$(TARGET)-objs := $(OBJ)

all:
#MODCOMP
	make -C /nix/store/kyg2zanannj4xvv042b0220js8pw0af7-linux_rpi-bcm2712-6.12.34-stable_20250702-dev/lib/modules/6.12.34/build M=$(PWD) modules
clean:
#MODCLEAN
	make -C /nix/store/kyg2zanannj4xvv042b0220js8pw0af7-linux_rpi-bcm2712-6.12.34-stable_20250702-dev/lib/modules/6.12.34/build M=$(PWD) clean
