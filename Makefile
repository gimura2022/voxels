DEBCFLAGS  = -g -O0
RELCFALGS  = -O3
PROJCFLAGS = -Wall -Wextra -Wpedantic -std=c2x

PROJLD = -lGLEW -lglfw -lGL -lm

PROJCPPFLAGS = -I include

CFLAGS   = $(PROJCFLAGS) 
CPPFLAGS = $(PROJCPPFLAGS)
LDFLAGS  = $(PROJLD)

CSOURCE = $(wildcard src/*.c)
OBJECTS = $(CSOURCE:.c=.o)

.PHONY: all
all: debug

.PHONY: debug
debug: CFLAGS += $(DEBCFLAGS)
debug: voxels.out

.PHONY: release
release: CFLAGS += $(RELCFALGS)
release: voxels.out

.PHONY: clean
clean:
	rm $(OBJECTS) voxels.out

voxels.out: $(OBJECTS)
	@$(CC) -o $@ $(OBJECTS) $(LDFLAGS) 
	@echo LD $@ $(OBJECTS)

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 
	@echo СС $@ $<
