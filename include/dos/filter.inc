.xlist

FILT_MAXSTRING	equ 128

S_FILT	STRUC
of_flag		dw ?
of_max_date	dw ?
of_min_date	dw ?
of_max_size	dd ?
of_min_size	dd ?
of_include	db FILT_MAXSTRING dup(?)
of_exclude	db FILT_MAXSTRING dup(?)
S_FILT	ENDS

externdef filter:DWORD
filter_fblk	PROTO _CType :DWORD
filter_wblk	PROTO _CType :DWORD
filter_edit	PROTO _CType :DWORD, :DWORD

.list
