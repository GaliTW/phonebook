CC ?= gcc
CFLAGS_common ?= -O0 -Wall -std=gnu99

SRCS_common = main.c
SRCS_FILES = $(wildcard *.c)
EXEC = $(basename $(notdir $(filter-out $(SRCS_common), $(SRCS_FILES))))
all: $(EXEC)

cache_ptr:
	@sudo sh -c "echo 0 > /proc/sys/kernel/kptr_restrict"

clear_cache:
	@echo "echo 1 > /proc/sys/vm/drop_caches" | sudo sh

phonebook_%: $(SRCS_common) phonebook_%.c phonebook_%.h
	$(CC) $(CFLAGS_common) -DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run_%: phonebook_%
	watch -d -t ./$<

stat_%: phonebook_% cache_ptr clear_cache
	@perf stat \
	-e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses \
	./$<

record_%: phonebook_% cache_ptr clear_cache
	@perf record -F 15000 \
	-e cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-store-misses,L1-dcache-prefetch-misses,L1-icache-load-misses \
	./$< && perf report

clean:
	$(RM) $(EXEC) *.o perf.*
