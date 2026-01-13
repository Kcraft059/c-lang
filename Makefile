TARGET := build/rpireg

SRCDIR := $(PWD)/src
SRC		 := $(shell find $(SRCDIR) -type f -name '*.c')
OBJ		 := $(patsubst $(PWD)/%.c, %.o, $(SRC))
FLAGS  := -I$(SRCDIR)/include

obj-m += $(TARGET).o
$(TARGET)-objs := $(OBJ)

#MODCOMPPATH
COMPPATH = /nix/store/kyg2zanannj4xvv042b0220js8pw0af7-linux_rpi-bcm2712-6.12.34-stable_20250702-dev/lib/modules/6.12.34/build

all:
	@mkdir -p $(dir $(TARGET))
	make -C $(COMPPATH) M=$(PWD) "KCFLAGS=$(FLAGS)" modules
clean:
	make -C $(COMPPATH) M=$(PWD) clean
