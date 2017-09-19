include iost.inc
include string.inc

extern searchstring:byte

    .code

SearchText proc private uses esi edi ebx pos:qword

local len:dword

    mov len,strlen(&searchstring)
    mov ebx,dword ptr pos[4]
    mov edi,dword ptr pos

    .while 1

        .break .if !eax

        xor ecx,ecx
        xor edx,edx
        mov dl,searchstring
        bt  STDI.ios_flag,0

        .ifc
            .while 1

                ogetc()
                .ifz
                    or  eax,-1
                    mov edx,eax
                    xor ebx,ebx
                    .break(1)
                .endif

                add edi,1
                adc ebx,0
                .break .if eax == edx
                .continue(0) .if eax != 10
                inc ecx
            .endw
        .else

            mov eax,edx
            sub al,'A'
            cmp al,'Z'-'A'+1
            sbb edx,edx
            and edx,'a'-'A'
            add eax,edx
            add eax,'A'
            mov edx,eax     ; tolower(*searchstring)

            .while 1

                ogetc()
                .ifz
                    or  eax,-1
                    mov edx,eax
                    xor ebx,ebx
                    .break(1)
                .endif

                add edi,1
                adc ebx,0

                .break .if al == dl

                sub al,'A'
                cmp al,'Z'-'A'+1
                sbb ah,ah
                and ah,'a'-'A'
                add al,ah
                add al,'A'      ; tolower(AL)

                .break .if al == dl
                .continue(0) .if eax != 10
                inc ecx
            .endw
        .endif

        add STDI.ios_line,ecx
        lea esi,searchstring
        mov eax,len
        mov ecx,STDI.ios_c
        sub ecx,STDI.ios_i
        .if eax >= ecx

            .if STDI.ios_flag & IO_MEMBUF || !ioread(&STDI)
                or  eax,-1
                mov edx,eax
                xor ebx,ebx
                .break
            .endif
        .endif

        .while 1

            ogetc()
            .ifz
                or  eax,-1
                mov edx,eax
                xor ebx,ebx
                .break(1)
            .endif

            add edi,1
            adc ebx,0

            inc esi
            lea edx,searchstring
            mov ecx,eax
            mov al,[esi]
            .break .if !eax
            .continue(0) .if eax == ecx

            bt STDI.ios_flag,0 ; IO_SEARCHCASE
            .ifnc
                mov ah,cl
                sub ax,'AA'
                cmp al,'Z'-'A' + 1
                sbb cl,cl
                and cl,'a'-'A'
                cmp ah,'Z'-'A' + 1
                sbb ch,ch
                and ch,'a'-'A'
                add ax,cx
                add ax,'AA'
                .continue(0) .if al == ah
            .endif

            mov eax,esi
            sub eax,edx
            sub edi,eax
            sbb ebx,0
            sub STDI.ios_i,eax
            .continue(1)
        .endw

        mov eax,esi
        sub eax,edx
        inc eax
        sub edi,eax
        sbb ebx,0
        mov eax,edi
        mov edx,ebx
        or  edi,1
        mov ecx,STDI.ios_line
        .break
    .endw
    ret

SearchText endp

SearchHex proc private uses esi edi ebx pos:qword

  local hex[128]:byte
  local string:LPSTR
  local hexstrlen:dword

    xor ecx,ecx
    lea esi,searchstring
    lea edx,hex
    mov string,edx
    mov ebx,dword ptr pos[4]
    mov edi,dword ptr pos

    .while 1

        .repeat
            mov al,[esi]
            .break(1) .if !al
            inc esi
            .continue(0) .if al < '0'
            .if al > '9'
                or al,0x20
                .continue(0) .if al > 'f'
                sub al,0x27
            .endif
            sub al,'0'
        .until 1
        mov ah,al
        .repeat
            mov al,[esi]
            .if !al
                xchg al,ah
                .break
            .endif
            inc esi
            .continue(0) .if al < '0'
            .if al > '9'
                or al,0x20
                .continue(0) .if al > 'f'
                sub al,0x27
            .endif
            sub al,'0'
        .until 1
        shl ah,4
        or  al,ah
        mov [edx],al
        inc edx
        inc ecx
    .endw
    mov hexstrlen,ecx

    .while 1

        mov eax,string
        movzx edx,byte ptr [eax]
        mov ecx,STDI.ios_line

        .while 1

            ogetc()
            .ifz
                or  eax,-1
                mov edx,eax
                xor ebx,ebx
                .break(1)
            .endif

            add edi,1   ; inc offset
            adc ebx,0

            .break .if al == dl
            .continue(0) .if eax != 10
            inc ecx
        .endw

        mov STDI.ios_line,ecx
        mov esi,string
        mov eax,hexstrlen
        mov ecx,STDI.ios_c
        sub ecx,STDI.ios_i

        .if eax >= ecx

            .if STDI.ios_flag & IO_MEMBUF || !ioread(&STDI)
                or  eax,-1
                mov edx,eax
                xor ebx,ebx
                .break
            .endif
        .endif

        .while 1

            ogetc()
            .ifz
                or  eax,-1
                mov edx,eax
                xor ebx,ebx
                .break(1)
            .endif

            add edi,1
            adc ebx,0

            inc esi
            mov edx,string
            mov ecx,esi
            sub ecx,edx
            .if ecx == hexstrlen

                mov eax,esi
                sub eax,edx
                inc eax
                sub edi,eax
                sbb ebx,0
                mov eax,edi
                mov edx,ebx
                or  edi,1
                mov ecx,STDI.ios_line
                .break(1)
            .endif
            .break .if al != [esi]
        .endw

        mov eax,esi
        sub eax,edx
        sub edi,eax
        sbb ebx,0
        sub STDI.ios_i,eax
    .endw
    ret

SearchHex endp

osearch proc

    mov eax,dword ptr STDI.ios_offset
    mov edx,dword ptr STDI.ios_offset[4]
    mov ecx,STDI.ios_flag
    and STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)

    .if ecx & IO_SEARCHSET
        xor eax,eax
        xor edx,edx
    .elseif !(ecx & IO_SEARCHCUR)
        add eax,1       ; offset++ (continue)
        adc edx,0
    .endif

    ioseek(&STDI, edx::eax, SEEK_SET)
    .ifnz
        .if STDI.ios_flag & IO_SEARCHHEX
            SearchHex(edx::eax)
        .else
            SearchText(edx::eax)
        .endif
    .endif
    ret

osearch endp

    END
