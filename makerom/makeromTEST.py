#!/usr/bin/env python3

rom = bytearray([0xFF] * 32768)

for x in range(int(32768 / 2)):
	rom[x*2] = 0x00

with open("romTEST.bin", "wb") as out_file:
	out_file.write(rom)
