CC = gcc
CFLAGS = -Wall -O2

PROG = main
FONTES = main.c lib_ppm.c lib_richard_cross.c lib_sobel.c lib_threshold.c lib_grey.c
OBJETOS = $(FONTES: .c=.o)

$(PROG): $(OBJETOS)
	gcc $(CFLAGS) $(OBJETOS) -o $@

clean:
	-@ rm -f $(OBJETOS) $(PROG)

# all: main

# main: main.o lib_ppm.o lib_richard_cross.o lib_sobel.o lib_threshold.o lib_grey.o
# 	$(CC) $(CFLAGS) -o main main.o lib_ppm.o lib_richard_cross.o lib_sobel.o lib_threshold.o lib_grey.o

# main.o: main.c
# 	$(CC) $(CFLAGS) -c main.c

# lib_ppm.o: lib_ppm.c
# 	$(CC) $(CFLAGS) -c lib_ppm.c

# lib_richard_cross.o: lib_richard_cross.c
# 	$(CC) $(CFLAGS) -c lib_richard_cross.c

# lib_sobel.o: lib_sobel.c
# 	$(CC) $(CFLAGS) -c lib_sobel.c

# lib_threshold.o: lib_threshold.c
# 	$(CC) $(CFLAGS) -c lib_threshold.c

# lib_grey.o: lib_grey.c
# 	$(CC) $(CFLAGS) -c lib_grey.c

# clean:
# 	rm -f *.o main *.ppm
