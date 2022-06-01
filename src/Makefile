PROG = blinky

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc #Compilador do linker script
CP = arm-none-eabi-objcopy
CFLAGS = -Wall -c -mcpu=cortex-m4 -mthumb -O0 
LFLAGS = -nostdlib -T stm32f411-rom.ld #Flags do ls e linker script file

#Modificações para gera o blinky.elf e imagem binária para ser gravada no microcontrolador

all: $(PROG).elf

blink.elf: main.o startup.o
	$(LD) $(LFLAGS) $^ -o $@
	$(CP) $(PROG).elf -O binary $(PROG).bin

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.elf