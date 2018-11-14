; _WRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

.code

_write proc uses edi esi ebx h:SINT, b:PVOID, l:SIZE_T

  local result, count, lb[1026]:byte

    .repeat

        mov eax,l
        .break .if !eax

        mov ebx,h
        .if ebx >= _NFILE_

            xor eax,eax
            mov oserrno,eax
            mov errno,EBADF
            dec eax
            .break
        .endif

        .if _osfile[ebx] & FH_APPEND

            _lseek(h, 0, SEEK_END)
        .endif

        xor eax,eax
        mov result,eax
        mov count,eax

        .if _osfile[ebx] & FH_TEXT

            .for esi = b ::

                mov eax,esi
                sub eax,b
                .break .if eax >= l

                lea edi,lb
                .for :: esi++, edi++, count++

                    lea edx,lb
                    mov eax,edi
                    sub eax,edx
                    .break .if eax >= 1024

                    mov eax,esi
                    sub eax,b
                    .break .if eax >= l

                    mov al,[esi]
                    .if al == 10

                        mov byte ptr [edi],13
                        inc edi
                    .endif
                    mov [edi],al
                .endf

                lea eax,lb
                mov edx,edi
                sub edx,eax
                .if !oswrite(h, &lb, edx)

                    inc result
                    .break
                .endif
                lea ecx,lb
                mov edx,edi
                sub edx,ecx
                .break .if eax < edx
            .endf
        .else
            .break .if oswrite(h, b, l)

            inc result
        .endif

        mov eax,count
        .if !eax
            .if eax == result
                .if oserrno == 5 ; access denied

                    mov errno,EBADF
                .endif
            .else
                .if _osfile[ebx] & FH_DEVICE

                    mov ebx,b
                    .break .if byte ptr [ebx] == 26
                .endif
                mov errno,ENOSPC
                mov oserrno,0
            .endif
            dec eax
        .endif
    .until 1
    ret

_write endp

    end
