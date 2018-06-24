include ltype.inc

	public	_ltype

	.data

_ltype	label byte
	db 0			; -1 EOF
	db _CONTROL		; 00 (NUL)
	db _CONTROL		; 01 (SOH)
	db _CONTROL		; 02 (STX)
	db _CONTROL		; 03 (ETX)
	db _CONTROL		; 04 (EOT)
	db _CONTROL		; 05 (ENQ)
	db _CONTROL		; 06 (ACK)
	db _CONTROL		; 07 (BEL)
	db _CONTROL		; 08 (BS)
	db _SPACE+_CONTROL	; 09 (HT)
	db _SPACE+_CONTROL	; 0A (LF)
	db _SPACE+_CONTROL	; 0B (VT)
	db _SPACE+_CONTROL	; 0C (FF)
	db _SPACE+_CONTROL	; 0D (CR)
	db _CONTROL		; 0E (SI)
	db _CONTROL		; 0F (SO)
	db _CONTROL		; 10 (DLE)
	db _CONTROL		; 11 (DC1)
	db _CONTROL		; 12 (DC2)
	db _CONTROL		; 13 (DC3)
	db _CONTROL		; 14 (DC4)
	db _CONTROL		; 15 (NAK)
	db _CONTROL		; 16 (SYN)
	db _CONTROL		; 17 (ETB)
	db _CONTROL		; 18 (CAN)
	db _CONTROL		; 19 (EM)
	db _CONTROL		; 1A (SUB)
	db _CONTROL		; 1B (ESC)
	db _CONTROL		; 1C (FS)
	db _CONTROL		; 1D (GS)
	db _CONTROL		; 1E (RS)
	db _CONTROL		; 1F (US)
	db _SPACE		; 20 SPACE
	db _PUNCT		; 21 !
	db _PUNCT		; 22 ""
	db _PUNCT		; 23 #
	db _PUNCT+_LABEL	; 24 $
	db _PUNCT		; 25 %
	db _PUNCT		; 26 &
	db _PUNCT		; 27 '
	db _PUNCT		; 28 (
	db _PUNCT		; 29 )
	db _PUNCT		; 2A *
	db _PUNCT		; 2B +
	db _PUNCT		; 2C
	db _PUNCT		; 2D -
	db _PUNCT		; 2E .
	db _PUNCT		; 2F /
	db _DIGIT+_HEX		; 30 0
	db _DIGIT+_HEX		; 31 1
	db _DIGIT+_HEX		; 32 2
	db _DIGIT+_HEX		; 33 3
	db _DIGIT+_HEX		; 34 4
	db _DIGIT+_HEX		; 35 5
	db _DIGIT+_HEX		; 36 6
	db _DIGIT+_HEX		; 37 7
	db _DIGIT+_HEX		; 38 8
	db _DIGIT+_HEX		; 39 9
	db _PUNCT		; 3A :
	db _PUNCT		; 3B ;
	db _PUNCT		; 3C <
	db _PUNCT		; 3D =
	db _PUNCT		; 3E >
	db _PUNCT+_LABEL	; 3F ?
	db _PUNCT+_LABEL	; 40 @
	db _UPPER+_LABEL+_HEX	; 41 A
	db _UPPER+_LABEL+_HEX	; 42 B
	db _UPPER+_LABEL+_HEX	; 43 C
	db _UPPER+_LABEL+_HEX	; 44 D
	db _UPPER+_LABEL+_HEX	; 45 E
	db _UPPER+_LABEL+_HEX	; 46 F
	db _UPPER+_LABEL	; 47 G
	db _UPPER+_LABEL	; 48 H
	db _UPPER+_LABEL	; 49 I
	db _UPPER+_LABEL	; 4A J
	db _UPPER+_LABEL	; 4B K
	db _UPPER+_LABEL	; 4C L
	db _UPPER+_LABEL	; 4D M
	db _UPPER+_LABEL	; 4E N
	db _UPPER+_LABEL	; 4F O
	db _UPPER+_LABEL	; 50 P
	db _UPPER+_LABEL	; 51 Q
	db _UPPER+_LABEL	; 52 R
	db _UPPER+_LABEL	; 53 S
	db _UPPER+_LABEL	; 54 T
	db _UPPER+_LABEL	; 55 U
	db _UPPER+_LABEL	; 56 V
	db _UPPER+_LABEL	; 57 W
	db _UPPER+_LABEL	; 58 X
	db _UPPER+_LABEL	; 59 Y
	db _UPPER+_LABEL	; 5A Z
	db _PUNCT		; 5B [
	db _PUNCT		; 5C \
	db _PUNCT		; 5D ]
	db _PUNCT		; 5E ^
	db _PUNCT+_LABEL	; 5F _
	db _PUNCT		; 60 `
	db _LOWER+_LABEL+_HEX	; 61 a
	db _LOWER+_LABEL+_HEX	; 62 b
	db _LOWER+_LABEL+_HEX	; 63 c
	db _LOWER+_LABEL+_HEX	; 64 d
	db _LOWER+_LABEL+_HEX	; 65 e
	db _LOWER+_LABEL+_HEX	; 66 f
	db _LOWER+_LABEL	; 67 g
	db _LOWER+_LABEL	; 68 h
	db _LOWER+_LABEL	; 69 i
	db _LOWER+_LABEL	; 6A j
	db _LOWER+_LABEL	; 6B k
	db _LOWER+_LABEL	; 6C l
	db _LOWER+_LABEL	; 6D m
	db _LOWER+_LABEL	; 6E n
	db _LOWER+_LABEL	; 6F o
	db _LOWER+_LABEL	; 70 p
	db _LOWER+_LABEL	; 71 q
	db _LOWER+_LABEL	; 72 r
	db _LOWER+_LABEL	; 73 s
	db _LOWER+_LABEL	; 74 t
	db _LOWER+_LABEL	; 75 u
	db _LOWER+_LABEL	; 76 v
	db _LOWER+_LABEL	; 77 w
	db _LOWER+_LABEL	; 78 x
	db _LOWER+_LABEL	; 79 y
	db _LOWER+_LABEL	; 7A z
	db _PUNCT		; 7B {
	db _PUNCT		; 7C |
	db _PUNCT		; 7D }
	db _PUNCT		; 7E ~
	db _CONTROL		; 7F (DEL)

	; and the rest are 0...

	db 257 - ($ - offset _ltype) dup(0)

	END

