.xlist

S_DZDS		STRUC
dz_envlen	dw ?
dz_envseg	dw ?
dz_command	dw 2 dup(?)
dz_fcb_0P	dw 2 dup(?)
dz_fcb_1P	dw 2 dup(?)
dz_dzmain	db 80 dup(?)
dz_dzcommand	db 128 dup(?)
dz_fcb_160	db 16 dup(?)
dz_fcb_161	db 16 dup(?)
dz_exeproc	db 80 dup(?)
dz_execommand	db 128 dup(?)
dz_errno	dw ?
dz_eflag	dw ?
dz_count	dw ?
dz_exename	dw ?
dz_oldintF1	dd ?
S_DZDS		ENDS	; 474 byte

.list
