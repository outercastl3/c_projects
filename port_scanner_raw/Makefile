CC = clang
CFLAGS = -Wall -Wextra
TARGET = scanner_raw

$(TARGET): main.o scanner_logic.o scanner_function.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o scanner_logic.o scanner_function.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

scanner_logic.o: scanner_logic.c scanner_logic.h
	$(CC) $(CFLAGS) -c scanner_logic.c

scanner_function.o: scanner_function.c scanner_function.h
	$(CC) $(CFLAGS) -c scanner_function.c

clean:
	rm -rf *.o $(TARGET)
