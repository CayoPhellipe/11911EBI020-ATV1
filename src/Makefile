CC = arm-none-eabi-gcc
CFLAGS = -Wall -c -mcpu=cortex-m4 -mthumb -O0 

all: startup.o main.o

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o