include ltype.inc

	public	__ltype

	.data

__ltype db	0			; -1
	db	0			; 00 (NUL)
	db	0			; 01 (SOH)
	db	0			; 02 (STX)
	db	0			; 03 (ETX)
	db	0			; 04 (EOT)
	db	0			; 05 (ENQ)
	db	0			; 06 (ACK)
	db	0			; 07 (BEL)
	db	0			; 08 (BS)
	db	_SPACE			; 09 (HT)
	db	_SPACE			; 0A (LF)
	db	_SPACE			; 0B (VT)
	db	_SPACE			; 0C (FF)
	db	_SPACE			; 0D (CR)
	db	0			; 0E (SI)
	db	0			; 0F (SO)
	db	0			; 10 (DLE)
	db	0			; 11 (DC1)
	db	0			; 12 (DC2)
	db	0			; 13 (DC3)
	db	0			; 14 (DC4)
	db	0			; 15 (NAK)
	db	0			; 16 (SYN)
	db	0			; 17 (ETB)
	db	0			; 18 (CAN)
	db	0			; 19 (EM)
	db	0			; 1A (SUB)
	db	0			; 1B (ESC)
	db	0			; 1C (FS)
	db	0			; 1D (GS)
	db	0			; 1E (RS)
	db	0			; 1F (US)
	db	_SPACE			; 20 SPACE
	db	0			; 21 !
	db	0			; 22 "
	db	0			; 23 #
	db	_LABEL			; 24 $
	db	0			; 25 %
	db	0			; 26 &
	db	0			; 27 '
	db	0			; 28 (
	db	0			; 29 )
	db	0			; 2A *
	db	0			; 2B +
	db	0			; 2C ,
	db	0			; 2D -
	db	_DOT			; 2E .
	db	0			; 2F /
	db	_DIGIT + _HEX		; 30 0
	db	_DIGIT + _HEX		; 31 1
	db	_DIGIT + _HEX		; 32 2
	db	_DIGIT + _HEX		; 33 3
	db	_DIGIT + _HEX		; 34 4
	db	_DIGIT + _HEX		; 35 5
	db	_DIGIT + _HEX		; 36 6
	db	_DIGIT + _HEX		; 37 7
	db	_DIGIT + _HEX		; 38 8
	db	_DIGIT + _HEX		; 39 9
	db	0			; 3A :
	db	0			; 3B ;
	db	0			; 3C <
	db	0			; 3D =
	db	0			; 3E >
	db	_LABEL			; 3F ?
	db	_LABEL			; 40 @
	db	_LABEL + _HEX		; 41 A
	db	_LABEL + _HEX		; 42 B
	db	_LABEL + _HEX		; 43 C
	db	_LABEL + _HEX		; 44 D
	db	_LABEL + _HEX		; 45 E
	db	_LABEL + _HEX		; 46 F
	db	_LABEL			; 47 G
	db	_LABEL			; 48 H
	db	_LABEL			; 49 I
	db	_LABEL			; 4A J
	db	_LABEL			; 4B K
	db	_LABEL			; 4C L
	db	_LABEL			; 4D M
	db	_LABEL			; 4E N
	db	_LABEL			; 4F O
	db	_LABEL			; 50 P
	db	_LABEL			; 51 Q
	db	_LABEL			; 52 R
	db	_LABEL			; 53 S
	db	_LABEL			; 54 T
	db	_LABEL			; 55 U
	db	_LABEL			; 56 V
	db	_LABEL			; 57 W
	db	_LABEL			; 58 X
	db	_LABEL			; 59 Y
	db	_LABEL			; 5A Z
	db	0			; 5B [
	db	0			; 5C \
	db	0			; 5D ]
	db	0			; 5E ^
	db	_LABEL			; 5F _
	db	0			; 60 `
	db	_LABEL + _HEX		; 61 a
	db	_LABEL + _HEX		; 62 b
	db	_LABEL + _HEX		; 63 c
	db	_LABEL + _HEX		; 64 d
	db	_LABEL + _HEX		; 65 e
	db	_LABEL + _HEX		; 66 f
	db	_LABEL			; 67 g
	db	_LABEL			; 68 h
	db	_LABEL			; 69 i
	db	_LABEL			; 6A j
	db	_LABEL			; 6B k
	db	_LABEL			; 6C l
	db	_LABEL			; 6D m
	db	_LABEL			; 6E n
	db	_LABEL			; 6F o
	db	_LABEL			; 70 p
	db	_LABEL			; 71 q
	db	_LABEL			; 72 r
	db	_LABEL			; 73 s
	db	_LABEL			; 74 t
	db	_LABEL			; 75 u
	db	_LABEL			; 76 v
	db	_LABEL			; 77 w
	db	_LABEL			; 78 x
	db	_LABEL			; 79 y
	db	_LABEL			; 7A z
	db	0			; 7B {
	db	0			; 7C |
	db	0			; 7D }
	db	0			; 7E ~
	db	0			; 7F (DEL)

	; and the rest are 0...

	db	257 - ($ - offset __ltype) dup(0)

	END

