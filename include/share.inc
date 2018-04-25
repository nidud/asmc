.pragma list(push, 0)

SH_COMPAT	equ 0000h
SH_DENYRW	equ 0010h
SH_DENYWR	equ 0020h
SH_DENYRD	equ 0030h
SH_DENYNONE	equ 0040h
SH_DENYNO	equ SH_DENYNONE ; MS documentation uses both

.pragma list(pop)
