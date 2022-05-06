main: bin/main.o bin/abp.o 
	gcc -o $@ $^
bin/main.o: main.c | abp.h fatal.h bin
	gcc -c -o $@ $^

bin/abp.o: abp.c | abp.h fatal.h bin
	gcc -c -o $@ $^
bin:
	mkdir $@
clean:
	rm -rf abp bin