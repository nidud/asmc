include tinfo.inc
include string.inc
include malloc.inc
include errno.inc

    .code

    assume esi:ptr S_TINFO
    assume edx:ptr S_TINFO

tiopen proc uses esi ti:PTINFO, tabsize:UINT, flags:UINT

    malloc(SIZE S_TINFO)
    jz	nomem

    mov edx,edi
    mov esi,eax
    mov edi,eax
    mov ecx,SIZE S_TINFO
    xor eax,eax
    rep stosb
    mov edi,edx
    mov eax,tabsize
    mov [esi].ti_tabz,eax

    mov ah,at_background[B_TextEdit]
    or	ah,at_foreground[F_TextEdit]
    mov al,' '
    mov [esi].ti_clat,eax
    mov [esi].ti_stat,eax
    mov eax,flags
    or	eax,_T_UNREAD
    mov [esi].ti_flag,eax
    ;
    ; adapt to current screen
    ;
    tsetrect(esi, tgetrect())

    mov [esi].ti_bcol,TIMAXLINE
    mov [esi].ti_blen,TIMAXFILE

    .if tialloc(esi)

	.if tigetfile(ti)
	    ;
	    ; link to last file
	    ;
	    mov [esi].ti_prev,edx
	    mov [edx].ti_next,esi
	.endif

	mov  eax,esi
	test eax,eax
    .else
	free(esi)
	jmp nomem
    .endif
toend:
    ret
nomem:
    ermsg(0, &CP_ENOMEM)
    xor eax,eax
    jmp toend
tiopen	endp

    assume ebx:ptr S_TINFO
    assume edi:ptr S_TINFO

ticlose proc uses esi edi ebx ti:PTINFO

    mov esi,ti
    xor edi,edi

    .if [esi].ti_flag & _T_MALLOC

	tifree(esi)
	dlclose(&[esi].ti_DOBJ)
    .endif

    .if tigetfile(esi)

	mov edi,[esi].ti_prev
	mov ebx,[esi].ti_next
	mov [esi].ti_prev,0
	mov [esi].ti_next,0

	.if ebx && [ebx].ti_prev == esi

	    mov [ebx].ti_prev,edi
	.endif

	.if edi

	    .if [edi].ti_next == esi

		mov [edi].ti_next,ebx
	    .endif
	.else

	    mov edi,ebx
	.endif
    .endif

    free(esi)
    mov eax,edi
    ret
ticlose endp

    assume ebx: nothing
    assume edi: nothing

tihide	proc ti:PTINFO

    mov ecx,ti
    .if ecx

	mov [ecx].S_TINFO.ti_scrc,0
	dlclose(&[ecx].S_TINFO.ti_DOBJ)
    .endif
    ret

tihide	endp

    assume esi: ptr S_TINFO

tihideall proc ti:PTINFO

    .if tigetfile(ti)

	tihide(ti)
    .endif
    ret

tihideall endp

timenus proc uses esi ebx ti:PTINFO

    mov esi,ti

    .if tistate(esi)

	.if edx & _D_ONSCR && ecx & _T_USEMENUS

	    mov ebx,eax

	    mov eax,[esi].ti_loff
	    add eax,[esi].ti_yoff
	    inc eax
	    push eax

	    mov eax,[esi].ti_xoff
	    add eax,[esi].ti_boff
	    push eax

	    mov eax,[ebx][4]
	    add al,[ebx].S_DOBJ.dl_rect.rc_col
	    sub al,18
	    mov cl,ah

	    scputf(eax, ecx, 0, 0, " col %-3u ln %-6u")
	    add esp,4*2

	    mov eax,' '
	    .if [esi].ti_flag & _T_MODIFIED

		mov al,'*'
	    .endif
	    movzx edx,[ebx].S_DOBJ.dl_rect.rc_x
	    scputw(edx, ecx, 1, eax)
	.endif
    .endif
    xor eax,eax
    ret
timenus endp

    assume edi:ptr S_DOBJ

tishow proc uses esi edi ebx ti:PTINFO

    mov esi,ti

    .if esi

	lea edi,[esi].S_TINFO.ti_DOBJ
	.if !([edi].dl_flag & _D_DOPEN)

	    tsetrect(esi, tgetrect())
	    mov edx,[esi].ti_clat
	    .if [esi].ti_flag & _T_USESTYLE

		mov edx,[esi].ti_stat
	    .endif

	    shr edx,8
	    .if rcopen([edi].dl_rect, _D_CLEAR or _D_BACKG, edx, 0, 0)

		mov [edi].dl_wp,eax
		mov [edi].dl_flag,_D_DOPEN
	    .endif
	.endif

	.if [edi].dl_flag & _D_DOPEN

	    .if !([edi].dl_flag & _D_ONSCR)

		dlshow(edi)
	    .endif
	    xor eax,eax
	    mov [esi].ti_scrc,eax

	    .if [esi].ti_flag & _T_USEMENUS

		movzx edx,[edi].dl_rect.rc_x
		movzx ebx,[edi].dl_rect.rc_y
		mov ecx,[esi].ti_cols
		mov ah,at_background[B_Menus]
		or  ah,at_foreground[F_Menus]
		mov al,' '

		scputw(edx, ebx, ecx, eax)

		inc edx
		sub ecx,19
		scpath(edx, ebx, ecx, [esi].ti_file)
	    .endif
	    tiputs(esi)
	.endif
    .endif
    ret
tishow	endp

titogglemenus proc uses esi ti:PTINFO

    mov esi,ti

    .if tistate(esi)

	tihide(esi)

	movzx edx,[esi].ti_DOBJ.dl_rect.rc_y
	movzx ecx,[esi].ti_DOBJ.dl_rect.rc_row
	mov eax,[esi].ti_flag
	xor eax,_T_USEMENUS
	mov [esi].ti_flag,eax
	.if eax & _T_USEMENUS

	    inc edx
	    dec ecx
	.endif
	mov [esi].ti_ypos,edx
	mov [esi].ti_rows,ecx

	tishow(esi)
    .endif
    xor eax,eax
    ret
titogglemenus endp

    assume esi:ptr S_TINFO
    assume edi:ptr S_TINFO

titogglefile proc uses esi edi ebx old:PTINFO, new:PTINFO

    mov edi,old
    mov eax,new
    mov ebx,edi
    mov esi,eax

    .if esi != edi && [esi].ti_flag & _T_TEDIT

	mov ebx,esi
	tishow(esi)

	.if [esi].ti_DOBJ.dl_flag & _D_DOPEN

	    and [edi].ti_DOBJ.dl_flag,NOT (_D_DOPEN OR _D_ONSCR)
	    free([esi].ti_DOBJ.dl_wp)
	    mov eax,[edi].ti_DOBJ.dl_wp
	    mov [esi].ti_DOBJ.dl_wp,eax
	.else
	    mov ebx,edi
	.endif
    .endif
    mov eax,ebx
    ret

titogglefile endp

    END
