CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99

SRCS_common = main.c
SRCS_FILES = $(wildcard *.c)
EXEC = $(basename $(notdir $(filter-out $(SRCS_common), $(SRCS_FILES))))
all: $(EXEC)

SRCS_common = main.c

phonebook_%: $(SRCS_common) phonebook_%.c phonebook_%.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run_%: phonebook_%
	watch -d -t ./$<

clean:
	$(RM) $(EXEC) *.o perf.*
