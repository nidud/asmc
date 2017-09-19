include tinfo.inc
include ltype.inc
include string.inc
include dzlib.inc

ST_ATTRIB   equ 1   ; attrib    <at> [<char>]
ST_CONTROL  equ 2   ; control   <at>
ST_QUOTE    equ 3   ; quote <at>
ST_NUMBER   equ 4   ; number    <at>
ST_CHAR     equ 5   ; char  <at> <chars>
ST_STRING   equ 6   ; string    <at> <string>
ST_START    equ 7   ; start <at> <string>
ST_WORD     equ 8   ; word  <at> <words> ...
ST_NESTED   equ 9   ; nested    <at> <string1> <string2>
ST_COUNT    equ 9

_X_QUOTE    equ 1
_X_COMMENT  equ 2
_X_BEGIN    equ 4
_X_WORD     equ 8

ISCHAR macro reg
    exitm<byte ptr _ltype[reg+1] & (_UPPER or _LOWER or _DIGIT)>
    endm

TOUPPER macro reg
    sub al,'a'
    cmp al,'z'-'a'+1
    sbb dl,dl
    and dl,'a'-'A'
    sub al,dl
    add al,'a'
    exitm  <reg>
    endm

TOLOWER macro reg
    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb dl,dl
    and dl,'a'-'A'
    add al,dl
    add al,'A'
    exitm <reg>
    endm

    .code

TIStyleIsQuote proc private uses esi edi ebx ecx line, string

    mov edi,line

    .while 1
        xor esi,esi
        xor ebx,ebx ; current quote
        mov eax,string
        sub eax,edi
        .break .ifng
        ;
        ; first offset of quote
        ;
        mov esi,memquote(edi, eax)
        .break .ifz

        or  bl,[eax]
        lea edi,[eax+1]

        .while 1
            .break(1) .if edi >= string
            mov ecx,string
            sub ecx,edi
            mov al,bl
            repnz scasb
            .break(1) .ifnz

            .break .if bl != '"'
            ;
            ; "case \"quoted text\""
            ;
            .break .if byte ptr [edi-2] != '\'
            ;
            ; case "C:\\"
            ;
            .break .if byte ptr [edi-3] == '\'
        .endw
    .endw

    mov eax,ebx ; return quote type
    ret

TIStyleIsQuote endp

tistyle proc uses esi edi ebx ti:PTINFO, line_id:dword, line_ptr:LPSTR, line_size:dword, out_buffer:LPWORD

local buffer:   LPSTR,  ; start of line
    endbuf:     LPSTR,  ; end of line
    endbufw:    LPSTR,  ; end of line (words)
    string:     LPSTR,
    ccount:     UINT,   ; length of visible line
    coffset:    UINT,   ; number of non-visible chars <= 8
    attrib[2]:  byte,   ; current attrib
    ctype[2]:   byte,   ; current type
    quote1:     LPSTR,  ; pointer to first quote
    ctable[256]:byte,   ; LUT of char offset in line
    xtable[256]:byte    ; inside "quotes"

    mov esi,ti
    mov edx,[esi].S_TINFO.ti_boff
    mov eax,line_ptr
    add eax,edx
    mov buffer,eax
    mov ecx,line_size
    sub ecx,edx
    .if ecx > [esi].S_TINFO.ti_cols

        mov ecx,[esi].S_TINFO.ti_cols
    .endif
    mov ccount,ecx
    add eax,ecx
    mov endbuf,eax
    mov endbufw,eax

    xor eax,eax
    mov ecx,256*2
    lea edi,xtable
    rep stosb

    .if edx

        mov ecx,8
    .endif

    .if edx >= 8

        mov edx,8
    .endif
    mov coffset,edx

    mov ecx,ccount  ; offset of last char + 1
    add ecx,edx     ; + <= 8 byte overlap
    mov ebx,buffer
    sub ebx,edx
    mov edi,endbuf
    .while  edi > ebx

        dec edi
        mov al,[edi]
        mov ctable[TOUPPER(eax)],cl
        mov ctable[TOLOWER(eax)],cl
        dec ecx
    .endw

    mov quote1,memquote(line_ptr, line_size)

    .if eax

        mov edi,eax
        mov bl,[edi] ; save quote in BL

        .while edi < endbuf

            movzx eax,byte ptr [edi]
            add edi,1
            .break .if !eax

            .if edi > buffer

                mov ecx,edi
                sub ecx,buffer
                or  xtable[ecx-1],1
            .endif

            .if [edi] == bl
                ;
                ; case C string \"
                ;
                .if bl == '"' && byte ptr [edi-1] == '\'
                    ;
                    ; case "C:\\"
                    ;
                    .continue .if byte ptr [edi-2] != '\'
                .endif
                inc edi
                .if edi > buffer

                    mov ecx,edi
                    sub ecx,buffer
                    or  xtable[ecx-1],1
                .endif
                mov ecx,line_size
                add ecx,line_ptr
                sub ecx,edi
                .break .if !memquote(edi, ecx)
                mov bl,[eax]
                mov edi,eax
            .endif
        .endw
    .endif

    .repeat

        mov esi,[esi].S_TINFO.ti_style

        .break .if !esi
        .break .if !ccount

        .while 1

            movzx eax,byte ptr [esi]
            movzx ebx,byte ptr [esi+1]
            add esi,2

            mov ctype,al
            mov attrib,bl

            .break .if !eax
            .break .if eax > ST_COUNT

            mov string,esi
            mov edx,endbuf
            .break  .if edx <= buffer

            .switch al
              .case ST_ATTRIB
                ;-----------------------------------------------
                ; 1. A Attrib   <at> [<char>]
                ;-----------------------------------------------
                mov edx,ti
                mov byte ptr [edx+1].S_TINFO.ti_stat,bl
                mov al,[esi]
                .if al

                    mov byte ptr [edx].S_TINFO.ti_stat,al
                .endif
                .endc

              .case ST_CONTROL
                ;-----------------------------------------------
                ; 2. O Control - match on all control chars
                ;-----------------------------------------------
                mov eax,ti
                .endc .if !([eax].S_TINFO.ti_flag & _T_SHOWTABS)

                xor eax,eax
                .for edx = out_buffer, edi = buffer,
                    al = [edi] : eax, edi < endbuf : edi++, al = [edi], edx += 2

                    .if eax != 9 && byte ptr _ltype[eax+1] & _CONTROL

                        mov [edx+1],bl
                    .endif
                .endf
                .endc

              .case ST_QUOTE
                ;-----------------------------------------------
                ; 3. Q Quote - match on '"' and "'"
                ;-----------------------------------------------
                xor eax,eax
                .for ecx = ccount,
                     edx = out_buffer,
                     edi = buffer : edi < endbuf, ecx : eax++, edi++, ecx--

                    .if xtable[eax] & _X_QUOTE

                        .if !(xtable[eax] & (_X_COMMENT or _X_BEGIN))

                            mov [edx+eax*2][1],bl
                        .endif
                    .endif
                .endf
                .endc

              .case ST_NUMBER
                ;-------------------------------------------------
                ; 4. D Digit - match on 0x 0123456789ABCDEF and Xh
                ;-------------------------------------------------
                mov edi,buffer
                .while edi < endbuf

                    movzx eax,byte ptr [edi]
                    add edi,1

                    .endc .if !eax

                    .if byte ptr _ltype[eax+1] & _DIGIT

                        lea edx,[edi-1]
                        .if edx > line_ptr

                            movzx ecx,byte ptr [edx-1]

                            .continue .if !ecx
                            .continue .if ecx == '_'
                            .continue .if ISCHAR(ecx)
                        .endif
                        mov esi,edi
                        .if al == '0'

                            mov cl,[esi]
                            or  cl,0x20
                            .if cl == 'x'

                                inc esi
                            .endif
                        .endif
                        xor ecx,ecx
                        .while 1
                            lodsb
                            .break .if !eax
                            .continue .if byte ptr _ltype[eax+1] & _HEX
                            or  al,0x20
                            .continue .if al == 'u' ; ..UL
                            .continue .if al == 'i' ; ..I64
                            .continue .if al == 'l' ; ..UL[L]
                            inc esi
                            .break .if al == 'h'    ; ..H
                            dec esi
                            mov al,[esi-1]
                            .break .if !(_ltype[eax+1] & _UPPER or _LOWER)
                            inc ecx
                            .break
                        .endw
                        .continue .if ecx

                        sub esi,edi
                        .while esi

                            lea eax,[edi-1]
                            .break .if eax >= endbuf
                            .if eax >= buffer

                                sub eax,buffer
                                .if !xtable[eax]

                                    add eax,eax
                                    add eax,out_buffer
                                    mov [eax+1],bl
                                .endif
                            .endif
                            inc edi
                            dec esi
                        .endw
                    .endif
                .endw
                .endc

              .case ST_CHAR
                ;-----------------------------------------------
                ; 5. C Char <at> <chars>
                ;-----------------------------------------------
                .while 1
                    movzx eax,byte ptr [esi]
                    add esi,1

                    .break .if !eax

                    .if ctable[eax]

                        mov ecx,ccount
                        mov edi,buffer
                        movzx edx,ctable[eax]
                        sub edx,coffset
                        add edi,edx
                        sub ecx,edx
                        .endc .ifs

                        .while edi <= endbuf

                            lea edx,[edi-1]
                            .if edx >= buffer
                                sub edx,buffer
                                .if !(xtable[edx] & (_X_COMMENT or _X_QUOTE or _X_BEGIN) )

                                    add edx,edx
                                    add edx,out_buffer
                                    mov [edx+1],bl
                                .endif
                            .endif
                            repnz scasb
                            .break .ifnz
                        .endw
                    .endif
                .endw
                .endc

              .case ST_STRING
                ;-------------------------------------------------------------
                ; 6. S String - match on all equal strings if not inside quote
                ;-------------------------------------------------------------
                .while byte ptr [esi]

                    mov edi,line_ptr
                    .while strstr(edi, esi)

                        lea edi,[eax+1]
                        .if eax >= buffer

                            mov edx,esi
                            mov ecx,eax
                            sub eax,buffer
                            add eax,eax
                            add eax,out_buffer
                            inc eax

                            .while ecx < endbuf && byte ptr [edx]

                                mov [eax],bl
                                add edx,1
                                add ecx,1
                                add eax,2
                            .endw
                        .endif
                    .endw
                    .repeat
                        lodsb
                        test al,al
                    .untilz
                .endw
                .endc

              .case ST_START
                ;-----------------------------------------------
                ; 7. B Begin - XX string
                ;    set color XX from string to end of line
                ;-----------------------------------------------
                .while byte ptr [esi]

                    mov eax,endbufw
                    .break .if eax <= buffer
                    sub eax,buffer
                    .if eax < 256 && xtable[eax-1] & _X_COMMENT

                        dec endbufw
                        .continue(0)
                    .endif

                    .repeat
                        movzx edx,byte ptr [esi]
                        movzx eax,ctable[edx]
                        .break .if !eax

                        mov edi,buffer
                        sub eax,coffset
                        add edi,eax

                        lea eax,[edi-1]
                        .if eax >= endbufw

                            mov eax,endbufw
                            dec eax
                        .endif
                        .if eax < buffer

                            mov eax,buffer
                        .endif
                        sub eax,buffer
                        and eax,0xFF
                        .break .if xtable[eax] & _X_QUOTE && edx != "'"

                        mov bh,byte ptr _ltype[edx+1]
                        and bh,_UPPER or _LOWER

                        lea eax,[edi-1]
                        .if eax > line_ptr && bh

                            movzx eax,byte ptr [eax-1]
                            .break .if !(byte ptr _ltype[eax+1] & _SPACE)
                        .endif

                        .while 1

                            mov edx,esi
                            lea ecx,[edi-1]
                            .repeat
                                add edx,1
                                add ecx,1
                                mov al,[edx]
                                .break .if !al
                                .continue(0) .if al == [ecx]
                                mov ah,[ecx]
                                or  eax,0x2020
                                .continue(0) .if al == ah
                            .until 1

                            .repeat
                                .break .if al

                                .if bh

                                    movzx eax,byte ptr [ecx]
                                    .break .if eax == '_'
                                    .break .if byte ptr _ltype[eax+1] & _UPPER or _LOWER
                                .endif

                                mov al,bl
                                and al,0x0F
                                .if al == 8
                                    mov bh,_X_COMMENT
                                .else
                                    mov bh,_X_BEGIN
                                .endif

                                lea eax,[edi-1]
                                mov ecx,endbufw
                                mov edx,eax
                                .if eax < buffer

                                    mov eax,buffer
                                .endif
                                .if bh == _X_COMMENT

                                    mov endbufw,eax
                                .endif
                                sub edx,buffer

                                .while edi <= ecx

                                    .if edi > buffer && edx < 256

                                        .if !(xtable[edx] & _X_COMMENT)

                                            lea eax,[edx*2]
                                            add eax,out_buffer
                                            mov [eax+1],bl
                                        .endif
                                        or  xtable[edx],bh
                                    .endif
                                    add edi,1
                                    add edx,1
                                .endw

                            .until 1

                            .break .if edi > endbufw
                            ;
                            ; continue search
                            ;
                            mov al,[esi]
                            mov cl,TOUPPER(al)
                            mov ch,TOLOWER(al)
                            xor edx,edx
                            .while edi < endbufw

                                mov al,[edi]
                                add edi,1
                                inc edx
                                .break .if al == cl
                                .break .if al == ch
                                dec edx
                            .endw
                            .break .if !edx
                        .endw
                    .until 1
                    .repeat
                        lodsb
                        test al,al
                    .untilz
                .endw
                .endc

              .case ST_WORD
                ;-----------------------------------------------
                ; 8. W Word - match on all equal words
                ;-----------------------------------------------
                .while byte ptr [esi]

                    mov eax,endbufw
                    .break .if eax <= buffer
                    sub eax,buffer
                    .if xtable[eax-1]

                        dec endbufw
                        .continue(0)
                    .endif

                    .repeat
                        movzx eax,byte ptr [esi]
                        .break .if !ctable[eax]

                        mov edi,buffer
                        movzx edx,ctable[eax]
                        sub edx,coffset
                        add edi,edx

                        .while 1

                            mov edx,esi
                            lea ecx,[edi-1]
                            .repeat
                                add edx,1
                                add ecx,1
                                mov al,[edx]
                                .break .if !al
                                .continue(0) .if al == [ecx]
                                mov ah,[ecx]
                                or  eax,0x2020
                                .continue(0) .if al == ah
                            .until 1

                            .repeat
                                .break .if al

                                lea edx,[edi-1]
                                .if edx >= buffer

                                    mov eax,edx
                                    sub eax,buffer
                                    and eax,0xFF
                                    .break .if xtable[eax] & _X_QUOTE
                                .endif
                                .if edx > line_ptr

                                    movzx eax,byte ptr [edx-1]
                                    .break .if eax == '_'
                                    .break .if ISCHAR(eax)
                                .endif

                                movzx eax,byte ptr [ecx]
                                .break .if al == '_'
                                .break .if ISCHAR(eax)

                                sub ecx,edi
                                lea eax,[edi-1]
                                sub eax,buffer
                                mov edx,eax
                                add eax,eax
                                add eax,out_buffer
                                inc eax
                                inc ecx

                                .assert eax >= out_buffer

                                .repeat
                                    .break .if edi > endbufw
                                    .if edi > buffer

                                        .if !xtable[edx]

                                            or  xtable[edx],_X_WORD
                                            mov [eax],bl
                                        .endif
                                    .endif
                                    add eax,2
                                    add edi,1
                                    add edx,1
                                .untilcxz

                            .until 1

                            .break .if edi > endbufw
                            ;
                            ; continue search
                            ;
                            mov al,[esi]
                            mov cl,TOUPPER(al)
                            mov ch,TOLOWER(al)
                            xor edx,edx
                            .while edi < endbufw

                                mov al,[edi]
                                add edi,1
                                inc edx
                                .break .if al == cl
                                .break .if al == ch
                                dec edx
                            .endw
                            .break .if !edx
                        .endw
                    .until 1
                    .repeat
                        lodsb
                        test al,al
                    .untilz
                .endw
                .endc

              .case ST_NESTED
                ;-----------------------------------------------
                ; 9. N Nested -- /* */
                ;-----------------------------------------------
                mov edi,line_ptr    ; find start condition
                mov eax,line_id
                xor ebx,ebx

                .if eax         ; first line ?
                    ;
                    ; seek back to last first arg (/*) */
                    ;
                    .if find_token()

                        mov ebx,eax ; EBX first arg
                        .repeat     ; ESI to next token
                            lodsb
                            test al,al
                        .untilz
                        movzx eax,byte ptr [esi]
                        ;
                        ; start, no end - ok
                        ;
                        .if eax
                            ;
                            ; find end */
                            ;
                            .if find_token() > ebx

                                xor eax,eax
                            .else
                                inc eax
                            .endif
                        .else
                            inc eax
                        .endif
                    .endif
                .endif

                .if eax

                    inc edi
                    mov ecx,line_size
                    find_arg2()
                .else
                    find_arg1()
                .endif
                .endc

            .endsw

            mov esi,string
            .repeat
                lodsb
                .continue .if al
                lodsb
            .until !al
        .endw
    .until 1
    ret

    ;--------------------------------------
    ; seek back to get offset of /* and */
    ;--------------------------------------

find_token:

    push edi
    push ebx
    push edx

    .repeat
        mov ebx,strlen(esi)
        .break  .ifz

        mov eax,ti
        mov edx,[eax].S_TINFO.ti_bp ; top of file
        mov edi,[eax].S_TINFO.ti_flp    ; current line
        mov eax,edi
        sub eax,edx
        .break  .ifz
        dec edi

        .while  1
            ;
            ; Find the first token searching backwards
            ;
            movzx eax,byte ptr [esi]
            mov ecx,edi
            sub ecx,edx
            .break .if !memrchr(edx, eax, ecx)

            mov edi,eax
            .continue .if strncmp(esi, edi, ebx)
            ;
            ; token found, now find start of line to make
            ; sure EDI is not indside " /* quotes */ "
            ;
            mov ecx,edi
            sub ecx,edx
            memrchr(edx, 10, ecx)
            lea eax,[eax+1]
            .ifz
                mov eax,edx
            .endif

            .if TIStyleIsQuote(eax, edi)

                .continue .if al == '"'
                ;
                ; ' is found but /* it's maybe a fake */
                ;
                .if streol(edi) != edi ; get end of line

                    sub eax,edi
                    .break .ifz

                    .continue .if memquote(edi, eax)
                .endif
            .endif
            mov eax,edi
            .break
        .endw
    .until 1
    pop edx
    pop ebx
    pop edi
    retn

set_attrib:

    .if edi > buffer

        .if edi > endbuf

            pop eax
            xor eax,eax
            retn
        .endif

        push ecx
        push eax
        lea eax,[edi-1] ; = offset in text line
        sub eax,buffer
        or  xtable[eax],_X_COMMENT
        add eax,eax
        add eax,out_buffer  ; = offset in screen line (*int)
        .assert eax >= out_buffer
        mov cl,attrib
        mov [eax+1],cl  ; set attrib for this char
        pop eax
        pop ecx
    .endif
    retn

clear_loop:

    .repeat
        inc edi
        set_attrib()
    .untilcxz

find_arg1:

    .repeat

        mov esi,string
        mov ecx,line_size
        mov eax,edi
        sub eax,line_ptr
        sub ecx,eax
        .ifng
            retn
        .endif
        mov al,[esi]
        repnz scasb
        .ifnz
            retn
        .endif
        inc esi
        xor eax,eax
        xor ebx,ebx

        .while 1
            inc ebx
            xor al,[esi+ebx-1]
            .break  .ifz
            sub al,[edi+ebx-1]
            .continue(01) .ifnz
        .endw

        .continue(0) .if TIStyleIsQuote(line_ptr, edi)

        .repeat
            set_attrib()
            add edi,1
            mov al,[esi]
            add esi,1
            .break(1) .if !al
        .untilcxz

        set_attrib()

    .until 1

find_arg2:

    .while ecx

        mov ax,[esi]    ; find next token
        test al,al
        jz clear_loop

        .repeat
            set_attrib()
            sub ecx,1
            .break(1) .ifz

            add edi,1
            .continue(0) .if al != [edi-2]
            test ah,ah
            jz find_arg1
        .until ah == [edi-1]

        .continue .if TIStyleIsQuote(line_ptr, edi)

        xor eax,eax
        xor ebx,ebx
        .repeat
            set_attrib()
            sub ecx,1
            .break(1) .ifz

            add edi,1
            add ebx,1
            xor al,[esi+ebx+1]
            jz  find_arg1
            sub al,[edi-1]
        .untilnz
        set_attrib()
    .endw
    retn

tistyle endp

    END
