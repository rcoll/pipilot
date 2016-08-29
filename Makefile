CC = gcc

CFLAGS = -lm -lwiringPi

TARGET = pipilot

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)