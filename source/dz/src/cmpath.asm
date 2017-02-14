; CMPATH.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include stdlib.inc
include cfini.inc

	.code

cmpath	PROC PRIVATE ini_id
local	path[_MAX_PATH]:BYTE

	.switch
	  .case !panel_state(cpanel)
	  .case !CFGetSectionID( addr cp_directory, ini_id )
	  .case WORD PTR [eax] == '><'
	  .case !strchr( eax, ',' )
		.endc
	  .default
		inc	eax
		strstart( eax )
		mov	ecx,eax
		strnzcpy( addr path, ecx, _MAX_PATH-1 )
		expenviron( eax )
		.endc .if path == '['
		cpanel_setpath(addr path)
		.endc
	.endsw
	ret
cmpath	ENDP

cmpathp MACRO q
cmpath&q PROC
	cmpath( q )
	ret
cmpath&q ENDP
	ENDM

cmpathp 0
cmpathp 1
cmpathp 2
cmpathp 3
cmpathp 4
cmpathp 5
cmpathp 6
cmpathp 7

	END
