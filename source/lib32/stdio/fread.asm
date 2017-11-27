include stdio.inc
include io.inc
include errno.inc
include string.inc

    .code

    assume ebx:ptr _iobuf

fread proc uses esi edi ebx buf:LPSTR, rsize:SINT, num:SINT, fp:LPFILE

  local total:SIZE_T, bufsize:SIZE_T, nbytes:SIZE_T

    mov esi,buf
    mov eax,rsize
    mov ecx,num
    mov ebx,fp
    mul ecx
    mov total,eax
    mov edi,eax

    test eax,eax
    jz  toend

    mov edx,_MAXIOBUF
    .if [ebx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF

        mov edx,[ebx]._bufsiz
    .endif
    mov bufsize,edx

    .while edi

        mov edx,[ebx]._cnt
        .if [ebx]._flag & _IOMYBUF or _IOYOURBUF && edx

            .if edi < edx

                mov edx,edi
            .endif
            memcpy(esi, [ebx]._ptr, edx)

            sub edi,edx
            sub [ebx]._cnt,edx
            add [ebx]._ptr,edx
            add esi,edx

        .elseif edi >= bufsize

            mov eax,edi
            mov ecx,bufsize
            .if ecx

                xor edx,edx
                div ecx
                mov eax,edi
                sub eax,edx
            .endif
            mov nbytes,eax

            .if !_read( [ebx]._file, esi, eax )

                jmp error

            .elseif eax == -1

                jmp error
            .endif

            sub edi,eax
            add esi,eax

        .else
            .if _filbuf(ebx) == -1

                jmp break
            .endif

            mov [esi],al
            inc esi
            dec edi
            mov eax,[ebx]._bufsiz
            mov bufsize,eax
        .endif
    .endw
    mov eax,num
toend:
    ret
error:
    or  [ebx]._flag,_IOEOF
break:
    mov eax,total
    sub eax,edi
    xor edx,edx
    div rsize
    jmp toend
fread   endp

    END
