CC = gcc
CCFLAGS = -c -Wall --std=c99

LINKER = gcc
LINKERFLAGS = -Wall --std=c99 -lm -o

PROG = target

SRCDIR = src
BINARYDIR = bin

OBJS = $(patsubst $(SRCDIR)/%.c, $(BINARYDIR)/%.o, $(wildcard $(SRCDIR)/*.c))

$(BINARYDIR):
	mkdir $(BINARYDIR)

$(PROG): $(OBJS)
	$(LINKER) $(OBJS) $(LINKERFLAGS) $(PROG)

$(BINARYDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) $< -o $@

all: $(BINARYDIR) $(PROG)

clean:
	rm -rf *.o $(PROG) $(BINARYDIR)

.PHONY: all clean
.DEFAULT_GOAL = all
