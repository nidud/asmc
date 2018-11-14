; _CTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

	.data

_ctype label word
	dw	0			; -1
	dw	_CONTROL		; 00 (NUL)
	dw	_CONTROL		; 01 (SOH)
	dw	_CONTROL		; 02 (STX)
	dw	_CONTROL		; 03 (ETX)
	dw	_CONTROL		; 04 (EOT)
	dw	_CONTROL		; 05 (ENQ)
	dw	_CONTROL		; 06 (ACK)
	dw	_CONTROL		; 07 (BEL)
	dw	_CONTROL		; 08 (BS)
	dw	_SPACE + _CONTROL	; 09 (HT)
	dw	_SPACE + _CONTROL	; 0A (LF)
	dw	_SPACE + _CONTROL	; 0B (VT)
	dw	_SPACE + _CONTROL	; 0C (FF)
	dw	_SPACE + _CONTROL	; 0D (CR)
	dw	_CONTROL		; 0E (SI)
	dw	_CONTROL		; 0F (SO)
	dw	_CONTROL		; 10 (DLE)
	dw	_CONTROL		; 11 (DC1)
	dw	_CONTROL		; 12 (DC2)
	dw	_CONTROL		; 13 (DC3)
	dw	_CONTROL		; 14 (DC4)
	dw	_CONTROL		; 15 (NAK)
	dw	_CONTROL		; 16 (SYN)
	dw	_CONTROL		; 17 (ETB)
	dw	_CONTROL		; 18 (CAN)
	dw	_CONTROL		; 19 (EM)
	dw	_CONTROL		; 1A (SUB)
	dw	_CONTROL		; 1B (ESC)
	dw	_CONTROL		; 1C (FS)
	dw	_CONTROL		; 1D (GS)
	dw	_CONTROL		; 1E (RS)
	dw	_CONTROL		; 1F (US)
	dw	_SPACE + _BLANK		; 20 SPACE
	dw	_PUNCT			; 21 !
	dw	_PUNCT			; 22 "
	dw	_PUNCT			; 23 #
	dw	_PUNCT			; 24 $
	dw	_PUNCT			; 25 %
	dw	_PUNCT			; 26 &
	dw	_PUNCT			; 27 '
	dw	_PUNCT			; 28 (
	dw	_PUNCT			; 29 )
	dw	_PUNCT			; 2A *
	dw	_PUNCT			; 2B +
	dw	_PUNCT			; 2C ,
	dw	_PUNCT			; 2D -
	dw	_PUNCT			; 2E .
	dw	_PUNCT			; 2F /
	dw	_DIGIT + _HEX		; 30 0
	dw	_DIGIT + _HEX		; 31 1
	dw	_DIGIT + _HEX		; 32 2
	dw	_DIGIT + _HEX		; 33 3
	dw	_DIGIT + _HEX		; 34 4
	dw	_DIGIT + _HEX		; 35 5
	dw	_DIGIT + _HEX		; 36 6
	dw	_DIGIT + _HEX		; 37 7
	dw	_DIGIT + _HEX		; 38 8
	dw	_DIGIT + _HEX		; 39 9
	dw	_PUNCT			; 3A :
	dw	_PUNCT			; 3B ;
	dw	_PUNCT			; 3C <
	dw	_PUNCT			; 3D =
	dw	_PUNCT			; 3E >
	dw	_PUNCT			; 3F ?
	dw	_PUNCT			; 40 @
	dw	_UPPER + _HEX		; 41 A
	dw	_UPPER + _HEX		; 42 B
	dw	_UPPER + _HEX		; 43 C
	dw	_UPPER + _HEX		; 44 D
	dw	_UPPER + _HEX		; 45 E
	dw	_UPPER + _HEX		; 46 F
	dw	_UPPER			; 47 G
	dw	_UPPER			; 48 H
	dw	_UPPER			; 49 I
	dw	_UPPER			; 4A J
	dw	_UPPER			; 4B K
	dw	_UPPER			; 4C L
	dw	_UPPER			; 4D M
	dw	_UPPER			; 4E N
	dw	_UPPER			; 4F O
	dw	_UPPER			; 50 P
	dw	_UPPER			; 51 Q
	dw	_UPPER			; 52 R
	dw	_UPPER			; 53 S
	dw	_UPPER			; 54 T
	dw	_UPPER			; 55 U
	dw	_UPPER			; 56 V
	dw	_UPPER			; 57 W
	dw	_UPPER			; 58 X
	dw	_UPPER			; 59 Y
	dw	_UPPER			; 5A Z
	dw	_PUNCT			; 5B [
	dw	_PUNCT			; 5C \
	dw	_PUNCT			; 5D ]
	dw	_PUNCT			; 5E ^
	dw	_PUNCT			; 5F _
	dw	_PUNCT			; 60 `
	dw	_LOWER + _HEX		; 61 a
	dw	_LOWER + _HEX		; 62 b
	dw	_LOWER + _HEX		; 63 c
	dw	_LOWER + _HEX		; 64 d
	dw	_LOWER + _HEX		; 65 e
	dw	_LOWER + _HEX		; 66 f
	dw	_LOWER			; 67 g
	dw	_LOWER			; 68 h
	dw	_LOWER			; 69 i
	dw	_LOWER			; 6A j
	dw	_LOWER			; 6B k
	dw	_LOWER			; 6C l
	dw	_LOWER			; 6D m
	dw	_LOWER			; 6E n
	dw	_LOWER			; 6F o
	dw	_LOWER			; 70 p
	dw	_LOWER			; 71 q
	dw	_LOWER			; 72 r
	dw	_LOWER			; 73 s
	dw	_LOWER			; 74 t
	dw	_LOWER			; 75 u
	dw	_LOWER			; 76 v
	dw	_LOWER			; 77 w
	dw	_LOWER			; 78 x
	dw	_LOWER			; 79 y
	dw	_LOWER			; 7A z
	dw	_PUNCT			; 7B {
	dw	_PUNCT			; 7C |
	dw	_PUNCT			; 7D }
	dw	_PUNCT			; 7E ~
	dw	_CONTROL		; 7F (DEL)

	; and the rest are 0...

	dw	257*2 - ($ - offset _ctype) dup(0)

_pctype	 LPWORD _ctype+2 ; pointer to table for char's
_pwctype LPWORD _ctype+2 ; pointer to table for wchar_t's

	END

