##
# Name: Makefile
# Purpose: TLV implmentation
# Auther: Aaron Chang
# Create: 2017.06.09
#

CC := gcc
CFLAGS := -Wall -O0
CFLAGS += -fstack-protector
LIBS :=


TARGET := main

OBJS := main.o tlv.o

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

