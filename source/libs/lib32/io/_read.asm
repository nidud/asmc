; _READ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

ER_ACCESS_DENIED equ 5
ER_BROKEN_PIPE   equ 109

.data
pipech  db _NFILE_ dup(10)
peekchr db 0

.code

read proc h:SINT, b:PVOID, count:SIZE_T
read endp

_read proc uses ebx esi edi h:SINT, b:PVOID, count:SIZE_T

  local NumberOfBytesRead:dword

    xor esi,esi         ; nothing read yet
    mov edi,b
    mov ebx,h
    xor eax,eax         ; nothing to read or at EOF

    .repeat

        .break .if eax == count

        movzx ecx,_osfile[ebx]
        .break .if ecx & FH_EOF

        mov _doserrno,eax
        .if ecx & FH_PIPE or FH_DEVICE
            mov al,pipech[ebx]
            .if al != 10
                mov [edi],al
                mov pipech[ebx],10
                inc edi
                inc esi
                dec count
            .endif
        .endif

        mov ecx,_osfhnd[ebx*4]
        .if !ReadFile(ecx, edi, count, &NumberOfBytesRead, 0)

            osmaperr()

            xor eax,eax
            mov edx,_doserrno
            .break .if edx == ER_BROKEN_PIPE

            dec eax
            .break .if edx != ER_ACCESS_DENIED
            mov errno,EBADF
            .break
        .endif

        add esi,NumberOfBytesRead
        mov edi,b
        mov al,_osfile[ebx]

        .if al & FH_TEXT

            and al,not FH_CRLF
            .if byte ptr [edi] == 10

                or al,FH_CRLF
            .endif
            mov _osfile[ebx],al

            mov edx,edi
            .while 1

                mov eax,b
                add eax,esi
                .break .if edi >= eax

                mov al,[edi]
                .if al == 26
                    .break .if _osfile[ebx] & FH_DEVICE
                    or _osfile[ebx],FH_EOF
                    .break
                .endif

                .if al != 13
                    mov [edx],al
                    inc edi
                    inc edx
                    .continue
                .endif

                mov eax,b
                lea eax,[eax+esi-1]
                .if edi < eax
                    .if byte ptr [edi+1] == 10
                        add edi,2
                        mov al,10
                    .else
                        mov al,[edi]
                        inc edi
                    .endif
                    mov [edx],al
                    inc edx
                    .continue
                .endif

                inc  edi
                push edx
                mov  ecx,_osfhnd[ebx*4]
                ReadFile(ecx, &peekchr, 1, &NumberOfBytesRead, 0)
                pop  edx

                .if !eax || !NumberOfBytesRead
                    mov al,13
                .elseif _osfile[ebx] & FH_DEVICE or FH_PIPE
                    mov al,10
                    .if peekchr != al
                        mov al,peekchr
                        mov pipech[ebx],al
                        mov al,13
                    .endif
                .else
                    mov al,10
                    .if b != edx || peekchr != al
                        push edx
                        _lseek(ebx, -1, SEEK_CUR)
                        pop  edx
                        mov  al,13
                        .continue .if peekchr == 10
                    .endif
                .endif
                mov [edx],al
                inc edx
            .endw
            mov eax,edx
            sub eax,b
        .else
            mov eax,esi
        .endif

    .until 1
    ret

_read endp

    end
