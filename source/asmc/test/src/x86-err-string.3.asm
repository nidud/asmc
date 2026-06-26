
;--- string ops with symbolic memory operands.
;--- invalid segment prefixes. works since v2.14

DSEG segment
dvarb	label byte
DSEG ends

ESEG segment
evarb	label byte
ESEG ends

SSEG segment
svarb	label byte
SSEG ends

CSEG segment
cvarb	label byte
CSEG ends

	.286

CSEG segment
	ASSUME cs:CSEG, ds:DSEG, es:ESEG, ss:SSEG

	stos cvarb
	stos dvarb
	stos evarb	;ok
	stos svarb

	scas cvarb
	scas dvarb
	scas evarb	;ok
	scas svarb

	ins cvarb, dx
	ins dvarb, dx
	ins evarb, dx	;ok
	ins svarb, dx

	movs cvarb, dvarb
	movs dvarb, dvarb
	movs evarb, dvarb	;ok
	movs svarb, dvarb

	cmps dvarb, cvarb
	cmps dvarb, dvarb
	cmps dvarb, evarb	;ok
	cmps dvarb, svarb

CSEG ends

	end

