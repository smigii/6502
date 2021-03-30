; NEED BLANK SPACE AT BEGINNING OF LINE

	.org $8000		; Origin at addr 8000

reset:
	lda #$ff		; # means load the value $ff, no # would mean load value @ $00ff
	sta $6002		; Store a at addr 6002

	lda #$50
	sta $6000

loop:
	ror				; Rotate bits right
	sta $6000

	jmp loop

	.org $fffc
	.word reset
	.word $0000
