
CFLAGS = -O0 -Wall -Werror -g

# Control the build verbosity                                                   
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif
all: test
test : test.c
	gcc -Wall test.c -o test -lm

.PHONY: all clean


				

 

plot: output.txt 
	gnuplot scripts/runtime.gp
	eog statistic.png
		

calculate: test.c
	$(CC) $(CFLAGS_common) $^ -o $@

 
clean:
	$(RM) $(TESTS) $(OBJS)
	$(RM) $(deps)
	rm -f  output.txt 

-include $(deps)
