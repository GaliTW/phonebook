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

shuf_%:
	shuf -o ./dictionary/$*RAND.txt ./dictionary/$*.txt

run_many_%: phonebook_%
	@for i in $(shell seq 1 200); \
	do ./$< | grep sec | awk '{count++} count % 2 == 0 {print $$6 >> "append_$*.txt"} count % 2 == 1 {print $$6 >> "findName_$*.txt"}'; \
	done

dcache_%: stat_%
	@for i in $(shell seq 1 200); \
	do make stat_$* 2>&1 | grep L1-dcache-load-misses | awk '{gsub(",","",$$1); print $$1 >> "dcache_$*.txt"}'; \
	done

clean:
	$(RM) $(EXEC) *.o perf.*

style:
	@astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.[ch]
