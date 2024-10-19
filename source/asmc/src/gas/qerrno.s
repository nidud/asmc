
.intel_syntax noprefix

.global qerrno


.SECTION .text
	.ALIGN	16


.SECTION .data
	.ALIGN	16

qerrno:
	.byte  0x00, 0x00, 0x00, 0x00


.att_syntax prefix
