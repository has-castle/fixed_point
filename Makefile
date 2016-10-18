src = $(wildcard *.cpp)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

LDFLAGS = 
CFLAGS = -std=c++11
CPP = g++

fp_test: $(obj)
	$(CPP) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CPP) $(CFLAGS) -o $@ -c $<

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean
clean:
	rm -f $(obj) fp_test

.PHONY: cleandep
cleandep:
	rm -f $(dep)