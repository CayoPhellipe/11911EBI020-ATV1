CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb -O0 # -O0 retira as optimizações automáticas do compilador

all: startup.o main.o

main.o: main.c
	$(CC) $(CFLAGS) $< -o $@

startup.o: startup.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o