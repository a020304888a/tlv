##
# Name: Makefile
# Purpose: TLV implmentation
# Auther: Aaron Chang
# Create: 2017.06.09
#

CC := gcc
CFLAGS := -Wall -O0 -std=gnu99
#CFLAGS += -Werror
CFLAGS += -fstack-protector
LIBS :=


TARGET := main

#C_SRCS := $(wildcard *.c)
#OBJS := ${C_SRCS:.c=.o}

OBJS := main.o tlv_oo.o

.SUFFIXS: .c .o

.PHONY: all
all: $(TARGET)
	@echo [OK]


# $@ => main, $^ => OBJS
$(TARGET): $(OBJS)
	@$(CC) -o $@ $^ $(CFLAGS) ${INC} $(LIBS)
	@echo [EX] $@
	@cp -v $@ ../$@
#	@cp $@ ../$@
#	@echo [CP] $@ -> ../$@

# $@ => .o, $^ => .c
%.o: %.c 
	@$(CC) -c -o $@ $^ $(CFLAGS) ${INC} ${LIBS}
	@echo [CC] $@

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf $(TARGET)
	@rm -rf ../$(TARGET)
	@echo [OK] clean finish

