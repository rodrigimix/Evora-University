main: bin/main.o bin/doubleLList.o bin/bigInt.o
	gcc -o $@ $^

bin/main.o: main.c | doubleLList.h bigInt.h  bin
	gcc -c -o $@ $^
bin/doubleLList.o: doubleLList.c | doubleLList.h bigInt.h bin
	gcc -c -o $@ $^
bin/bigInt.o: bigInt.c | doubleLList.h bigInt.h bin
	gcc -c -o $@ $^

bin:
	mkdir $@
clean:
	rm -rf queue bin