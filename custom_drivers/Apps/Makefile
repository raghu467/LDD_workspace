CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = file_opss.o  

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

host: $(OBJ)
	$(CC) -o File_opps.elf $^ $(CFLAGS)
