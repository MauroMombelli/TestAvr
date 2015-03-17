#!/bin/bash

avr-gcc -std=c11 -mmcu=atmega32u4 -DF_CPU=16000000L -c test_bottone.c && \
avr-gcc -g -std=c11 -mmcu=atmega32u4 -DF_CPU=16000000L -o test_bottone.elf test_bottone.o && \
avr-objcopy -j .text -j .data -O ihex test_bottone.elf test_bottone.hex && \
avr-size -C --mcu=atmega32u4 test_bottone.elf 
