; STRINGGETSWORKER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc
include tchar.inc

.code

StringGetsWorker proc uses rbx pszDest:LPTSTR, cchDest:size_t, pcchNewDestLength:ptr size_t

    .new hr:HRESULT = S_OK
    .new cchNewDestLength:size_t = 0

    ldr rcx,pszDest
    ldr rbx,cchDest

    .if ( rbx == 1 )

        mov TCHAR ptr [rcx],0
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER

    .else

        .while ( rbx > 1 )

            .ifd ( _fgettc(stdin) == EOF )

                .if ( cchNewDestLength == 0 )
                    mov hr,STRSAFE_E_END_OF_FILE
                .endif
                .break
            .endif
            .if ( _tal == 10 )
                .break
            .endif
            mov rcx,pszDest
            mov [rcx],_tal
            add rcx,TCHAR
            dec rbx
            mov pszDest,rcx
            inc cchNewDestLength
        .endw
        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif

    mov rdx,pcchNewDestLength
    .if ( rdx )
        mov rax,cchNewDestLength
        mov [rdx],rax
    .endif
    mov eax,hr
    ret
    endp

    end
