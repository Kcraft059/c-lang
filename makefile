# Dirs
SRCDIR := ./src
HDRDIR := $(SRCDIR)/include
OBJDIR := ./obj
OUTDIR := ./out

# Compiler & flags
CC 		 := clang
CFLAGS := -Wall
LIBS   := -llgpio

# Targets
DEPS 	 := $(shell find $(SRCDIR) -type f -name '*.h')
SRC  	 := $(shell find $(SRCDIR) -type f -name '*.c')
OBJ  	 := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

TARGET := $(OUTDIR)/exec

# Rules
## Build obj
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

## Link objs
$(TARGET): $(OBJ)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

## Rule names
.PHONY: clean

all: $(TARGET)

asan: CFLAGS += -fsanitize=address
asan: all

clean:	
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)