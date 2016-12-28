src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

LDFLAGS ?=
LDFLAGS += -lm
CXX ?= g++
ifdef CXX_OVERRIDE
CXX = $(CXX_OVERRIDE)
endif
STD ?= c++11
CXXFLAGS ?=
CXXFLAGS += -Wall -Werror -O3
CXXFLAGS += -std=$(STD)
CXXFLAGS += -I../include
EXEC = catch_test

$(EXEC): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo Building $@ complete.

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) $(dep) $(EXEC)
	@echo Cleanup complete.

.PHONY: rebuild
rebuild: clean $(EXEC)

.PHONY: run
run: $(EXEC)
	@./$(EXEC)