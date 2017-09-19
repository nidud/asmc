; DOSKEY.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include alloc.inc

    .data

externdef	IDD_DZHistory:dword
doskey_bindex	db 0
doskey_isnext	db 0

    .code

doskeysave proc

    .if strtrim(&com_base)

	mov eax,history
	.if eax

	    lea edx,[eax].S_HISTORY.h_doskey
	    mov doskey_bindex,0
	    mov doskey_isnext,0
	    mov eax,[edx]
	    .if eax

		.if strcmp(&com_base, eax)

		    free([edx + 4 * (MAXDOSKEYS - 1)])
		    memmove(&[edx+4], edx, 4 * (MAXDOSKEYS - 1))
		.else
		    mov eax,1
		    ret
		.endif
	    .endif
	.endif
	push edx
	salloc(&com_base)
	pop edx
	mov [edx],eax
	mov eax,1
    .endif
    ret

doskeysave endp

doskeytocommand proc private

    mov eax,history
    movzx ecx,doskey_bindex

    mov eax,[eax+ecx*4].S_HISTORY.h_doskey
    .if eax

	strcpy(&com_base, eax)
    .endif
    ret

doskeytocommand endp

CommandlineVisible:
    mov eax,DLG_Commandline
    mov eax,[eax]
    and eax,_D_ONSCR
    ret

cmdoskeyup proc

    .if CommandlineVisible()

	mov eax,1
	.if doskey_isnext == al

	    mov com_base,ah
	.else
	    doskeytocommand()
	    inc doskey_bindex
	    .if doskey_bindex >= MAXDOSKEYS

		mov doskey_bindex,0
	    .endif
	.endif
	comevent(KEY_END)
	mov eax,1
	mov doskey_isnext,ah
    .endif
    ret

cmdoskeyup endp

cmdoskeydown proc

    .if CommandlineVisible()

	xor eax,eax
	.if doskey_isnext == al

	    mov com_base,al
	.else
	    .if doskey_bindex == al

		mov doskey_bindex,MAXDOSKEYS-1
	    .else
		dec doskey_bindex
	    .endif
	    doskeytocommand()
	.endif
	comevent(KEY_END)
	mov eax,1
	mov doskey_isnext,al
    .endif
    ret
cmdoskeydown endp

history_event_list proc uses esi

    push eax
    mov eax,[eax].S_DOBJ.dl_object
    mov esi,eax
    mov ecx,[edx].S_LOBJ.ll_dcount
    .repeat
	or  [eax].S_TOBJ.to_flag,_O_STATE
	lea eax,[eax+SIZE S_TOBJ]
    .untilcxz
    mov ecx,[edx].S_LOBJ.ll_numcel
    mov eax,[edx].S_LOBJ.ll_index
    mov edx,[edx].S_LOBJ.ll_list
    lea edx,[edx+eax*4]

    .while  ecx
	mov eax,[edx]
	.break .if !eax
	mov [esi].S_TOBJ.to_data,eax
	and [esi].S_TOBJ.to_flag,not _O_STATE
	lea edx,[edx+4]
	lea esi,[esi+SIZE S_TOBJ]
	dec ecx
    .endw
    dlinit()
    mov eax,1
    ret

history_event_list endp

cmhistory proc uses edi ebx

  local ll:S_LOBJ

    .if CommandlineVisible()

	.if rsopen(IDD_DZHistory)

	    mov ebx,eax
	    lea edi,ll
	    xor eax,eax
	    mov ecx,SIZE S_LOBJ
	    rep stosb
	    mov ll.ll_proc,history_event_list
	    mov ll.ll_dcount,16
	    mov edx,history
	    add edx,S_HISTORY.h_doskey
	    mov ll.ll_list,edx
	    mov ecx,MAXDOSKEYS
	    xor edi,edi

	    .repeat
		.if eax != [edx]
		    inc edi
		.endif
		add edx,4
	    .untilcxz

	    mov ll.ll_count,edi
	    .if edi > 16
		mov edi,16
	    .endif

	    mov ll.ll_numcel,edi
	    mov al,doskey_bindex
	    mov [ebx].S_DOBJ.dl_index,al

	    .if al >= 16
		mov [ebx].S_DOBJ.dl_index,cl
	    .endif

	    lea edx,ll
	    mov tdllist,edx
	    mov eax,ebx

	    history_event_list()
	    dlshow(ebx)
	    rsevent(IDD_DZHistory, ebx)
	    dlclose(ebx)

	    mov eax,edx
	    .if eax
		dec eax
		mov doskey_bindex,al
		inc eax
		shl eax,4
		strcpy(&com_base, [ebx+eax].S_TOBJ.to_data)
		comevent(KEY_END)
		mov eax,1
	    .endif
	.endif
    .endif
    ret

cmhistory endp

    END
