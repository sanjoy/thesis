.PHONY: clean all check

BASE_NAME=sorting-algorithms
COMMON_FLAGS=-Wall -Werror -std=c99

ALL_OBJECTS=$(BASE_NAME)-unoptimized.s $(BASE_NAME)-optimized.s \
	$(BASE_NAME)-unoptimized $(BASE_NAME)-optimized         \
	$(BASE_NAME)-with-asserts

all:: $(ALL_OBJECTS)

$(BASE_NAME)-unoptimized.s : $(BASE_NAME).c
	$(CC) $(COMMON_FLAGS) -O0 -S -DNDEBUG $< -o $@

$(BASE_NAME)-optimized.s : $(BASE_NAME).c
	$(CC) $(COMMON_FLAGS) -O3 -S -DNDEBUG $< -o $@

$(BASE_NAME)-unoptimized : $(BASE_NAME).c
	$(CC) $(COMMON_FLAGS) -O0 -DNDEBUG $< -o $@

$(BASE_NAME)-optimized : $(BASE_NAME).c
	$(CC) $(COMMON_FLAGS) -O3 -DNDEBUG $< -o $@

$(BASE_NAME)-with-asserts : $(BASE_NAME).c
	$(CC) $(COMMON_FLAGS) -O0 -g3 $< -o $@

clean::
	 rm -f $(ALL_OBJECTS)

check::
	./$(BASE_NAME)-with-asserts --bubble-sort
	./$(BASE_NAME)-with-asserts --insertion-sort
	./$(BASE_NAME)-with-asserts --quick-sort
	./$(BASE_NAME)-with-asserts --merge-sort
