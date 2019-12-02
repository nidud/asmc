; CMPATH.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include stdlib.inc
include cfini.inc

    .code

cmpath proc private ini_id
local path[_MAX_PATH]:byte

    .switch
      .case !panel_state(cpanel)
      .case !CFGetSectionID(&cp_directory, ini_id)
      .case word ptr [eax] == '><'
      .case !strchr(eax, ',')
	.endc
      .default
	inc eax
	strstart(eax)
	mov ecx,eax
	strnzcpy(&path, ecx, _MAX_PATH-1)
	expenviron(eax)
	.endc .if path == '['
	cpanel_setpath(&path)
	.endc
    .endsw
    ret
cmpath endp

cmpathp macro q
cmpath&q proc
    cmpath(q)
    ret
cmpath&q endp
    endm

cmpathp 0
cmpathp 1
cmpathp 2
cmpathp 3
cmpathp 4
cmpathp 5
cmpathp 6
cmpathp 7

    END
