
.intel_syntax noprefix

.global OmfFixGenFixModend
.global OmfFixGenFix


.SECTION .text
	.ALIGN	16

OmfFixGenFixModend:
	xor	eax, eax
	ret

OmfFixGenFix:
	xor	eax, eax
	ret

.att_syntax prefix
