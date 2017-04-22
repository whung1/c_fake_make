CC=gcc
CFLAGS= -Wall -g
DEPS = main.h
OBJ = main.o file_handle.o fake.o
TARGET = fake

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

cat: cat.o
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.o $(TARGET) 
