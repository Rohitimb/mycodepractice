outfile:main.o sum.o mul.o
	@echo Generating executable files
	$(CC) main.o sum.o mul.o -o outfile
sum.o:sum.c
	$(CC) -c sum.c
mul.o:mul.c
	$(CC) -c mul.c
main.o:main.c header.h
	$(CC) -c main.c
clean: 
	@echo deleting all .o files
	$(RM) *.o
