queue: bin/queue.o bin/stackar.o
	gcc -o $@ $^

bin/queue.o: queue.c | queue.h fatal.h stackar.h bin
	gcc -c -o $@ $^

bin/stackar.o: stackar.c | fatal.h stackar.h bin
	gcc -c -o $@ $^
bin:
	mkdir $@
clean:
	rm -rf queue bin
