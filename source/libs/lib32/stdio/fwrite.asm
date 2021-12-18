; FWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include string.inc

    .code

    assume ebx:LPFILE

fwrite proc uses esi edi ebx buf:LPSTR, rsize:SINT, num:SINT, fp:LPFILE

  local total:SINT, bufsize:SINT, nbytes:SINT

    mov esi,buf
    mov ebx,fp
    mov eax,rsize
    mul num
    mov edi,eax
    mov total,eax

    mov edx,_MAXIOBUF
    .if [ebx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF

        mov edx,[ebx]._iobuf._bufsiz
    .endif
    mov bufsize,edx

    .while edi

        mov ecx,[ebx]._cnt
        .if [ebx]._flag & _IOMYBUF or _IOYOURBUF && ecx

            .if edi < ecx

                mov ecx,edi
            .endif

            sub edi,ecx
            sub [ebx]._cnt,ecx
            mov edx,edi
            mov edi,[ebx]._ptr
            add [ebx]._ptr,ecx
            rep movsb
            mov edi,edx

        .elseif edi >= bufsize

            .if [ebx]._flag & _IOMYBUF or _IOYOURBUF

                fflush( ebx )
                test eax,eax
                jnz break
            .endif

            mov eax,edi
            mov ecx,bufsize
            .if ecx

                xor edx,edx
                div ecx
                mov eax,edi
                sub eax,edx
            .endif
            mov nbytes,eax

            _write([ebx]._file, esi, eax)
            cmp eax,-1
            je  error

            sub edi,eax
            add esi,eax
            cmp eax,nbytes
            jb  error
        .else
            movzx eax,byte ptr [esi]
            _flsbuf(eax, ebx)
            cmp eax,-1
            je  break

            inc esi
            dec edi
            mov eax,[ebx]._bufsiz

            .if !eax

                mov eax,1
            .endif
            mov bufsize,eax
        .endif
    .endw
    mov eax,num
toend:
    ret
error:
    or  [ebx]._flag,_IOERR
break:
    mov eax,total
    sub eax,edi
    xor edx,edx
    div rsize
    jmp toend
fwrite  endp

    END
