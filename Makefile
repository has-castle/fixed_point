src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

LDFLAGS ?=
LDFLAGS += -lm
CPP ?= g++
STD ?= c++11
CPPFLAGS ?=
CPPFLAGS += -Wall -Werror -O3 -g
CPPFLAGS += -std=$(STD)
CPPFLAGS += -Iinclude
EXEC = fp_demo

$(EXEC): $(obj)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Building $@ complete.

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -o $@ -c $<

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.cpp
	$(CPP) $(CPPFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(dep) $(EXEC)
	@echo Cleanup complete.

.PHONY: rebuild
rebuild: clean $(EXEC)

.PHONY: run
run: $(EXEC)
	@echo Starting ./$(EXEC)
	@echo ===============================
	@./$(EXEC)

.PHONY: test test_clean test_rebuild test_run
test:
	@cd tests; make

test_clean:
	@cd tests; make clean

test_rebuild:
	@cd tests; make rebuild

test_run:
	@cd tests; make run

all: test $(EXEC)

.PHONY: all_clean all_rebuild all_run
all_clean: test_clean clean

all_rebuild: test_rebuild rebuild

all_run: test_run run
