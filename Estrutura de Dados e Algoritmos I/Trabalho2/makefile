main: bin/main.o bin/doubleLList.o bin/find_letter2.o bin/hash.o
	gcc -o $@ $^

bin/main.o: main.c | doubleLList.h find_letter.h hash.h bin
	gcc -c -o $@ $^
bin/doubleLList.o: doubleLList.c | doubleLList.h find_letter.h bin
	gcc -c -o $@ $^
bin/find_letter2.o: find_letter.c | doubleLList.h find_letter.h hash.h bin
	gcc -c -o $@ $^
bin/hash.o: hash.c | hash.h bin
	gcc -c -o $@ $^

bin:
	mkdir $@
clean:
	rm -rf queue bin