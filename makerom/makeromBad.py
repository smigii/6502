#!/usr/bin/env python3

rom = bytearray([0xAF] * 32768)

for x in range(int(32768 / 2)):
	rom[x*2] = 0x20

rom[2000] = 0xAA

with open("romFault.bin", "wb") as out_file:
	out_file.write(rom)
