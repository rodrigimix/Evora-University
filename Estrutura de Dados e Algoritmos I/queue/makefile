queue: bin/queue.o
	gcc -o $@ $^
bin/queue.o: queue.c | queue.h fatal.h bin
	gcc -c -o $@ $^
bin:
	mkdir $@
clean:
	rm -rf queue bin