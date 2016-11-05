src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

LDFLAGS ?=
LDFLAGS += -lm
CPP ?= g++
STD ?= c++11
CPPFLAGS ?=
CPPFLAGS += -Wall -Werror -O3
CPPFLAGS += -std=$(STD)
CPPFLAGS += -I../include
EXEC = catch_test

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
	@./$(EXEC)