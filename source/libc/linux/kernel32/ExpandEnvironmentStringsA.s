; EXPANDENVIRONMENTSTRINGSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include string.inc
include winbase.inc

.code

 ExpandEnvironmentStringsA proc WINAPI uses rbx lpSrc:LPCSTR, lpDst:LPSTR, nSize:DWORD
   .new needed:uint_t = 0
   .new remain:uint_t
   .new varlen:uint_t
   .new toklen:uint_t
   .new dstptr:string_t
   .new tmpptr:string_t
   .new namebuf[256]:char_t
    ldr rbx,lpSrc
    ldr rdx,lpDst
    ldr eax,nSize
    .if ( !rbx )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
    .if ( !rdx )
        xor eax,eax
    .endif
    mov remain,eax
    mov dstptr,rdx
    .while ( byte ptr [rbx] )
        mov al,[rbx]
        .if ( al == '%' )
            .if strchr(&[rbx+1], '%')
                sub rax,rbx
                dec rax
                .ifs ( eax > 0 && eax < 256 )
                    mov toklen,eax
                    memcpy(&namebuf, &[rbx+1], eax)
                    mov eax,toklen
                    mov namebuf[rax],0
                    GetEnvironmentVariableA(&namebuf, NULL, 0)
                    .ifs ( eax > 0 )
                        dec eax
                        mov varlen,eax
                        add needed,eax
                        mov ecx,remain
                        .if ( ecx > 1 )
                            mov edx,ecx
                            dec edx
                            .if ( eax <= edx )
                                GetEnvironmentVariableA(&namebuf, dstptr, ecx)
                                add dstptr,rax
                                sub remain,eax
                            .else
                                inc eax
                                mov varlen,eax
                                .if malloc(rax)
                                    mov tmpptr,rax
                                    GetEnvironmentVariableA(&namebuf, tmpptr, varlen)
                                    mov edx,remain
                                    dec edx
                                    memcpy(dstptr, tmpptr, rdx)
                                    mov edx,remain
                                    dec edx
                                    add dstptr,rdx
                                    mov remain,1
                                    free(tmpptr)
                                .endif
                            .endif
                        .endif
                        mov eax,toklen
                        lea rbx,[rbx+rax+2]
                       .continue
                    .endif
                .endif
            .endif
        .endif
        mov al,[rbx]
        inc rbx
        inc needed
        .if ( remain > 1 )
            mov rdx,dstptr
            mov [rdx],al
            inc dstptr
            dec remain
        .endif
    .endw
    mov rdx,dstptr
    inc needed
    .if ( remain >= 1 && rdx )
        mov byte ptr [rdx],0
    .endif
    .return( needed )
    endp

    end
