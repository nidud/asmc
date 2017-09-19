; CMSORT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc

    .code

cmsort proc private uses esi edi ebx	; AX: OFFSET panel, DX: sort flag

local path[_MAX_PATH]:byte

    mov esi,edx
    .if panel_state(eax)

	mov ecx,esi
	mov edi,eax
	mov esi,[eax].S_PANEL.pn_wsub
	mov eax,[esi].S_WSUB.ws_flag
	and eax,not (_W_SORTSIZE or _W_NOSORT)
	or  eax,ecx
	mov [esi].S_WSUB.ws_flag,eax

	.if panel_curobj(edi)

	    lea ecx,path
	    strcpy(ecx, eax)
	    wssort(esi)
	    .if wsearch(esi, addr path) != -1

		push eax
		dlclose([edi].S_PANEL.pn_xl)
		pop  eax
		panel_setid(edi, eax)
		.if edi == cpanel

		    pcell_show(edi)
		.endif
	    .endif
	.endif
	panel_putitem(edi, 0)
	mov eax,1
    .endif
    ret
cmsort	endp

cmnosort:
    .if panel_state(eax)

	push eax
	mov edx,[eax].S_PANEL.pn_wsub
	or  [edx].S_WSUB.ws_flag,_W_NOSORT
	panel_read(eax)
	pop eax
	panel_putitem(eax, 0)
	mov eax,1
    .endif
    ret

cmanosort proc
    mov eax,panela
    jmp cmnosort
cmanosort endp

cmbnosort proc
    mov eax,panelb
    jmp cmnosort
cmbnosort endp

cmcnosort proc
    mov eax,cpanel
    jmp cmnosort
cmcnosort endp

cmadate proc
    mov eax,panela
    mov edx,_W_SORTDATE
    jmp cmsort
cmadate endp

cmbdate proc
    mov eax,panelb
    mov edx,_W_SORTDATE
    jmp cmsort
cmbdate endp

cmcdate proc
    mov eax,cpanel
    mov edx,_W_SORTDATE
    jmp cmsort
cmcdate endp

cmatype proc
    mov eax,panela
    mov edx,_W_SORTTYPE
    jmp cmsort
cmatype endp

cmbtype proc
    mov eax,panelb
    mov edx,_W_SORTTYPE
    jmp cmsort
cmbtype endp

cmctype proc
    mov eax,cpanel
    mov edx,_W_SORTTYPE
    jmp cmsort
cmctype endp

cmasize proc
    mov eax,panela
    mov edx,_W_SORTSIZE
    jmp cmsort
cmasize endp

cmbsize proc
    mov eax,panelb
    mov edx,_W_SORTSIZE
    jmp cmsort
cmbsize endp

cmcsize proc
    mov eax,cpanel
    mov edx,_W_SORTSIZE
    jmp cmsort
cmcsize endp

cmaname proc
    mov eax,panela
    mov edx,_W_SORTNAME
    jmp cmsort
cmaname endp

cmbname proc
    mov eax,panelb
    mov edx,_W_SORTNAME
    jmp cmsort
cmbname endp

cmcname proc
    mov eax,cpanel
    mov edx,_W_SORTNAME
    jmp cmsort
cmcname endp

    END
