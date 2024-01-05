# Set compiler
CC = gcc

# Set compiler flags
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces -I./resources

# Set library paths
LIBDIR = lib/

# Set library flags
LDFLAGS = -L$(LIBDIR)  -lraylib -lopengl32 -lgdi32 -lwinmm

# Set directories
SRCDIR = include
INCDIR = include
BUILDDIR = build
TARGET = ProjetAlgo

# Set source files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Set default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build files
.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.o 
	rm -f ProjetAlgo 
