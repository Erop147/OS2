

;
; +-------------------------------------------------------------------------+
; |   This file	has been generated by The Interactive Disassembler (IDA)    |
; |	   Copyright (c) 2009 by Hex-Rays, <support@hex-rays.com>	    |
; |			 License info: E7-EC05-8A45-34			    |
; |				 Licensed User				    |
; +-------------------------------------------------------------------------+
;
; Input	MD5   :	ADCBF5BCCD613B34F0779526E804EC3E

; ---------------------------------------------------------------------------
; File Name   :	D:\cygwin\home\Erop\OS\boot.bin
; Format      :	Binary file
; Base Address:	0000h Range: 0000h - 0200h Loaded length: 0200h

		.686p
		.mmx
		.model flat

; ===========================================================================

; Segment type:	Pure code
seg000		segment	byte public 'CODE' use16
		assume cs:seg000
		assume es:nothing, ss:nothing, ds:nothing, fs:nothing, gs:nothing

loc_0:
		cli
		xor	ax, ax
		mov	ss, ax
		mov	sp, 7BECh
		mov	bp, sp
		mov	ds, ax
		mov	si, 7C00h
		mov	es, ax
		mov	di, 600h
		mov	cx, 100h
		cld
		rep movsw
		jmp	far ptr	0:61Fh
; ---------------------------------------------------------------------------
		xor	al, al
		cmp	dl, al
		jnz	short loc_27
		mov	dl, 80h	; '�'

loc_27:					; CODE XREF: seg000:0023j
		mov	[bp+12h], dl
		mov	si, 790h
		mov	di, 720h
		call	di
		mov	si, 7BEh
		mov	cx, 4
		mov	ah, 80h	; '�'
		xor	al, al

loc_3C:					; CODE XREF: seg000:loc_4Cj
		mov	bl, [si+0]
		cmp	ah, bl		; DATA XREF: seg000:012Ar
		jz	short loc_56
		cmp	al, bl
		jnz	short loc_66
		add	si, 10h
		dec	cx

loc_4C:					; DATA XREF: seg000:0076r seg000:00BEr ...
		jnz	short loc_3C
		mov	si, 733h
		mov	di, 6FDh
		call	di

loc_56:					; CODE XREF: seg000:0041j
		mov	di, si

loc_58:					; CODE XREF: seg000:0064j
					; DATA XREF: seg000:010Cr
		add	si, 10h
		dec	cx
		jz	short loc_6E
		mov	bl, [si+0]
		cmp	ah, bl
		jnz	short loc_58

loc_66:					; CODE XREF: seg000:0045j
		mov	si, 74Ah
		mov	di, 6FDh
		call	di

loc_6E:					; CODE XREF: seg000:005Dj
		mov	ah, 41h	; 'A'
		mov	bx, 55AAh
		mov	dl, [bp+12h]
		int	13h		; DISK -
		jb	short loc_CA
		cmp	bx, 0AA55h
		jnz	short loc_CA
		and	cx, 1
		jz	short loc_CA
		mov	byte ptr [bp+0], 10h
		mov	byte ptr [bp+1], 0
		mov	byte ptr [bp+2], 1
		mov	byte ptr [bp+3], 0
		mov	word ptr [bp+4], 7C00h
		mov	word ptr [bp+6], 0
		mov	ax, [di+8]
		mov	[bp+8],	ax
		mov	ax, [di+0Ah]
		mov	[bp+0Ah], ax
		mov	word ptr [bp+0Ch], 0
		mov	word ptr [bp+0Eh], 0
		mov	si, bp
		mov	ah, 42h	; 'B'
		int	13h		; DISK -
		jnb	short loc_E6
		mov	si, 756h
		mov	di, 6FDh
		call	di

loc_CA:					; CODE XREF: seg000:0078j seg000:007Ej ...
		mov	dh, [di+1]
		mov	cx, [di+2]
		mov	ax, 201h
		mov	dl, [bp+12h]
		mov	bx, 7C00h
		int	13h		; DISK - READ SECTORS INTO MEMORY
					; AL = number of sectors to read, CH = track, CL = sector
					; DH = head, DL	= drive, ES:BX -> buffer to fill
					; Return: CF set on error, AH =	status,	AL = number of sectors read
		jnb	short loc_E6
		mov	si, 756h
		mov	di, 6FDh
		call	di

loc_E6:					; CODE XREF: seg000:00C0j seg000:00DCj
		mov	bx, 7C00h
		mov	ax, [bx+1FEh]
		cmp	ax, 0AA55h
		jnz	short loc_FA
		mov	si, di
		jmp	far ptr	0:7C00h
; ---------------------------------------------------------------------------

loc_FA:					; CODE XREF: seg000:00F1j
		mov	si, 760h
		mov	di, 720h
		call	di
		mov	si, 76Ch
		mov	di, 720h
		call	di
		xor	ax, ax
		int	16h		; KEYBOARD - READ CHAR FROM BUFFER, WAIT IF EMPTY
					; Return: AH = scan code, AL = character
		xor	bx, bx
		mov	es, bx
		mov	bx, 472h
		mov	ax, 1234h
		mov	es:[bx], ax
		jmp	far ptr	0FFFFh:0
; ---------------------------------------------------------------------------
		pusha
		xor	bx, bx
		lodsb
		or	al, al
		jz	short loc_131

loc_128:				; CODE XREF: seg000:012Fj
		mov	ah, 0Eh
		int	10h		; - VIDEO - WRITE CHARACTER AND	ADVANCE	CURSOR (TTY WRITE)
					; AL = character, BH = display page (alpha modes)
					; BL = foreground color	(graphics modes)
		lodsb
		or	al, al
		jnz	short loc_128

loc_131:				; CODE XREF: seg000:0126j
		popa
		retn
; ---------------------------------------------------------------------------
		dec	si
		outsw
		and	[bx+di+63h], ah
		jz	short near ptr unk_1A3
		jbe	short near ptr unk_1A1
		and	[di+6Eh], ah
		jz	short near ptr unk_1B3
		jns	short near ptr loc_162+1
		imul	bp, [bp+20h], 424Dh
		push	dx
		add	[bx+di+6Eh], cl
		jbe	short near ptr unk_1AF
		insb
		imul	sp, [si+20h], 424Dh
		push	dx
		add	[bx+di+2Fh], cl
		dec	di
		and	[di+72h], ah
		jb	short near ptr unk_1CD
		jb	short $+2
		dec	cx
		outsb

loc_162:				; CODE XREF: seg000:0141j
		jbe	short near ptr loc_1C4+1
		insb
		imul	sp, [si+20h], 4250h
		push	bx
		add	[di], cl
		or	dl, [bx+si+72h]
		db	65h
		jnb	short near ptr unk_1E6
		and	[bx+di+6Ch], ah
		insw
		outsw
		jnb	short near ptr unk_1EE
		and	[bx+di+6Eh], ah
		jns	short near ptr unk_19F
		imul	sp, [di+79h], 20h
		jz	short near ptr unk_1F4
		and	[bp+si+65h], dh
		bound	bp, [bx+6Fh]
		jz	short near ptr unk_1BB
		db	2Eh
		add	cs:[di+42h], cl
		push	dx
		db	2Eh, 2Eh
		add	cs:[bx+si], al
; ---------------------------------------------------------------------------
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
unk_19F		db    0			; CODE XREF: seg000:017Dj
		db    0
unk_1A1		db    0			; CODE XREF: seg000:013Aj
		db    0
unk_1A3		db    0			; CODE XREF: seg000:0138j
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
unk_1AF		db    0			; CODE XREF: seg000:014Cj
		db    0
		db    0
		db    0
unk_1B3		db    0			; CODE XREF: seg000:013Fj
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
unk_1BB		db    0			; CODE XREF: seg000:018Bj
		db    0
		db    0
; ---------------------------------------------------------------------------
		add	byte ptr [bx+di], 1
		add	[bx+di], bh
		aas

loc_1C4:				; CODE XREF: seg000:loc_162j
		mov	di, 3F07h
; ---------------------------------------------------------------------------
		db    0
		db    0
; ---------------------------------------------------------------------------
		add	cl, al
		std
		pop	ds
; ---------------------------------------------------------------------------
unk_1CD		db    0			; CODE XREF: seg000:015Cj
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
unk_1E6		db    0			; CODE XREF: seg000:0170j
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
unk_1EE		db    0			; CODE XREF: seg000:0178j
		db    0
		db    0
		db    0
		db    0
		db    0
unk_1F4		db    0			; CODE XREF: seg000:0183j
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db  55h	; U
		db 0AAh	; �
seg000		ends


		end

