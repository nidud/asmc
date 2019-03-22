; NLSDATA1.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef DLL_FOR_WIN32S

include stdlib.inc
;include nlsint.inc

public	__mb_cur_max
public	__decimal_point
public	__decimal_point_length

.data
;
;  Value of MB_CUR_MAX macro.
;
__mb_cur_max int_t 1

;
;  Localized decimal point string.
;
dot	db ".",0,0,0

__decimal_point dd dot


;
;  Decimal point length, not including terminating null.
;
__decimal_point_length size_t 1


endif ; DLL_FOR_WIN32S

	end