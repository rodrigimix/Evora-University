list: bin/list.o
	gcc -o $@ $^
bin/list.o: list.c | fatal.h bin
	gcc -c -o $@ $^
bin:
	mkdir $@
clean:
	rm -rf list bin

