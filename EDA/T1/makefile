main: bin/main.o bin/doubleLList.o
	gcc -o $@ $^

bin/main.o: main.c | doubleLList.h  bin
	gcc -c -o $@ $^
bin/doubleLList.o: doubleLList.c | doubleLList.h bin
	gcc -c -o $@ $^

bin:
	mkdir $@
clean:
	rm -rf queue bin