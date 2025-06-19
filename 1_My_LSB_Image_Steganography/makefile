a.out: main.o encode.o decode.o
	gcc -o a.out main.o encode.o decode.o

main.o: main.c encode.h decode.h types.h
	gcc -c main.c

encode.o: encode.c encode.h types.h
	gcc -c encode.c

decode.o: decode.c decode.h types.h
	gcc -c decode.c

clean:
	rm *.o *.out
	