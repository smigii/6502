#!/usr/bin/env python3

code = bytearray([
	# Initialize B port to all output
	0xa9, 0xff,			#lda #$ff
	0x8d, 0x02, 0x60,	#sta $6002

	# Write 55 to B port
	0xa9, 0x55,			#lda #$5f
	0x8d, 0x00, 0x60,	#sta $6000

	# Write AA to B port
	0xa9, 0xaa,			#lda #$aa
	0x8d, 0x00, 0x60,	#sta $6000

	# Loop back up to write 55
	0x4c, 0x05, 0x80	#jmp 8005

	])

rom = code + bytearray([0xea] * (32768 - len(code)))

rom[0x7ffc] = 0x00
rom[0x7ffd] = 0x80

with open("rom.bin", "wb") as out_file:
	out_file.write(rom)
