src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)

LDFLAGS = -lm
CPPFLAGS = -std=c++11 -Wall -Werror
EXEC = fp_test
CPP = g++

$(EXEC): $(obj)
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

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

.PHONY: cleandep
cleandep:
	rm -f $(dep)

.PHONY: run
run:
	@./$(EXEC)