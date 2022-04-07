ex3: bin/ex3.o bin/stackar.o
	gcc -o $@ $^
bin/ex3.o: ex3.c | fatal.h stackar.h bin
	gcc -c -o $@ $^
bin/stackar.o: stackar.c | fatal.h stackar.h bin
	gcc -c -o $@ $^
bin:
	mkdir $@
clean:
	rm -rf ex3 bin