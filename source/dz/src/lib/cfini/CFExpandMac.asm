include direct.inc
include string.inc
include alloc.inc
include winbase.inc
include dzlib.inc

    .code

CFExpandMac proc uses esi edi ebx string, file

  local longpath, longfile, shortpath, shortfile, S2, S1, drive

    .while  1

        .if !strchr(string, '!')
            ;
            ; "<string> <file>"
            ; "<string> "<file name>""
            ;
            lea ebx,S1
            mov eax,'" '
            mov [ebx],eax
            mov esi,strchr(file, ' ')

            .if !eax

                mov [ebx+1],al
            .endif

            strcat(strcat(string, ebx), file)

            .if esi

                inc ebx
                strcat(eax, ebx)
            .endif
            .break
        .endif

        ;---------------------------------------------------------------
        ; File macros:
        ;
        ;    !!	    !
        ;    !:	    Drive + ':'
        ;    !\	    Long path
        ;    !	    Long file name
        ;    .!	    Long extension
        ;    .!~    Short extension
        ;    !~\    Short path
        ;    ~!	    Short file name
        ;
        ;---------------------------------------------------------------

        mov longpath,alloca(WMAXPATH*2)
        mov edi,eax
        mov ecx,WMAXPATH*2
        add eax,WMAXPATH
        mov shortpath,eax
        xor eax,eax
        rep stosb

        GetFullPathName(file, WMAXPATH, strcpy(longpath, file), 0)

        xor eax,eax
        mov drive,eax
        mov edi,longpath
        mov ebx,[edi]

        .if bl != '\' && bh != ':'

            .break .if !GetCurrentDirectory(WMAXPATH, shortpath)

            strfcat(longpath, shortpath, file)
        .endif

        GetShortPathName(edi, strcpy(shortpath, edi), WMAXPATH)

        .if bh == ':'

            mov word ptr drive,bx
            strcpy(edi, addr [edi+3])
            mov ecx,shortpath
            strcpy(ecx, addr [ecx+3])
        .endif

        lea esi,S1
        lea edi,S2
        mov ebx,string
        ;
        ; remove <!!>
        ;
        mov dword ptr [esi],"!!"
        mov dword ptr [edi],"››"
        strxchg(ebx, esi, edi)
        ;
        ; xchg <!:> -- <<drive>:>
        ;
        mov byte ptr [esi+1],':'
        strxchg(ebx, esi, addr drive)
        ;
        ; xchg <.!~> -- <Short extension>
        ;
        xor eax,eax
        mov [edi],eax
        mov dword ptr [esi],"~!."
        strext(shortpath)
        mov edx,edi
        .if eax
            mov edx,eax
        .endif
        push edx
        strxchg(ebx, esi, edx)
        pop edx
        ;
        ; remove short extension
        ;
        .if edx != edi

            mov byte ptr [edx],0
        .endif
        ;
        ; xchg <.!> -- <Long extension>
        ;
        mov dword ptr [esi],"!."
        strext(longpath)
        mov edx,edi
        .if eax
            mov edx,eax
        .endif
        push    edx
        strxchg(ebx, esi, edx)
        pop edx
        ;
        ; remove long extension
        ;
        .if edx != edi

            mov byte ptr [edx],0
        .endif

        mov shortfile,strfn(shortpath)
        .if eax == shortpath

            mov shortpath,edi
        .else

            mov byte ptr [eax-1],0
        .endif

        mov longfile,strfn(longpath)
        .if eax == longpath

            mov longpath,edi
        .else

            mov byte ptr [eax-1],0
        .endif
        ;
        ; xchg <!\> -- <Long path>
        ;
        mov dword ptr [esi],"\!"
        strxchg(ebx, esi, longpath)
        ;
        ; xchg <!~\> -- <Short path>
        ;
        mov dword ptr [esi],"\~!"
        strxchg(ebx, esi, shortpath)
        ;
        ; xchg <!~> -- <Short file>
        ;
        mov dword ptr [esi],"!~"
        strxchg(ebx, esi, shortfile)
        ;
        ; xchg <!> -- <Long file>
        ;
        mov dword ptr [esi],"!"
        strxchg(ebx, esi, longfile)
        ;
        ; xchg <››> -- <!>
        ;
        mov dword ptr [esi],"››"
        mov dword ptr [edi],"!"
        strxchg(ebx, esi, edi)
        ;
        ; done
        ;
        .break
    .endw
    ret

CFExpandMac endp

    END
