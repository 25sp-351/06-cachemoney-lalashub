CC = gcc
CFLAGS = -Wall -g
OBJFILES = cachemoney.o
TARGET = cachemoney

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(OBJFILES) -o $(TARGET)

cachemoney.o: cachemoney.c
	$(CC) $(CFLAGS) -c cachemoney.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJFILES) $(TARGET)

.PHONY: all clean run
