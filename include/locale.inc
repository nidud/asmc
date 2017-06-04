ifndef __LIBC_INC
 include libc.inc
endif

.xlist

LC_ALL		equ 0
LC_COLLATE	equ 1
LC_CTYPE	equ 2
LC_MONETARY	equ 3
LC_NUMERIC	equ 4
LC_TIME		equ 5

LC_MIN		equ LC_ALL
LC_MAX		equ LC_TIME


lconv		STRUC
decimal_point	LPSTR ?
thousands_sep	LPSTR ?
grouping	LPSTR ?
int_curr_symbol LPSTR ?
currency_symbol LPSTR ?
mon_decimal_point LPSTR ?
mon_thousands_sep LPSTR ?
mon_grouping	LPSTR ?
positive_sign	LPSTR ?
negative_sign	LPSTR ?
int_frac_digits BYTE ?
frac_digits	BYTE ?
p_cs_precedes	BYTE ?
p_sep_by_space	BYTE ?
n_cs_precedes	BYTE ?
n_sep_by_space	BYTE ?
p_sign_posn	BYTE ?
n_sign_posn	BYTE ?
lconv		ENDS


setlocale	PROTO :SINT, :LPSTR
localeconv	PROTO
_wsetlocale	PROTO :SINT, :LPWSTR

.list
