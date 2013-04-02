.PHONY: clean all check

ALL_SORTS_NAME=sorting-algorithms
COMMON_FLAGS=-Wall -Werror -std=c99

ALL_OBJECTS=$(ALL_SORTS_NAME)-unoptimized.s $(ALL_SORTS_NAME)-optimized.s \
	$(ALL_SORTS_NAME)-unoptimized $(ALL_SORTS_NAME)-optimized         \
	$(ALL_SORTS_NAME)-with-asserts

all:: $(ALL_OBJECTS) qsort-n

$(ALL_SORTS_NAME)-unoptimized.s : $(ALL_SORTS_NAME).c numbers.inc
	$(CC) $(COMMON_FLAGS) -O0 -S -DNDEBUG $< -o $@

$(ALL_SORTS_NAME)-optimized.s : $(ALL_SORTS_NAME).c numbers.inc
	$(CC) $(COMMON_FLAGS) -O3 -S -DNDEBUG $< -o $@

$(ALL_SORTS_NAME)-unoptimized : $(ALL_SORTS_NAME).c numbers.inc
	$(CC) $(COMMON_FLAGS) -O0 -DNDEBUG $< -o $@

$(ALL_SORTS_NAME)-optimized : $(ALL_SORTS_NAME).c numbers.inc
	$(CC) $(COMMON_FLAGS) -O3 -DNDEBUG $< -o $@

$(ALL_SORTS_NAME)-with-asserts : $(ALL_SORTS_NAME).c numbers.inc
	$(CC) $(COMMON_FLAGS) -O0 -g3 $< -o $@

qsort-n : qsort-n.c numbers.inc
	$(CC) $(COMMON_FLAGS) -O3 $< -o $@

clean::
	 rm -f $(ALL_OBJECTS)

check::
	./$(ALL_SORTS_NAME)-with-asserts --bubble-sort
	./$(ALL_SORTS_NAME)-with-asserts --insertion-sort
	./$(ALL_SORTS_NAME)-with-asserts --quick-sort
	./$(ALL_SORTS_NAME)-with-asserts --merge-sort
