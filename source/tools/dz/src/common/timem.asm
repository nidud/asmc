include tinfo.inc
include direct.inc
include errno.inc
include malloc.inc
include string.inc
include ltype.inc
include dzlib.inc

    .code

;
; Validate tinfo
; return CX .ti_flag, DX .dl_flag, AX dialog
;
tistate proc ti:PTINFO

    mov edx,ti
    xor eax,eax

    .if edx

        mov ecx,[edx].S_TINFO.ti_flag
        lea edx,[edx].S_TINFO.ti_DOBJ

        .if ecx & _T_TEDIT

            mov eax,edx
            movzx edx,[edx].S_DOBJ.dl_flag
        .endif
    .endif
    ret

tistate endp

;-----------------------------------------------------------------------------
; Alloc file buffer
;-----------------------------------------------------------------------------

    assume esi:ptr S_TINFO

tialloc proc uses esi ti:PTINFO

    mov esi,ti

    mov eax,[esi].ti_blen
    add eax,TIMAXLINE*2+_MAX_PATH*2+STYLESIZE

    .if malloc(eax)

        or  [esi].ti_flag,_T_MALLOC or _T_TEDIT
        mov [esi].ti_bp,eax
        add eax,[esi].ti_blen
        mov [esi].ti_lp,eax
        add eax,TIMAXLINE*2
        mov [esi].ti_style,eax
        add eax,STYLESIZE
        mov [esi].ti_file,eax
        mov eax,1
    .else

        ermsg(0, addr CP_ENOMEM)
        xor eax,eax
    .endif
    ret

tialloc endp

tifree proc uses esi ti:PTINFO

    mov esi,ti
    mov eax,[esi].ti_flag
    .if eax & _T_MALLOC
        xor eax,_T_MALLOC
        mov [esi].ti_flag,eax
        free([esi].ti_bp)
    .endif
    ret

tifree endp

tirealloc proc uses esi edi ebx edx ti:PTINFO

    mov esi,ti
    mov edi,[esi].ti_bp
    mov ebx,[esi].ti_blen
    add [esi].ti_blen,TIMAXFILE

    .if !tialloc(esi)
        mov [esi].ti_blen,ebx
    .else
        memcpy([esi].ti_bp, edi, ebx)
        add ebx,edi
        memcpy([esi].ti_lp, ebx, TIMAXLINE * 2 + _MAX_PATH * 2 + STYLESIZE)
        free(edi)
        sub [esi].ti_flp,edi
        mov eax,[esi].ti_bp
        add [esi].ti_flp,eax
        mov eax,edi
        test    eax,eax
    .endif

    ret
tirealloc endp

    assume esi:nothing

timemzero proc uses edi ti:PTINFO

    mov eax,ti
    mov ecx,[eax].S_TINFO.ti_blen
    mov edx,[eax].S_TINFO.ti_bp
    mov edi,edx
    add ecx,TIMAXLINE*2
    xor eax,eax
    rep stosb
    mov eax,edx
    ret

timemzero endp

    assume edx:ptr S_TINFO

;------------------------------------------------------------------------------
; Get line from buffer
;------------------------------------------------------------------------------

tigetline proc uses esi edi ebx ti:PTINFO, line_id:UINT

    mov eax,line_id         ; ARG: line id
    mov ebx,eax
    mov edx,ti
    mov edi,[edx].ti_bp     ; file is string[MAXFILESIZE]

    .repeat

        .if eax                         ; first line ?
            mov ecx,[edx].ti_curl       ; current line ?
            .if eax == ecx              ; save time on repeated calls..
                mov edi,[edx].ti_flp    ; pointer to current line in buffer
            .else
                mov esi,eax             ; loop from EDI to line id in EAX
                .repeat
                    .if !strchr(edi, 10)
                        mov [edx].ti_curl,eax
                        mov edi,[edx].ti_bp
                        mov [edx].ti_flp,edi
                        .break
                    .endif
                    lea edi,[eax+1]
                    dec esi
                .untilz
            .endif
        .endif

        mov [edx].ti_flp,edi        ; set current line pointer
        .if strchr(edi, 10)         ; get length of line
            .if byte ptr [eax-1] == 0Dh
                dec eax
            .endif
            sub eax,edi
        .else
            strlen(edi)
        .endif

        mov [edx].ti_fbcnt,eax
        mov [edx].ti_curl,ebx
        mov ecx,eax
        mov esi,edi
        mov edi,[edx].ti_lp
        xor eax,eax

        .if ecx < [edx].ti_blen

            mov [edi],eax
            mov ebx,[edx].ti_tabz   ; create mask for tabs in EBX
            dec ebx
            and ebx,TIMAXTABSIZE-1

            .while ecx

                lodsb
                .if eax == 9

                    .if [edx].ti_flag & _T_USETABS

                        .repeat
                            mov [edi],ax
                            inc edi
                            mov eax,TITABCHAR
                        .until !( edi & ebx )
                    .else
                        or [edx].ti_flag,_T_MODIFIED
                        mov al,' '
                        mov [edi],ax
                        inc edi
                        .while ebx & edi
                            mov [edi],ax
                            inc edi
                        .endw
                    .endif
                .else
                    mov [edi],ax
                    inc edi
                .endif
                dec ecx
            .endw

            mov eax,[edx].ti_lp     ; set expanded line size
            mov ecx,edi
            sub ecx,eax
            mov [edx].ti_bcnt,ecx
        .endif
    .until 1
    test eax,eax
    ret

tigetline endp

tigetnextl proc uses esi edi ebx ti:PTINFO

    xor eax,eax
    mov edx,ti
    mov [edx].ti_curl,eax
    mov edi,[edx].ti_flp    ; next = current + size + 0D 0A
    add edi,[edx].ti_fbcnt
    mov al,[edi]
    .if eax
        .if al == 0x0D
            inc edi
            mov al,[edi]
        .endif
        .if al != 0x0A
            xor eax,eax
        .else
            inc edi
            mov [edx].ti_flp,edi
            strchr(edi,10)
            .ifz
                strlen(edi)
            .else
                .if byte ptr [eax-1] == 0x0D
                    dec eax
                .endif
                sub eax,edi
            .endif
            mov [edx].ti_fbcnt,eax
            mov ecx,eax
            mov esi,edi
            mov edi,[edx].ti_lp
            xor eax,eax
            mov [edi],eax

            .if ecx < [edx].ti_blen

                mov ebx,[edx].ti_tabz
                dec ebx
                and ebx,TIMAXTABSIZE-1

                .while ecx
                    lodsb
                    .if al == 9
                        .if [edx].ti_flag & _T_USETABS
                            stosb
                            mov eax,TITABCHAR
                            .while edi & ebx
                                stosb
                            .endw
                        .else
                            or [edx].ti_flag,_T_MODIFIED
                            mov al,' '
                            stosb
                            .while ebx & edi
                                stosb
                            .endw
                        .endif
                    .else
                        stosb
                    .endif
                    dec ecx
                .endw
                mov [edi],ah
                mov eax,[edx].ti_lp
                mov ecx,edi
                sub ecx,eax
                mov [edx].ti_bcnt,ecx
            .else
                xor eax,eax
            .endif
        .endif
    .endif
    test eax,eax
    ret

tigetnextl endp

ticurlp proc uses esi edi ti:PTINFO

    mov edx,ti          ; current line =
    mov eax,[edx].ti_loff   ; line offset -- first line on screen
    add eax,[edx].ti_yoff   ; + y offset -- cursory()

    .if tigetline(edx, eax)

        mov esi,eax
        xor ecx,ecx         ; just in case..
        add eax,[edx].ti_bcol   ; terminate line
        mov [eax-1],cl
        ;
        ; cursor->x may be above lenght of line
        ; so space is added up to current x-pos
        ;
        .repeat
            mov eax,[edx].ti_boff   ; current line offset =
            add eax,[edx].ti_xoff   ; buffer offset -- start of screen line
            .break .if eax < [edx].ti_bcol  ; + x offset -- cursorx()
            .if [edx].ti_xoff != ecx
                dec [edx].ti_xoff
            .else
                .break .if [edx].ti_boff == ecx
                dec [edx].ti_boff
            .endif
        .until  0
        mov edi,eax
        .if strlen(esi) < edi
            mov ecx,' '
            .repeat
                mov [esi+eax],cx
                inc eax
            .until  eax >= edi
            mov ecx,eax
        .endif
        mov [edx].ti_bcnt,eax   ; byte count in line
        mov eax,esi
    .endif
    test eax,eax
    ret
ticurlp endp

ticurcp proc ti:PTINFO
    ;
    ; current pointer = current line + line offset
    ;
    .if ticurlp(ti)
        add eax,[edx].ti_boff
        add eax,[edx].ti_xoff
    .endif
    ret

ticurcp endp

tiexpandline proc uses esi edi ebx eax ti:PTINFO, line:LPSTR

    mov edx,ti
    mov eax,line
    mov ebx,[edx].ti_tabz

    .if [edx].ti_flag & _T_USETABS

        dec bl
        and ebx,TIMAXTABSIZE-1
        mov esi,eax
        mov edi,eax
        mov ecx,[edx].ti_bcol
        add ecx,esi
        dec ecx
        .while  1
            lodsb
            .break .if al < 1

            .if al == 9
                stosb   ; insert TAB char
                        ; insert "spaces" to next Tab offset
                .break .if edi >= ecx
                .while esi & ebx
                    strshr(esi, TITABCHAR)
                    .break .if edi >= ecx
                    inc esi
                    mov edi,esi
                .endw
                .continue
            .endif

            .break .if edi == ecx
            stosb
        .endw
        mov byte ptr [edi],0
    .endif
    ret
tiexpandline endp

    assume edx:nothing

tioptimalfill proc uses esi edi ebx ecx ti:PTINFO, line_offset:LPSTR

    mov esi,line_offset
    strlen(esi)
    mov ecx,eax

    mov edx,ti
    mov eax,[edx].S_TINFO.ti_flag
    and eax,_T_OPTIMALFILL or _T_USETABS
    cmp eax,_T_OPTIMALFILL or _T_USETABS
    mov eax,esi

    .repeat

        .break .ifnz
        .break .if ecx < 5

        push esi
        xor eax,eax

        .while 1

            mov ebx,esi
            lodsb

            .switch al
              .case 0
              .case 10
              .case 13
                .break
              .case 39
              .case '"'
                mov bl,al
                .repeat
                    lodsb
                    .break(1) .if !al
                    cmp al,bl
                .until al == bl
                .continue(0)
            .endsw

            .continue(0) .if !(_ltype[eax+1] & _SPACE)
            .repeat
                lodsb
                .break(1) .if al == 10
                .break(1) .if al == 13
            .until !(_ltype[eax+1] & _SPACE)

            dec esi
            .while 1
                mov edi,ebx
                sub edi,[esp]
                mov ecx,edi
                add edi,8
                and edi,-8
                sub edi,ecx
                lea ecx,[esi+1]
                sub ecx,ebx
                .break .if ecx < 3
                .break .if ecx <= edi
                mov byte ptr [ebx],9
                inc ebx
                mov ecx,edi
                dec ecx
                .ifnz
                    mov edi,ebx
                    add ebx,ecx
                    mov al,TITABCHAR
                    rep stosb
                .endif
            .endw
            .if ecx
                dec ecx
                .ifnz
                    mov al,' '
                    mov edi,ebx
                    rep stosb
                .endif
            .endif
        .endw
        pop eax
    .until 1
    ret

tioptimalfill endp

    assume edx:ptr S_TINFO
    assume ecx:ptr S_TIOST

__st_open proc ti:PTINFO, ts:PTIOST, char:UINT

    .if ticurcp(ti)

        mov ecx,ts
        mov [ecx].ts_line_ptr,eax
        mov [ecx].ts_index,0

        mov eax,char
        mov [ecx].ts_char,al

        mov eax,[edx].ti_flp
        mov [ecx].ts_file_ptr,eax
        add eax,[edx].ti_fbcnt
        mov [ecx].ts_file_end,eax

        mov eax,[edx].ti_lp
        add eax,[edx].ti_bcol
        mov [ecx].ts_buffer,eax
    .endif
    ret

__st_open endp

__st_putc proc uses ecx ts:PTIOST, char:UINT

    mov eax,ts
    mov ecx,[eax].S_TIOST.ts_index

    .if ecx < TIMAXLINE

        add ecx,[eax].S_TIOST.ts_buffer
        inc [eax].S_TIOST.ts_index
        movzx   eax,byte ptr char
        mov [ecx],ax
        clc
    .else
        xor eax,eax
        stc
    .endif
    ret

__st_putc endp

    assume ecx:nothing
    assume esi:ptr S_TIOST

__st_copy2 proc uses esi ebx ti:PTINFO, ts:PTIOST

    mov esi,ts
    mov edx,ti

    mov ecx,[esi].ts_line_ptr
    mov ebx,[edx].ti_lp
    sub ecx,ebx
    .repeat
        mov al,[ebx]
        .if al != TITABCHAR
            __st_putc(esi, eax)
            jc toend
        .endif
        inc ebx
    .untilcxz
    clc
toend:
    ret
__st_copy2 endp

__st_copy proc uses esi ti:PTINFO, ts:PTIOST

    mov esi,ts
    mov edx,ti
    mov ecx,[esi].ts_line_ptr

    .if byte ptr [ecx] == TITABCHAR

        mov eax,2000h + TITABCHAR
        mov [ecx],ah

        .if [ecx+1] == al
            mov byte ptr [ecx],9
        .endif

        .if ecx > [edx].ti_lp

            .repeat
                dec ecx
                .break .if [ecx] != al
                mov [ecx],ah
            .until  ecx == [edx].ti_lp

            .if byte ptr [ecx] == 9
                mov [ecx],ah
            .endif
        .endif
    .endif

    __st_copy2(edx, esi)
    ret

__st_copy endp

    assume edx:ptr S_TIOST

__st_trim proc uses edx ecx ts:PTIOST

    mov edx,ts
    mov ecx,[edx].ts_index
    mov eax,[edx].ts_buffer

    .while ecx
        sub ecx,1

        .break .if byte ptr [eax+ecx] != ' '

        mov byte ptr [eax+ecx],0
        mov [edx].ts_index,ecx
    .endw
    ret

__st_trim endp

    assume edx:ptr S_TINFO

__st_flush proc uses esi edi ebx ti:PTINFO, ts:PTIOST

    mov esi,ts
    mov edx,ti

    .if [edx].ti_flag & _T_OPTIMALFILL && [esi].ts_index

        tiexpandline(edx, [esi].ts_buffer)
        tioptimalfill(edx, [esi].ts_buffer)

        mov ecx,eax
        mov ebx,eax
        mov [esi].ts_index,0

        .while  1
            mov al,[ecx]
            .break .if !al
            .if al != TITABCHAR
                mov [ebx],al
                inc ebx
                inc [esi].ts_index
            .endif
            inc ecx
        .endw

    .endif

    mov eax,[esi].ts_file_ptr
    add eax,[esi].ts_index
    mov ecx,[esi].ts_file_end
    cmp eax,ecx
    je  done
    jb  shrink

    strlen(ecx)
    inc eax
    add eax,[esi].ts_file_end
    mov ecx,[edx].ti_bp
    add ecx,[edx].ti_blen
    sub ecx,256
    cmp eax,ecx
    jb  extend

    mov eax,edx
    tirealloc(edx)
    jz  error

    sub [esi].ts_file_end,eax
    sub [esi].ts_file_ptr,eax
    mov eax,[edx].ti_bp
    add [esi].ts_file_end,eax
    add [esi].ts_file_ptr,eax
    mov eax,[edx].ti_lp
    add eax,[edx].ti_bcol
    mov [esi].ts_buffer,eax

shrink:
    mov eax,[esi].ts_file_ptr
    add eax,[esi].ts_index
    strmove(eax,[esi].ts_file_end)
done:
    memcpy([esi].ts_file_ptr, [esi].ts_buffer, [esi].ts_index)
    or  [edx].ti_flag,_T_MODIFIED
    xor eax,eax
toend:
    ret
extend:
    sub eax,[esi].ts_file_end
    mov ecx,[esi].ts_file_ptr
    add ecx,[esi].ts_index
    memmove(ecx,[esi].ts_file_end,eax)
    jmp done
error:
    mov eax,_TI_CMFAILED
    jmp toend

__st_flush endp

__st_tail proc uses esi edi ti:PTINFO, ts:PTIOST, tail:LPSTR

    mov esi,ts
    mov edi,tail

    .repeat
        movzx eax,byte ptr [edi]
        .while eax

            .if eax != TITABCHAR
                __st_putc(esi, eax)
                .ifc
                    mov eax,_TI_CMFAILED
                    .break
                .endif
            .endif
            add edi,1
            movzx eax,byte ptr [edi]
        .endw
        __st_trim(esi)
        __st_flush(ti, esi)
    .until 1
    ret

__st_tail endp

    END
