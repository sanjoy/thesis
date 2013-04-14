HEADERS=$(wildcard *.h *.hpp) numbers.inc
SOURCES=$(wildcard *.cpp)

TARGETS=$(patsubst %.cpp, %-energyopt, $(SOURCES))         \
	$(patsubst %.cpp, %-normalopt, $(SOURCES))         \
	$(patsubst %.cpp, %-timed-energyopt, $(SOURCES))   \
	$(patsubst %.cpp, %-timed-normalopt, $(SOURCES))   \
	$(patsubst %.cpp, %-stock, $(SOURCES))             \
	$(patsubst %.cpp, %-stock-debug, $(SOURCES))

all:: check-llvm-config $(TARGETS)

clean::
	rm -f *.s
	rm -f $(TARGETS)
	rm -f numbers.inc

LLVM_ROOT=$(shell $(llvm_config) --obj-root)
LLVM_OPT=$(LLVM_ROOT)/bin/opt
LLVM_DIS=$(LLVM_ROOT)/bin/llvm-dis
LLVM_LLC=$(LLVM_ROOT)/bin/llc

CXX_FLAGS=-Wall -Werror
COMMON_LLC_ARGS=-O3 -post-RA-scheduler
ENERGY_LLC_ARGS=-pre-RA-energy-opt -post-RA-energy-opt

check-llvm-config:
ifndef llvm_config
	$(error "llvm_config not defined!")
endif

numbers.inc:
	runhaskell Random.hs 1000 2000 > $@

time-measure.o: time-measure.cc
	clang++ -c $< -o $@

%-energyopt: %-opt.ll time-measure.o
	$(LLVM_LLC) $(COMMON_LLC_ARGS) $(ENERGY_LLC_ARGS) $< -o $@.s
	g++ $@.s -lm time-measure.o -o $@

%-normalopt: %-opt.ll time-measure.o
	$(LLVM_LLC) $(COMMON_LLC_ARGS) $< -o $@.s
	g++ $@.s -lm time-measure.o -o $@

%-opt.ll: %-opt.bc
	$(LLVM_DIS) $< -o $@

%-opt.bc: %.ll
	$(LLVM_OPT) -O3 $< -o $@

%-timed.ll: %.cpp $(HEADERS)
	clang++ $(CXX_FLAGS) -DNDEBUG -DMEASURE_TIME -emit-llvm -S -o $@ $<

%.ll: %.cpp $(HEADERS)
	clang++  $(CXX_FLAGS) -DNDEBUG -emit-llvm -S -o $@ $<

%-stock: %.cpp $(HEADERS)
	clang++ $(CXX_FLAGS) -O3 -DNDEBUG -lm $< -o $@

%-stock-debug: %.cpp $(HEADERS)
	clang++ $(CXX_FLAGS) -g3 -lm $< -o $@
