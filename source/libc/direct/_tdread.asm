; _TDREAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include string.inc
include malloc.inc
include tchar.inc

    .code

    assume rbx:PDIRENT

_dread proc uses rbx d:PDIRENT

   .new h:intptr_t
   .new fp:tstring_t
   .new ff:_tfinddatai64_t

    ldr rbx,d

    _dfree(rbx)
    _tcslen([rbx].path)
ifdef _UNICODE
    add eax,eax
endif
    add rax,[rbx].path
    mov fp,rax

    mov rcx,_tcsfcat([rbx].path, NULL, [rbx].mask)
    mov h,_tfindfirsti64(rcx, &ff)
    mov rcx,fp
    mov TCHAR ptr [rcx],0

    .if ( h == -1 )

       .return( 0 )
    .endif

    .while ( eax != -1 )

        .if ( ff.name == '.' && ff.name[TCHAR] == 0 )

            _tfindnexti64(h, &ff)
            .continue
        .endif

        _tcslen(&ff.name)
        .if !malloc(&[rax*TCHAR+FILENT])

            .break
        .endif

        mov rcx,rax
        mov [rcx].FILENT.name,NULL
        mov [rcx].FILENT.attrib,ff.attrib
        mov [rcx].FILENT.size,ff.size

        mov rax,[rbx].fcb
        .if ( rax == NULL )
            mov [rbx].fcb,rcx
        .else
            .while ( [rax].FILENT.name )
                mov rax,[rax].FILENT.name
            .endw
            mov [rax].FILENT.name,rcx
        .endif
        _tcscpy(&[rcx].FILENT.nbuf, &ff.name)

        inc [rbx].count
        _tfindnexti64(h, &ff)
    .endw
    _findclose(h)

    mov ecx,[rbx].count
    mov rdx,malloc(&[rcx*size_t+size_t])
    mov rcx,[rbx].fcb
    mov [rbx].fcb,rax

    assume rbx:nothing

    .if ( rax )

        .for ( rbx = rcx : rbx : rdx+=size_t )

            mov [rdx],rbx
            lea rax,[rbx].FILENT.nbuf
            mov rcx,rbx
            mov rbx,[rbx].FILENT.name
            mov [rcx].FILENT.name,rax
        .endf
        mov [rdx],rbx
        mov rbx,d
        mov eax,[rbx].DIRENT.count

    .else

        .for ( rbx = rcx : rbx : )

            mov rcx,rbx
            mov rbx,[rbx].FILENT.name
            free(rcx)
        .endf
        xor eax,eax
    .endif
    ret

_dread endp

    end
