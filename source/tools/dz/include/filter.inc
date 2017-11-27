.xlist

FILT_MAXSTRING	equ 128

S_FILT		STRUC
of_flag		dd ?
of_max_date	dd ?
of_min_date	dd ?
of_max_size	SIZE_T ?
of_min_size	SIZE_T ?
of_include	db FILT_MAXSTRING dup(?)
of_exclude	db FILT_MAXSTRING dup(?)
S_FILT		ENDS ; 276

externdef	filter:SIZE_T
filter_fblk	PROTO :PTR S_FBLK
filter_wblk	PROTO :PTR WIN32_FIND_DATA
filter_edit	PROTO :PTR, :PTR

.list
