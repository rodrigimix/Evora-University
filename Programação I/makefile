othello: bin/othello.o bin/othello_func.o 
	gcc -o $@ $^ 
bin/othello.o: othello.c | othello_func.h bin
	gcc -c -o $@ $^
bin/othello_func.o: othello_func.c | othello_func.h bin
	gcc -c -o $@ $^
bin:
	mkdir $@
clean:
	rm -rf bin othello